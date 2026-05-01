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
#include "debug_server.h"
#include "verify_mode.h"
#include "input_script.h"
#include "override_text.h"
#include "override_chr.h"
#ifdef ENABLE_NESTOPIA_ORACLE
#include "nestopia_bridge.h"
#endif
#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

/* ---- Watchdog globals (extern'd by runner's debug_server.c) ---- */
int         g_watchdog_triggered = 0;
uint32_t    g_watchdog_frame     = 0;
const char *g_watchdog_stack_dump = "";

/* ---- Debug mode ---- */
static int s_debug_enabled = 0;
static void get_exe_relative_path(const char *filename, char *out, int max_len);

static int check_debug_ini(void) {
    char path[512];
    get_exe_relative_path("debug.ini", path, sizeof(path));
    FILE *f = fopen(path, "r");
    if (f) { fclose(f); return 1; }
    return 0;
}

/* ---- Debug server state ---- */
static int s_tcp_port = 4370;

/* ROM path exposed by runner for verify mode init */
const char *g_rom_path_for_extras = NULL;

/* ---- Text override: Faxanadu tile encodings ---- */

/* FAXANADU_1 — title/menu text.  A=0xE0, space=0x20.  Null-terminated. */
static uint8_t fax_tile_encode(char ch) {
    if (ch >= 'A' && ch <= 'Z') return (uint8_t)(0xE0 + (ch - 'A'));
    if (ch == ' ')               return 0x20;
    return 0xFF;  /* unencodable */
}

/* FAXANADU_DIALOGUE — NPC dialogue text.  Plain ASCII printable characters
 * map to themselves.  Space maps to 0xFD (word space token).  '\n' maps to
 * 0xFC (line break within dialogue box).  Terminated by 0xFF. */
static uint8_t fax_dialogue_encode(char ch) {
    if (ch >= 0x21 && ch <= 0x7E) return (uint8_t)ch;  /* printable ASCII */
    if (ch == ' ')                return 0xFD;           /* word space */
    if (ch == '\n')               return 0xFC;           /* line break */
    return 0xFF;  /* unencodable */
}

/* ASCII — plain null-terminated ASCII (Mantra screen, etc.). */
static uint8_t ascii_encode(char ch) {
    if (ch >= 0x20 && ch <= 0x7E) return (uint8_t)ch;
    return 0xFF;  /* unencodable */
}

/* Path to the JSON override table.  Default = CWD-relative so the file lives
 * wherever the user launches the game from.  Override with --text-overrides. */
static char s_text_overrides_path[512] = "text_overrides.json";
static int  s_text_overrides_enabled = 0;  /* opt-in via --text-overrides */

static void text_override_setup(void) {
    text_override_init();

    /* Register all Faxanadu text encodings.  Each carries its own terminator
     * byte so the override system writes the correct end-of-string marker. */
    text_override_register_encoding("FAXANADU_1",        fax_tile_encode,     0x00);
    text_override_register_encoding("FAXANADU_DIALOGUE", fax_dialogue_encode, 0xFF);
    text_override_register_encoding("ASCII",             ascii_encode,        0x00);

    /* Load overrides from the JSON table (CWD by default, see --text-overrides).
     * Edit that file while the game runs; changes hot-reload within ~1 second. */
    text_override_load_json(s_text_overrides_path);
}

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

uint32_t game_get_expected_crc32(void) { return 0x57DD23D1u; }

const char *game_get_name(void) { return "Faxanadu"; }

/* CHR override — opt-in via --chr-overrides or --chr-dump. */
static char s_chr_overrides_dir[512] = "tiles";
static char s_tile_compile_dir[512] = "";
static int  s_tile_compile = 0;
static int  s_chr_dump = 0;
static int  s_chr_enabled = 0;       /* set by --chr-overrides or --chr-dump */
static int  s_chr_overrides_set = 0; /* explicitly passed --chr-overrides */

void game_on_init(void) {
    /* --tile-compile: batch convert PNGs to .chr.bin, then exit */
    if (s_tile_compile) {
        int n = chr_override_compile_dir(s_tile_compile_dir);
        printf("[ChrOverride] Compiled %d PNGs in %s\n", n, s_tile_compile_dir);
        exit(0);
    }

    /* Text override plugin — opt-in via --text-overrides */
    if (s_text_overrides_enabled)
        text_override_setup();

    /* Auto-detect tiles/manifest.json next to exe (like debug.ini) */
    if (!s_chr_enabled) {
        char tiles_manifest[512];
        get_exe_relative_path("tiles/manifest.json", tiles_manifest, sizeof(tiles_manifest));
        FILE *tf = fopen(tiles_manifest, "r");
        if (tf) {
            fclose(tf);
            s_chr_enabled = 1;
            s_chr_overrides_set = 1;
            get_exe_relative_path("tiles", s_chr_overrides_dir, sizeof(s_chr_overrides_dir));
            printf("[ChrOverride] Auto-detected tiles/manifest.json\n");
        }
    }

    /* Tile override plugin — via CLI or auto-detect */
    if (s_chr_enabled) {
        chr_override_init();
        if (s_chr_dump)
            chr_override_set_dump(1);
        if (s_chr_overrides_set)
            chr_override_load_manifest(s_chr_overrides_dir);
    }

    s_debug_enabled = check_debug_ini();

    if (s_debug_enabled) {
        printf("[Debug] debug.ini found — TCP server and verify mode enabled\n");
        debug_server_init(s_tcp_port);

        if (g_run_mode != RUN_MODE_NATIVE && g_rom_path_for_extras) {
            verify_mode_init(g_rom_path_for_extras);
        }
    } else if (g_run_mode != RUN_MODE_NATIVE) {
        /* --verify or --emulated implies debug even without ini */
        s_debug_enabled = 1;
        debug_server_init(s_tcp_port);
        if (g_rom_path_for_extras)
            verify_mode_init(g_rom_path_for_extras);
    }

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
    if (s_debug_enabled) {
        debug_server_poll();
        debug_server_wait_if_paused();
        int ovr = debug_server_get_input_override();
        if (ovr >= 0)
            g_controller1_buttons = (uint8_t)ovr;
    }

    if (s_text_overrides_enabled) {
        text_override_reload_if_changed();
        text_override_apply();
    }

    if (s_chr_enabled)
        chr_override_reload_if_changed();

    maybe_inject_password();
}

void game_post_nmi(uint64_t frame_count) {
    (void)frame_count;

    if (s_chr_enabled)
        chr_override_frame_end();

    if (s_debug_enabled) {
        debug_server_record_frame();
    }
}

int game_handle_arg(const char *key, const char *val) {
    if (strcmp(key, "--text-overrides") == 0 && val) {
        strncpy(s_text_overrides_path, val, sizeof(s_text_overrides_path) - 1);
        s_text_overrides_path[sizeof(s_text_overrides_path) - 1] = '\0';
        s_text_overrides_enabled = 1;
        printf("[TextOverride] Override path set to \"%s\"\n", val);
        return 1;
    }
    if (strcmp(key, "--tile-dump") == 0) {
        s_chr_dump = 1;
        s_chr_enabled = 1;
        printf("[ChrOverride] Tile dump enabled\n");
        return 1;
    }
    if (strcmp(key, "--tiles") == 0 && val) {
        strncpy(s_chr_overrides_dir, val, sizeof(s_chr_overrides_dir) - 1);
        s_chr_overrides_dir[sizeof(s_chr_overrides_dir) - 1] = '\0';
        s_chr_enabled = 1;
        s_chr_overrides_set = 1;
        printf("[ChrOverride] Tile dir set to \"%s\"\n", val);
        return 1;
    }
    if (strcmp(key, "--tile-compile") == 0 && val) {
        strncpy(s_tile_compile_dir, val, sizeof(s_tile_compile_dir) - 1);
        s_tile_compile_dir[sizeof(s_tile_compile_dir) - 1] = '\0';
        s_tile_compile = 1;
        printf("[ChrOverride] Tile compile dir: \"%s\"\n", val);
        return 1;
    }
    if (strcmp(key, "--password") == 0 && val) {
        s_password = val;
        s_password_from_cli = 1;
        printf("[Password] Will auto-fill mantra: \"%s\"\n", val);
        return 1;
    }
    if (strcmp(key, "--tcp-port") == 0 && val) {
        s_tcp_port = atoi(val);
        printf("[Debug] TCP port set to %d\n", s_tcp_port);
        return 1;
    }
    if (strcmp(key, "--verify") == 0) {
        g_run_mode = RUN_MODE_VERIFY;
        printf("[Verify] Dual-execution verify mode enabled\n");
        return 1;
    }
    if (strcmp(key, "--emulated") == 0) {
        g_run_mode = RUN_MODE_EMULATED;
        printf("[Verify] FCEUX emulated mode enabled\n");
        return 1;
    }
    return 0;
}

const char *game_arg_usage(void) {
    return "  --text-overrides PATH  Path to text_overrides.json (default: ./text_overrides.json)\n"
           "  --tile-dump            Dump unique CHR transfers as PNGs to tiles/\n"
           "  --tiles DIR            Path to tile override directory (default: ./tiles)\n"
           "  --tile-compile DIR     Batch convert all PNGs in DIR to .chr.bin cache files\n"
           "  --password STRING   Auto-fill Faxanadu mantra on password screen\n"
           "  --tcp-port PORT     TCP debug server port (default 4370)\n"
           "  --verify            Enable dual-execution verify mode (FCEUX oracle)\n"
           "  --emulated          Run purely via FCEUX emulator (no recompiled code)\n";
}

void game_run_nmi(void) {
    verify_mode_run_nmi();
}

void game_run_main(void) {
    if (g_run_mode == RUN_MODE_EMULATED) {
#ifdef ENABLE_NESTOPIA_ORACLE
        /* Nestopia drives the entire execution — its own CPU, PPU, APU. */
        printf("[Emulated] Nestopia driving main loop\n");

        static uint32_t fceux_argb[256 * 240];  /* ARGB framebuffer */

        extern void runner_present_framebuf(const uint32_t *argb_buf);

        for (;;) {
            /* Poll SDL events */
            {
                SDL_Event ev;
                while (SDL_PollEvent(&ev)) {
                    if (ev.type == SDL_QUIT) exit(0);
                    if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_ESCAPE) exit(0);
                    if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_F5)
                        g_turbo ^= 1;
                }

                /* Read keyboard for controller input */
                const uint8_t *keys = SDL_GetKeyboardState(NULL);
                uint8_t btn = 0;
                if (keys[SDL_SCANCODE_Z])      btn |= 0x80;
                if (keys[SDL_SCANCODE_X])      btn |= 0x40;
                if (keys[SDL_SCANCODE_TAB])    btn |= 0x20;
                if (keys[SDL_SCANCODE_RETURN]) btn |= 0x10;
                if (keys[SDL_SCANCODE_UP])     btn |= 0x08;
                if (keys[SDL_SCANCODE_DOWN])   btn |= 0x04;
                if (keys[SDL_SCANCODE_LEFT])   btn |= 0x02;
                if (keys[SDL_SCANCODE_RIGHT])  btn |= 0x01;
                g_controller1_buttons = btn;
            }

            /* Debug server */
            debug_server_poll();
            debug_server_wait_if_paused();

            /* Run one FCEUX frame (FCEUX's own PPU renders internally) */
            nestopia_bridge_run_frame(g_controller1_buttons);

            /* Get FCEUX's rendered framebuffer (palette indices) and palette */
            nestopia_bridge_get_framebuf_argb(fceux_argb);

            /* Present FCEUX's frame directly to SDL window */
            runner_present_framebuf(fceux_argb);

            /* Also extract RAM state for debug server queries */
            nestopia_bridge_get_ram(g_ram);
            nestopia_bridge_get_sram(g_sram);
            g_frame_count++;

            /* Record frame for debug server */
            debug_server_record_frame();

            /* Frame pacing: ~60fps */
            if (!g_turbo) SDL_Delay(16);
        }
#else
        fprintf(stderr, "[Error] FCEUX not compiled in, falling back to native\n");
        func_RESET();
#endif
    } else {
        /* Native or verify mode: func_RESET() drives the main loop,
         * NMI fires via nes_vblank_callback → game_run_nmi(). */
        func_RESET();
    }
}

int game_dispatch_override(uint16_t addr) { (void)addr; return 0; }

uint8_t game_ram_read_hook(uint16_t pc, uint16_t addr, uint8_t val) {
    (void)pc; (void)addr; return val;
}

/* ---- Debug server game hooks ---- */

void game_fill_frame_record(void *record) {
    NESFrameRecord *r = (NESFrameRecord *)record;
    r->game_data[0] = g_ram[0x12];    /* game_mode */
    r->game_data[1] = g_ram[0xEB];    /* room_id */
    r->game_data[2] = g_ram[0x0394];  /* player_hp */
    r->game_data[3] = g_ram[0x035C];  /* player_gold_lo */
    r->game_data[4] = g_ram[0x035D];  /* player_gold_hi */
}

void game_post_render(uint32_t *framebuf) { (void)framebuf; }

int game_handle_debug_cmd(const char *cmd, int id, const char *json) {
    (void)json;

    if (strcmp(cmd, "faxanadu_state") == 0) {
        debug_server_send_fmt(
            "{\"id\":%d,\"ok\":true,"
            "\"game_mode\":\"0x%02X\",\"room\":\"0x%02X\","
            "\"player_hp\":%d,\"player_max_hp\":%d,"
            "\"gold\":%d,"
            "\"scroll_x\":%d,\"scroll_y\":%d,"
            "\"frame\":%llu}",
            id,
            g_ram[0x12], g_ram[0xEB],
            g_ram[0x0394], g_ram[0x0396],
            g_ram[0x035C] | (g_ram[0x035D] << 8),
            g_ppuscroll_x, g_ppuscroll_y,
            (unsigned long long)g_frame_count);
        return 1;
    }

    if (strcmp(cmd, "entity_table") == 0) {
        /* Faxanadu entities live at $0300-$03FF area.
         * Entity type at $0300+i, state at $0310+i, X at $0320+i, Y at $0330+i.
         * 16 entity slots. */
        char *buf = (char *)malloc(4096);
        if (!buf) {
            debug_server_send_fmt("{\"id\":%d,\"ok\":false,\"error\":\"alloc failed\"}", id);
            return 1;
        }

        int pos = snprintf(buf, 128, "{\"id\":%d,\"ok\":true,\"entities\":[", id);
        int first = 1;
        for (int i = 0; i < 16; i++) {
            uint8_t type = g_ram[0x0300 + i];
            if (type == 0) continue;  /* empty slot */
            if (!first) buf[pos++] = ',';
            first = 0;
            pos += snprintf(buf + pos, 128,
                "{\"slot\":%d,\"type\":\"0x%02X\",\"state\":\"0x%02X\","
                "\"x\":%d,\"y\":%d}",
                i, type, g_ram[0x0310 + i],
                g_ram[0x0320 + i], g_ram[0x0330 + i]);
        }
        pos += snprintf(buf + pos, 8, "]}");
        debug_server_send_line(buf);
        free(buf);
        return 1;
    }

    return 0;
}
