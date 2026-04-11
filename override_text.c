/*
 * override_text.c — Runtime text override system for nesrecomp games.
 *
 * See override_text.h for architecture and usage.
 *
 * PPU DMA buffer format ($0500, used by Faxanadu's $CF3C processor):
 *
 *   Normal packet (count 0x00–0xF9):
 *     [count | flags, ppu_addr_hi, ppu_addr_lo, tile_0, ..., tile_{count-1}]
 *     High bit of count = PPUCTRL vertical-increment flag (strip before use).
 *     count & 0x7F = number of tile bytes that follow.
 *
 *   Special command (count 0xFA–0xFF):
 *     Game-defined dispatch.  These are 3-byte commands — skip without modifying.
 *
 *   Read  pointer: g_ram[0x1F] (incremented by NMI drain)
 *   Write pointer: g_ram[0x20] (incremented by game code)
 *   Both are 8-bit; the buffer wraps within the 256-byte $0500 page.
 */

#include "override_text.h"
#include "nes_runtime.h"   /* g_ram[], runner_get_prg_bank_rw() */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* ---- Platform stat() -------------------------------------------------- */

#ifdef _WIN32
#  include <sys/stat.h>
   typedef struct _stat StatBuf;
#  define stat_call(path, buf) _stat((path), (buf))
#else
#  include <sys/stat.h>
   typedef struct stat StatBuf;
#  define stat_call(path, buf) stat((path), (buf))
#endif

/* ---- NES DMA buffer constants ----------------------------------------- */

#define BUF_BASE      0x500u  /* base address of PPU DMA buffer in RAM     */
#define BUF_RD_PTR    0x1Fu   /* RAM address: current read  pointer (1 byte) */
#define BUF_WR_PTR    0x20u   /* RAM address: current write pointer (1 byte) */
#define SPACE_TILE    0x20u   /* tile byte for ASCII space — used as pad     */
#define SPECIAL_FIRST 0xFAu   /* first special-command opcode (skip)        */

/* ---- $0500 buffer scanner table --------------------------------------- */

typedef struct {
    uint8_t pattern[TEXT_OVERRIDE_MAX_LEN];
    uint8_t replacement[TEXT_OVERRIDE_MAX_LEN];
    int     pattern_len;
    int     replacement_len;
    int     hit_count;
} TextOverride;

static TextOverride s_overrides[TEXT_OVERRIDE_MAX];
static int          s_num_overrides = 0;

/* ---- Encoding registry ----------------------------------------------- */

typedef struct {
    char           name[32];
    tile_encode_fn fn;
} EncEntry;

static EncEntry s_encodings[TEXT_OVERRIDE_MAX_ENC];
static int      s_num_encodings = 0;

/* ---- JSON hot-reload state -------------------------------------------- */

static char   s_json_path[512];
static int    s_json_path_set = 0;
static time_t s_json_mtime    = 0;
static int    s_reload_ticks  = 0;

#define RELOAD_INTERVAL 60  /* check mtime every 60 calls (~1 s at 60 fps) */

/* ======================================================================
 * Lifecycle
 * ====================================================================== */

void text_override_init(void) {
    s_num_overrides = 0;
    s_num_encodings = 0;
    s_json_path_set = 0;
    s_json_mtime    = 0;
    s_reload_ticks  = 0;
}

/* ======================================================================
 * Encoding registry
 * ====================================================================== */

void text_override_register_encoding(const char *name, tile_encode_fn fn) {
    if (s_num_encodings >= TEXT_OVERRIDE_MAX_ENC) {
        fprintf(stderr, "[TextOverride] encoding table full\n");
        return;
    }
    EncEntry *e = &s_encodings[s_num_encodings++];
    strncpy(e->name, name, sizeof(e->name) - 1);
    e->name[sizeof(e->name) - 1] = '\0';
    e->fn = fn;
}

tile_encode_fn text_override_find_encoding(const char *name) {
    for (int i = 0; i < s_num_encodings; i++) {
        if (strcmp(s_encodings[i].name, name) == 0)
            return s_encodings[i].fn;
    }
    return NULL;
}

/* ======================================================================
 * PRG ROM patching (raw)
 * ====================================================================== */

void text_override_patch_prg(int bank, uint16_t prg_addr,
                              const uint8_t *replacement, int rep_len) {
    uint8_t *bank_ptr = runner_get_prg_bank_rw(bank);
    if (!bank_ptr) {
        fprintf(stderr, "[TextOverride] patch_prg: bank %d not available\n", bank);
        return;
    }
    if (prg_addr < 0x8000 || prg_addr > 0xBFFF) {
        fprintf(stderr, "[TextOverride] patch_prg: addr $%04X out of $8000-$BFFF range\n",
                prg_addr);
        return;
    }
    int offset = prg_addr - 0x8000;
    if (offset + rep_len > 0x4000) {
        fprintf(stderr, "[TextOverride] patch_prg: patch would exceed bank boundary\n");
        return;
    }
    memcpy(bank_ptr + offset, replacement, (size_t)rep_len);
}

/* ---- ASCII + encoder, fixed original_len ------------------------------ */

int text_override_patch_prg_ascii(int bank, uint16_t prg_addr,
                                   const char *replacement,
                                   tile_encode_fn encode) {
    /* +1 for the null terminator we always append. */
    uint8_t buf[TEXT_OVERRIDE_MAX_LEN + 1];
    int     rep_len = 0;

    for (const char *p = replacement; *p; p++) {
        if (rep_len >= TEXT_OVERRIDE_MAX_LEN) return 0;
        uint8_t t = encode(*p);
        if (t == 0xFF) return 0;
        buf[rep_len++] = t;
    }
    if (rep_len == 0) return 0;

    buf[rep_len] = 0x00;  /* implicit null terminator */

    text_override_patch_prg(bank, prg_addr, buf, rep_len + 1);
    return 1;
}

/* ---- ASCII + encoder, _auto variant (addr only, no length needed) ----- */

int text_override_patch_prg_auto(int bank, uint16_t prg_addr,
                                  const char *replacement,
                                  tile_encode_fn encode) {
    return text_override_patch_prg_ascii(bank, prg_addr, replacement, encode);
}

/* ======================================================================
 * Minimal JSON parser
 * ====================================================================== */

static const char *json_skip_ws(const char *p) {
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') p++;
    return p;
}

/* Read a quoted JSON string into buf (buflen includes null terminator).
 * Returns pointer past closing '"', or NULL on error. */
static const char *json_read_str(const char *p, char *buf, int buflen) {
    if (*p != '"') return NULL;
    p++;
    int i = 0;
    while (*p && *p != '"') {
        if (*p == '\\') {
            p++;
            if (!*p) return NULL;
            /* Minimal escaping: just emit the next character as-is. */
        }
        if (i < buflen - 1) buf[i++] = *p;
        p++;
    }
    if (*p != '"') return NULL;
    buf[i] = '\0';
    return p + 1;
}

/* Read a non-negative decimal integer. */
static const char *json_read_int(const char *p, int *out) {
    if (*p < '0' || *p > '9') return NULL;
    *out = 0;
    while (*p >= '0' && *p <= '9') {
        *out = *out * 10 + (*p - '0');
        p++;
    }
    return p;
}

/* Skip past a JSON value of any type. */
static const char *json_skip_value(const char *p) {
    p = json_skip_ws(p);
    if (*p == '"') {
        char tmp[256];
        return json_read_str(p, tmp, sizeof(tmp));
    }
    if ((*p >= '0' && *p <= '9') || *p == '-') {
        int tmp;
        if (*p == '-') p++;
        return json_read_int(p, &tmp);
    }
    if (*p == '[') {
        p++;
        p = json_skip_ws(p);
        while (*p && *p != ']') {
            p = json_skip_value(p);
            if (!p) return NULL;
            p = json_skip_ws(p);
            if (*p == ',') p++;
        }
        if (*p == ']') p++;
        return p;
    }
    if (*p == '{') {
        p++;
        p = json_skip_ws(p);
        while (*p && *p != '}') {
            char key[64];
            const char *q = json_read_str(p, key, sizeof(key));
            if (!q) return NULL;
            p = json_skip_ws(q);
            if (*p != ':') return NULL;
            p = json_skip_value(p + 1);
            if (!p) return NULL;
            p = json_skip_ws(p);
            if (*p == ',') p++;
            p = json_skip_ws(p);
        }
        if (*p == '}') p++;
        return p;
    }
    /* null / true / false */
    while (*p && *p != ',' && *p != ']' && *p != '}' && *p != ' ') p++;
    return p;
}

/*
 * Parse one JSON object:
 *   { "bank": <int>, "addr": "<hex>", "encoding": "<name>", "replacement": "<str>" }
 * Calls text_override_patch_prg_auto() on success.
 * Returns 1 on success, 0 on parse/lookup/patch error.
 * *pp is advanced past the closing '}'.
 */
static int json_parse_entry(const char **pp) {
    const char *p = json_skip_ws(*pp);
    if (*p != '{') return 0;
    p++;

    int      bank     = -1;
    uint16_t addr     = 0;
    char     enc_name[32]                    = {0};
    char     replacement[TEXT_OVERRIDE_MAX_LEN] = {0};
    int      have_bank = 0, have_addr = 0, have_enc = 0, have_rep = 0;

    while (1) {
        p = json_skip_ws(p);
        if (*p == '}') { p++; break; }
        if (*p == ',') { p++; continue; }
        if (*p == '\0') return 0;

        char key[32];
        p = json_read_str(p, key, sizeof(key));
        if (!p) return 0;
        p = json_skip_ws(p);
        if (*p != ':') return 0;
        p++;
        p = json_skip_ws(p);

        if (strcmp(key, "bank") == 0) {
            p = json_read_int(p, &bank);
            if (!p) return 0;
            have_bank = 1;
        } else if (strcmp(key, "addr") == 0) {
            char hex[8] = {0};
            p = json_read_str(p, hex, sizeof(hex));
            if (!p) return 0;
            addr = (uint16_t)strtoul(hex, NULL, 16);
            have_addr = 1;
        } else if (strcmp(key, "encoding") == 0) {
            p = json_read_str(p, enc_name, sizeof(enc_name));
            if (!p) return 0;
            have_enc = 1;
        } else if (strcmp(key, "replacement") == 0) {
            p = json_read_str(p, replacement, sizeof(replacement));
            if (!p) return 0;
            have_rep = 1;
        } else {
            p = json_skip_value(p);
            if (!p) return 0;
        }
    }

    *pp = p;

    if (!have_bank || !have_addr || !have_enc || !have_rep) {
        fprintf(stderr, "[TextOverride] JSON entry missing required field(s)\n");
        return 0;
    }

    tile_encode_fn encode = text_override_find_encoding(enc_name);
    if (!encode) {
        fprintf(stderr, "[TextOverride] JSON: unknown encoding \"%s\"\n", enc_name);
        return 0;
    }

    if (!text_override_patch_prg_auto(bank, addr, replacement, encode)) {
        fprintf(stderr, "[TextOverride] JSON: patch failed bank%d $%04X \"%s\"\n",
                bank, addr, replacement);
        return 0;
    }

    return 1;
}

/* ======================================================================
 * JSON file loading
 * ====================================================================== */

int text_override_load_json(const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "[TextOverride] Cannot open \"%s\"\n", path);
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    rewind(f);

    if (fsize <= 0 || fsize > 65536) {
        fclose(f);
        fprintf(stderr, "[TextOverride] JSON file size out of range (%ld bytes)\n", fsize);
        return -1;
    }

    char *buf = (char *)malloc((size_t)fsize + 1);
    if (!buf) { fclose(f); return -1; }
    size_t nread = fread(buf, 1, (size_t)fsize, f);
    fclose(f);
    buf[nread] = '\0';

    /* Cache path and mtime for hot-reload. */
    strncpy(s_json_path, path, sizeof(s_json_path) - 1);
    s_json_path[sizeof(s_json_path) - 1] = '\0';
    s_json_path_set = 1;

    StatBuf st;
    if (stat_call(path, &st) == 0)
        s_json_mtime = st.st_mtime;

    /* Parse: expect a top-level array. */
    const char *p = json_skip_ws(buf);
    if (*p != '[') {
        fprintf(stderr, "[TextOverride] JSON: expected '[' at start of \"%s\"\n", path);
        free(buf);
        return -1;
    }
    p++;

    int count = 0;
    while (1) {
        p = json_skip_ws(p);
        if (*p == ']' || *p == '\0') break;
        if (*p == ',') { p++; continue; }
        if (*p != '{') {
            fprintf(stderr, "[TextOverride] JSON: expected '{' or ']'\n");
            break;
        }
        if (json_parse_entry(&p))
            count++;
    }

    free(buf);
    printf("[TextOverride] %d override(s) loaded from \"%s\"\n", count, path);
    return count;
}

/* ======================================================================
 * Hot reload
 * ====================================================================== */

void text_override_reload_if_changed(void) {
    if (!s_json_path_set) return;
    if (++s_reload_ticks < RELOAD_INTERVAL) return;
    s_reload_ticks = 0;

    StatBuf st;
    if (stat_call(s_json_path, &st) != 0) return;
    if (st.st_mtime == s_json_mtime) return;

    printf("[TextOverride] Change detected, reloading \"%s\"\n", s_json_path);
    text_override_load_json(s_json_path);
}

/* ======================================================================
 * $0500 DMA buffer — pattern registration
 * ====================================================================== */

void text_override_register(const uint8_t *pattern,     int pattern_len,
                             const uint8_t *replacement, int replacement_len) {
    if (s_num_overrides >= TEXT_OVERRIDE_MAX) {
        fprintf(stderr, "[TextOverride] table full, cannot register pattern\n");
        return;
    }
    if (pattern_len <= 0 || pattern_len > TEXT_OVERRIDE_MAX_LEN ||
        replacement_len <= 0 || replacement_len > TEXT_OVERRIDE_MAX_LEN) {
        fprintf(stderr, "[TextOverride] invalid pattern/replacement length\n");
        return;
    }
    TextOverride *o = &s_overrides[s_num_overrides++];
    memcpy(o->pattern,     pattern,     (size_t)pattern_len);
    memcpy(o->replacement, replacement, (size_t)replacement_len);
    o->pattern_len     = pattern_len;
    o->replacement_len = replacement_len;
    o->hit_count       = 0;
}

int text_override_register_ascii(const char *original, const char *override_str,
                                  tile_encode_fn encode) {
    uint8_t pat[TEXT_OVERRIDE_MAX_LEN];
    uint8_t rep[TEXT_OVERRIDE_MAX_LEN];
    int     pat_len = 0, rep_len = 0;

    for (const char *p = original; *p; p++) {
        if (pat_len >= TEXT_OVERRIDE_MAX_LEN) return 0;
        uint8_t t = encode(*p);
        if (t == 0xFF) return 0;
        pat[pat_len++] = t;
    }
    for (const char *p = override_str; *p; p++) {
        if (rep_len >= TEXT_OVERRIDE_MAX_LEN) return 0;
        uint8_t t = encode(*p);
        if (t == 0xFF) return 0;
        rep[rep_len++] = t;
    }
    if (pat_len == 0 || rep_len == 0) return 0;

    text_override_register(pat, pat_len, rep, rep_len);
    return 1;
}

/* ======================================================================
 * $0500 DMA buffer — apply overrides
 * ====================================================================== */

static inline uint8_t buf_advance(uint8_t ptr, uint8_t n) {
    return (uint8_t)(ptr + n);
}

/*
 * Walk every packet in the $0500 buffer between the current read and write
 * pointers.  For each normal packet, search its tile payload for every
 * registered pattern and replace it in-place.
 *
 * Replacement shorter than pattern: pad remaining bytes with SPACE_TILE.
 * Replacement longer  than pattern: write as many bytes as fit within the
 * original pattern slot (extra bytes silently dropped).
 */
void text_override_apply(void) {
    if (s_num_overrides == 0) return;

    uint8_t rd = g_ram[BUF_RD_PTR];
    uint8_t wr = g_ram[BUF_WR_PTR];
    if (rd == wr) return;

    uint8_t pos      = rd;
    int     max_iter = 256;

    while (pos != wr && max_iter-- > 0) {
        uint8_t count_raw = g_ram[BUF_BASE + pos];

        if (count_raw >= SPECIAL_FIRST) {
            pos = buf_advance(pos, 3);
            continue;
        }

        uint8_t count = count_raw & 0x7Fu;
        if (count == 0) {
            pos = buf_advance(pos, 3);
            continue;
        }

        uint8_t tile_base = buf_advance(pos, 3);

        for (int oi = 0; oi < s_num_overrides; oi++) {
            TextOverride *o    = &s_overrides[oi];
            int           plen = o->pattern_len;
            if (plen > (int)count) continue;

            for (int t = 0; t <= (int)count - plen; t++) {
                uint8_t tile_pos = buf_advance(tile_base, (uint8_t)t);

                int match = 1;
                for (int k = 0; k < plen && match; k++) {
                    if (g_ram[BUF_BASE + buf_advance(tile_pos, (uint8_t)k)] != o->pattern[k])
                        match = 0;
                }
                if (!match) continue;

                int rlen  = o->replacement_len;
                int write = (rlen < plen) ? rlen : plen;
                for (int k = 0; k < write; k++)
                    g_ram[BUF_BASE + buf_advance(tile_pos, (uint8_t)k)] = o->replacement[k];
                for (int k = write; k < plen; k++)
                    g_ram[BUF_BASE + buf_advance(tile_pos, (uint8_t)k)] = SPACE_TILE;

                o->hit_count++;
            }
        }

        pos = buf_advance(pos, (uint8_t)(3 + count));
    }
}

/* ======================================================================
 * Diagnostics
 * ====================================================================== */

void text_override_dump_buffer(tile_encode_fn encode) {
    (void)encode;

    uint8_t rd = g_ram[BUF_RD_PTR];
    uint8_t wr = g_ram[BUF_WR_PTR];

    printf("[TextOverride] buffer rd=0x%02x wr=0x%02x\n", rd, wr);
    if (rd == wr) {
        printf("[TextOverride]   (empty)\n");
        return;
    }

    uint8_t pos   = rd;
    int     idx   = 0;
    int     limit = 256;

    while (pos != wr && limit-- > 0) {
        uint8_t count_raw = g_ram[BUF_BASE + pos];

        if (count_raw >= SPECIAL_FIRST) {
            printf("[TextOverride]   [%d] SPECIAL 0x%02x param=0x%02x,0x%02x\n",
                   idx, count_raw,
                   g_ram[BUF_BASE + buf_advance(pos, 1)],
                   g_ram[BUF_BASE + buf_advance(pos, 2)]);
            pos = buf_advance(pos, 3);
            idx++;
            continue;
        }

        uint8_t count   = count_raw & 0x7Fu;
        uint8_t addr_hi = g_ram[BUF_BASE + buf_advance(pos, 1)];
        uint8_t addr_lo = g_ram[BUF_BASE + buf_advance(pos, 2)];

        printf("[TextOverride]   [%d] TILES count=%u ppu=0x%04x flags=0x%02x tiles=",
               idx, count, ((uint16_t)addr_hi << 8) | addr_lo, count_raw & 0x80u);

        uint8_t tile_pos = buf_advance(pos, 3);
        for (uint8_t k = 0; k < count; k++)
            printf("%02x ", g_ram[BUF_BASE + buf_advance(tile_pos, k)]);
        printf("\n");

        pos = buf_advance(pos, (uint8_t)(3 + count));
        idx++;
    }
}
