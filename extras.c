/*
 * games/faxanadu/extras.c — Faxanadu-specific runner hooks
 *
 * Implements game_extras.h for Faxanadu.
 * Features:
 *   --password   Auto-injects a mantra into the RAM buffer on the password screen.
 *   Auto-load    Loads the most recent mantra from saves.txt on startup.
 */
#include "game_extras.h"
#include "nes_runtime.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

/* ---- Password state ---- */
static const char *s_password          = NULL;
static int         s_password_injected = 0;
static int         s_password_from_cli = 0;  /* 1 if --password was given on CLI */

/* ---- Auto-load state ---- */
static char    s_loaded_password[25];   /* password loaded from saves.txt */

/* Returns the mantra table index (0-63) for a character, or -1 if invalid.
 * Bank12 $8764 table order: A-Z (0-25), a-z (26-51), 0-9 (52-61), ',' (62), '?' (63) */
static int password_char_to_index(char ch) {
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';
    if (ch >= 'a' && ch <= 'z') return 26 + (ch - 'a');
    if (ch >= '0' && ch <= '9') return 52 + (ch - '0');
    if (ch == ',') return 62;
    if (ch == '?') return 63;
    return -1;
}

/* ---- Path helper ---- */

/* Build path: <exe_dir>/filename. Same pattern as launcher.c:get_rom_cfg_path(). */
static void get_exe_relative_path(const char *filename, char *out, int max_len) {
#ifdef _WIN32
    char exe_path[MAX_PATH];
    GetModuleFileNameA(NULL, exe_path, MAX_PATH);
    char *last_sep = strrchr(exe_path, '\\');
    if (last_sep) *(last_sep + 1) = '\0';
    snprintf(out, max_len, "%s%s", exe_path, filename);
#else
    snprintf(out, max_len, "%s", filename);
#endif
}

/* ---- saves.txt I/O ---- */

/* Read the first line of saves.txt into s_loaded_password[].
 * Validates that every character is a valid password character.
 * Returns 1 on success, 0 if no valid password found. */
static int load_password_from_file(void) {
    char path[512];
    get_exe_relative_path("saves.txt", path, sizeof(path));

    FILE *f = fopen(path, "r");
    if (!f) return 0;

    char line[256];
    if (!fgets(line, sizeof(line), f)) { fclose(f); return 0; }
    fclose(f);

    /* Strip trailing newline/carriage return */
    int len = (int)strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        line[--len] = '\0';

    if (len == 0 || len > 24) return 0;

    /* Validate every character */
    for (int i = 0; i < len; i++) {
        if (password_char_to_index(line[i]) < 0) return 0;
    }

    memcpy(s_loaded_password, line, len + 1);
    return 1;
}

/* ---- Inject password into the mantra entry RAM buffer ---- */
/* Detection (Ghidra bank12 analysis):
 *   $0665 == len  — max-length register set to our password length
 *   $0666 == 0    — no characters entered yet (fresh screen)
 *   $0600 == 0xFF — first slot is empty sentinel
 * Writes character table indices to $0600+i, sets $0664 = $0666 = len. */
static void maybe_inject_password(void) {
    if (!s_password || s_password_injected) return;

    /* Strip spaces (sometimes shown as separators online) */
    static char s_pw_stripped[25];
    int slen = 0;
    for (const char *p = s_password; *p && slen < 24; p++)
        if (*p != ' ') s_pw_stripped[slen++] = *p;
    s_pw_stripped[slen] = '\0';
    s_password = s_pw_stripped;

    int len = (int)strlen(s_password);
    if (len == 0 || len > 24) return;

    uint8_t max_len = g_ram[0x665];
    if (max_len == 0)         return;   /* screen not initialized yet */
    if (g_ram[0x666] != 0)   return;   /* something already entered */
    if (g_ram[0x600] != 0xFF) return;  /* first slot not empty */

    for (int i = 0; i < len; i++) {
        int idx = password_char_to_index(s_password[i]);
        if (idx < 0) {
            fprintf(stderr, "[Password] Unknown char '%c' at pos %d — aborted\n",
                    s_password[i], i);
            return;
        }
        g_ram[0x600 + i] = (uint8_t)idx;
    }
    for (int i = len; i < (int)max_len; i++)
        g_ram[0x600 + i] = 0xFF;   /* fill remaining slots with empty sentinel */

    g_ram[0x664] = (uint8_t)len;   /* cursor: positioned after last entered char */
    g_ram[0x666] = (uint8_t)len;   /* characters-entered count */

    /* Queue PPU tile writes so the characters appear on screen.
     * $0500 DMA queue format: [count(1 byte), addr_hi, addr_lo, tile...]
     * Queue write-ptr at $0020. Tiles are ASCII values (bank12 $8764 maps index→ASCII).
     * Row 0 (positions 0-15):  PPU $2129+pos
     * Row 1 (positions 16-31): PPU $2149+(pos-16) */
    for (int i = 0; i < len; i++) {
        uint8_t ppu_lo = (i < 16) ? (0x28 + i) : (0x48 + (i - 16));
        uint8_t tile   = (uint8_t)s_password[i];   /* ASCII = PPU tile number */
        uint8_t wp     = g_ram[0x20];
        g_ram[0x500 + wp++] = 0x01;   /* 1 tile */
        g_ram[0x500 + wp++] = 0x21;   /* PPU addr hi */
        g_ram[0x500 + wp++] = ppu_lo;
        g_ram[0x500 + wp++] = tile;
        g_ram[0x20] = wp;
    }

    s_password_injected = 1;
    printf("[Password] Injected \"%s\" (%d chars)\n", s_password, len);
}

/* ---- game_extras.h implementation ---- */

uint32_t game_get_expected_crc32(void) { return 0x42C4EC66u; }

const char *game_get_name(void) { return "Faxanadu"; }

void game_on_init(void) {
    /* If no --password CLI flag, try loading from saves.txt */
    if (!s_password_from_cli) {
        if (load_password_from_file()) {
            s_password = s_loaded_password;
            printf("[Password] Loaded mantra from saves.txt: \"%s\"\n", s_loaded_password);
        }
    }
}

void game_on_frame(uint64_t frame_count) {
    (void)frame_count;
    maybe_inject_password();
}

void game_post_nmi(uint64_t frame_count) {
    (void)frame_count;
}

int game_handle_arg(const char *key, const char *val) {
    if (strcmp(key, "--password") == 0 && val) {
        s_password = val;
        s_password_from_cli = 1;
        printf("[Password] Will auto-fill mantra: \"%s\"\n", val);
        return 1;
    }
    return 0;
}

const char *game_arg_usage(void) {
    return "  --password STRING   Auto-fill Faxanadu mantra on password screen\n";
}
