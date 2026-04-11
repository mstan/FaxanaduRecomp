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
 *     Game-defined dispatch (e.g. fog animation rotation).
 *     We skip these — do not modify.
 *
 *   Read  pointer: g_ram[0x1F] (incremented by NMI drain)
 *   Write pointer: g_ram[0x20] (incremented by game code)
 *   Both are 8-bit; the buffer wraps within the 256-byte $0500 page.
 *
 * Scanning: walk read_ptr..write_ptr (with 8-bit wrap), parse each packet,
 *   search tile payload for registered patterns, replace in-place.
 */

#include "override_text.h"
#include "nes_runtime.h"   /* g_ram[] */

#include <string.h>
#include <stdio.h>

/* ---- NES DMA buffer constants ----------------------------------------- */

#define BUF_BASE      0x500u  /* base address of PPU DMA buffer in RAM     */
#define BUF_RD_PTR    0x1Fu   /* RAM address: current read  pointer (1 byte) */
#define BUF_WR_PTR    0x20u   /* RAM address: current write pointer (1 byte) */
#define SPACE_TILE    0x20u   /* tile byte for ASCII space — used as pad     */
#define SPECIAL_FIRST 0xFAu   /* first special-command opcode (skip)        */

/* ---- Override table ---------------------------------------------------- */

typedef struct {
    uint8_t pattern[TEXT_OVERRIDE_MAX_LEN];
    uint8_t replacement[TEXT_OVERRIDE_MAX_LEN];
    int     pattern_len;
    int     replacement_len;
    int     hit_count;          /* diagnostic: times this override fired  */
} TextOverride;

static TextOverride s_overrides[TEXT_OVERRIDE_MAX];
static int          s_num_overrides = 0;

/* ---- Lifecycle --------------------------------------------------------- */

void text_override_init(void) {
    s_num_overrides = 0;
}

/* ---- Registration (raw tile bytes) ------------------------------------- */

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

/* ---- Registration (ASCII + encoder) ------------------------------------ */

int text_override_register_ascii(const char *original, const char *override_str,
                                  tile_encode_fn encode) {
    uint8_t pat[TEXT_OVERRIDE_MAX_LEN];
    uint8_t rep[TEXT_OVERRIDE_MAX_LEN];
    int     pat_len = 0, rep_len = 0;

    for (const char *p = original; *p; p++) {
        if (pat_len >= TEXT_OVERRIDE_MAX_LEN) return 0;
        uint8_t t = encode(*p);
        if (t == 0xFF) return 0;  /* unencodable character */
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

/* ---- Buffer walk helpers ----------------------------------------------- */

/* Advance an 8-bit buffer pointer by n bytes (wraps within 256). */
static inline uint8_t buf_advance(uint8_t ptr, uint8_t n) {
    return (uint8_t)(ptr + n);
}

/* Return 1 if ptr is within [rd, wr) with 8-bit wrap. */
static inline int buf_in_range(uint8_t ptr, uint8_t rd, uint8_t wr) {
    if (rd <= wr)
        return ptr >= rd && ptr < wr;
    /* wrapped: rd > wr means the range crosses the 256 boundary */
    return ptr >= rd || ptr < wr;
}

/* ---- Apply overrides --------------------------------------------------- */

/*
 * Walk every packet in the $0500 buffer between the current read and write
 * pointers.  For each normal packet, search its tile payload for every
 * registered pattern and replace it in-place.
 *
 * Replacement shorter than pattern: pad remaining bytes with SPACE_TILE.
 * Replacement longer  than pattern: write as many bytes as fit within the
 * original pattern slot (remaining bytes are silently dropped — the caller
 * should choose replacement lengths ≤ pattern length for lossless overrides,
 * or ensure the surrounding nametable has room and extend count separately).
 */
void text_override_apply(void) {
    if (s_num_overrides == 0) return;

    uint8_t rd = g_ram[BUF_RD_PTR];
    uint8_t wr = g_ram[BUF_WR_PTR];

    if (rd == wr) return;  /* buffer empty */

    uint8_t pos = rd;

    /* Safety: limit iterations to avoid infinite loop if buffer is corrupt. */
    int max_iter = 256;

    while (pos != wr && max_iter-- > 0) {
        uint8_t count_raw = g_ram[BUF_BASE + pos];

        /* Special command ($FA–$FF): we don't know the payload size reliably.
         * These are 3-byte commands (opcode + 2 params) — skip safely. */
        if (count_raw >= SPECIAL_FIRST) {
            pos = buf_advance(pos, 3);
            continue;
        }

        /* Normal packet: count & 0x7F = number of tile bytes */
        uint8_t count = count_raw & 0x7Fu;

        /* Packet is 3 header bytes + count tile bytes */
        if (count == 0) {
            pos = buf_advance(pos, 3);
            continue;
        }

        /* tile_base: buffer offset of first tile byte in this packet */
        uint8_t tile_base = buf_advance(pos, 3);

        /* Try every registered override against this packet's tile payload. */
        for (int oi = 0; oi < s_num_overrides; oi++) {
            TextOverride *o = &s_overrides[oi];
            int           plen = o->pattern_len;

            if (plen > (int)count) continue;  /* pattern longer than packet */

            /* Slide the pattern over every position in the tile payload. */
            for (int t = 0; t <= (int)count - plen; t++) {
                uint8_t tile_pos = buf_advance(tile_base, (uint8_t)t);

                /* Check match. */
                int match = 1;
                for (int k = 0; k < plen && match; k++) {
                    if (g_ram[BUF_BASE + buf_advance(tile_pos, (uint8_t)k)]
                            != o->pattern[k]) {
                        match = 0;
                    }
                }
                if (!match) continue;

                /* Replace. */
                int rlen   = o->replacement_len;
                int write  = (rlen < plen) ? rlen : plen;  /* bytes to copy */

                for (int k = 0; k < write; k++) {
                    g_ram[BUF_BASE + buf_advance(tile_pos, (uint8_t)k)]
                        = o->replacement[k];
                }
                /* Pad remainder with space tile if replacement is shorter. */
                for (int k = write; k < plen; k++) {
                    g_ram[BUF_BASE + buf_advance(tile_pos, (uint8_t)k)]
                        = SPACE_TILE;
                }

                o->hit_count++;
            }
        }

        /* Advance past this packet. */
        pos = buf_advance(pos, (uint8_t)(3 + count));
    }
}

/* ---- ROM-level patching ------------------------------------------------ */

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

int text_override_patch_prg_ascii(int bank, uint16_t prg_addr,
                                   int original_len,
                                   const char *replacement,
                                   tile_encode_fn encode) {
    uint8_t buf[TEXT_OVERRIDE_MAX_LEN];
    int     rep_len = 0;

    for (const char *p = replacement; *p; p++) {
        if (rep_len >= TEXT_OVERRIDE_MAX_LEN) return 0;
        uint8_t t = encode(*p);
        if (t == 0xFF) return 0;
        buf[rep_len++] = t;
    }
    if (rep_len == 0) return 0;

    /* Encode replacement into a zero-padded buffer the same length as original
     * so we don't corrupt adjacent string data. */
    uint8_t patched[TEXT_OVERRIDE_MAX_LEN];
    memset(patched, SPACE_TILE, (size_t)original_len);
    int copy = (rep_len < original_len) ? rep_len : original_len;
    memcpy(patched, buf, (size_t)copy);
    /* Keep the null terminator in place if replacement is shorter. */
    if (rep_len < original_len)
        patched[rep_len] = 0x00;

    text_override_patch_prg(bank, prg_addr, patched, original_len);
    return 1;
}

/* ---- Diagnostics ------------------------------------------------------- */

void text_override_dump_buffer(tile_encode_fn encode) {
    (void)encode;  /* unused for now — decode tile→char not implemented here */

    uint8_t rd = g_ram[BUF_RD_PTR];
    uint8_t wr = g_ram[BUF_WR_PTR];

    printf("[TextOverride] buffer rd=0x%02x wr=0x%02x\n", rd, wr);
    if (rd == wr) {
        printf("[TextOverride]   (empty)\n");
        return;
    }

    uint8_t pos  = rd;
    int     idx  = 0;
    int     limit = 256;

    while (pos != wr && limit-- > 0) {
        uint8_t count_raw = g_ram[BUF_BASE + pos];

        if (count_raw >= SPECIAL_FIRST) {
            uint8_t p1 = g_ram[BUF_BASE + buf_advance(pos, 1)];
            uint8_t p2 = g_ram[BUF_BASE + buf_advance(pos, 2)];
            printf("[TextOverride]   [%d] SPECIAL 0x%02x param=0x%02x,0x%02x\n",
                   idx, count_raw, p1, p2);
            pos = buf_advance(pos, 3);
            idx++;
            continue;
        }

        uint8_t count    = count_raw & 0x7Fu;
        uint8_t addr_hi  = g_ram[BUF_BASE + buf_advance(pos, 1)];
        uint8_t addr_lo  = g_ram[BUF_BASE + buf_advance(pos, 2)];
        uint16_t ppu_addr = ((uint16_t)addr_hi << 8) | addr_lo;

        printf("[TextOverride]   [%d] TILES count=%u ppu=0x%04x flags=0x%02x tiles=",
               idx, count, ppu_addr, count_raw & 0x80u);

        uint8_t tile_pos = buf_advance(pos, 3);
        for (uint8_t k = 0; k < count; k++) {
            printf("%02x ", g_ram[BUF_BASE + buf_advance(tile_pos, k)]);
        }
        printf("\n");

        pos = buf_advance(pos, (uint8_t)(3 + count));
        idx++;
    }
}
