/* Faxanadu's mantra saves on the cycle host. Capture uses the ROM's encoder
 * on a complete isolated machine; only the resulting text leaves the scope. */
#include "cyc_host_extras.h"
#include "cyc_mod.h"
#include "cyc_core.h"
#include "override_text.h"
#include "override_chr.h"
#include "mods/zelda2/fax_link.h"
#include "fax_world.h"
#ifdef CYC_WITH_SDL
#include "cyc_tcp.h"
#include <SDL.h>
#endif
#include <string.h>
#include <time.h>
#include <stdlib.h>

static char password[25], saved[25];
static bool password_cli, injected, history_started;
static uint64_t frame;
static bool text_enabled, tiles_enabled, tile_dump;
static char text_path[1100] = "text_overrides.json", tiles_path[1100] = "tiles", compile_path[1100];

static uint8_t title_encode(char ch) {
    return ch >= 'A' && ch <= 'Z' ? (uint8_t)(0xE0 + ch - 'A') : ch == ' ' ? 0x20 : 0xFF;
}
static uint8_t dialogue_encode(char ch) {
    return ch >= 0x21 && ch <= 0x7E ? (uint8_t)ch : ch == ' ' ? 0xFD : ch == '\n' ? 0xFC : 0xFF;
}
static uint8_t ascii_encode(char ch) { return ch >= 0x20 && ch <= 0x7E ? (uint8_t)ch : 0xFF; }

static int char_index(char ch) {
    if (ch >= 'A' && ch <= 'Z') return ch - 'A';
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 26;
    if (ch >= '0' && ch <= '9') return ch - '0' + 52;
    return ch == ',' ? 62 : ch == '?' ? 63 : -1;
}
static char index_char(int i) {
    return "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789,?"[i];
}
static bool parse_password(const char *s, char out[25]) {
    char tmp[25]; int n = 0;
    for (; *s; ++s) {
        if (*s == ' ') continue;
        if (n == 24 || char_index(*s) < 0) return false;
        tmp[n++] = *s;
    }
    if (!n) return false;
    tmp[n] = 0;
    memcpy(out, tmp, (size_t)n + 1);
    return true;
}
static bool sidecar_path(const char *name, char out[1100]) {
#ifdef CYC_WITH_SDL
    char *base = SDL_GetBasePath();
    if (!base) return false;
    int n = snprintf(out, 1100, "%s%s", base, name);
    SDL_free(base);
#else
    int n = snprintf(out, 1100, "%s", name);
#endif
    return n > 0 && n < 1100;
}
static bool read_password(const char *name, char out[25]) {
    char path[1100], line[128];
    if (!sidecar_path(name, path)) return false;
    FILE *f = fopen(path, "r");
    if (!f) return false;
    bool ok = fgets(line, sizeof(line), f) != NULL;
    fclose(f);
    if (!ok) return false;
    line[strcspn(line, "\r\n")] = 0;
    return parse_password(line, out);
}

static bool generate_mantra(char out[25]) {
    out[0] = 0;
    if (!cyc_mod_isolate_begin()) return false;
    CycModRegs regs;
    cyc_mod_regs(&regs);
    regs.x = 12;               /* fixed-bank MMC1 switch: 16 KiB PRG bank 12 */
    bool ok = cyc_mod_call(0xCC1A, &regs);
    if (ok) ok = cyc_mod_call(0x96FE, &regs);
    int count = ok ? cyc_mod_peek(0x04CB) : 0;
    ok = count > 0 && count <= 24;
    if (ok) {
        for (int c = 0; c < count; ++c) {
            int idx = 0;
            for (int b = 0; b < 6; ++b) {
                int bit = c * 6 + b;
                idx = (idx << 1) | ((cyc_mod_peek((uint16_t)(0x04CD + bit / 8)) >> (7 - bit % 8)) & 1);
            }
            out[c] = index_char(idx);
        }
        out[count] = 0;
    }
    cyc_mod_isolate_end();
    return ok;
}
static bool save_mantra(const char *mantra) {
    if (!cyc_host_saves_enabled()) return false;
    if (!strcmp(mantra, saved)) return true;
    char path[1100], temp[1120];
    if (!sidecar_path("faxanadu.srm", path)) return false;
    snprintf(temp, sizeof(temp), "%s.tmp", path);
    FILE *f = fopen(temp, "w");
    if (!f) return false;
    bool ok = fprintf(f, "%s\n", mantra) > 0;
    if (fclose(f) != 0) ok = false;
#ifdef _WIN32
    /* SDL's replacement helper is not available; the shared save helper uses
     * the Windows atomic replace below too. Never truncate the previous save. */
    if (ok) {
        extern bool faxanadu_replace_file(const char *, const char *);
        ok = faxanadu_replace_file(temp, path);
    }
#else
    if (ok) ok = rename(temp, path) == 0;
#endif
    if (!ok) { remove(temp); return false; }
    snprintf(saved, sizeof(saved), "%s", mantra);
    snprintf(password, sizeof(password), "%s", mantra);
    injected = false;
    if (sidecar_path("faxanadu_mantra_log.txt", path)) {
        f = fopen(path, "a");
        if (f) {
            time_t now = time(NULL); struct tm *lt = localtime(&now);
            char stamp[32] = "unknown time";
            if (lt) strftime(stamp, sizeof(stamp), "%Y-%m-%d %H:%M:%S", lt);
            if (!history_started) fprintf(f, "# --- session %s ---\n", stamp);
            fprintf(f, "%s  %s\n", stamp, mantra);
            fclose(f); history_started = true;
        }
    }
    return true;
}
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
bool faxanadu_replace_file(const char *from, const char *to) {
    return MoveFileExA(from, to, MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != 0;
}
#endif

static void inject_password(void) {
    if (!password[0] || injected) return;
    unsigned max = cyc_mod_peek(0x0665), n = (unsigned)strlen(password);
    if (!max || max > 32 || n > max || cyc_mod_peek(0x0666) || cyc_mod_peek(0x0600) != 0xFF) return;
    /* Avoid overwriting pending game packets in the circular PPU queue. */
    uint8_t wp = cyc_mod_peek(0x20), rp = cyc_mod_peek(0x1F);
    unsigned free_bytes = (uint8_t)(rp - wp - 1);
    if (n * 4 > free_bytes) return;
    for (unsigned i = 0; i < max; ++i)
        cyc_mod_poke((uint16_t)(0x0600 + i), i < n ? (uint8_t)char_index(password[i]) : 0xFF);
    cyc_mod_poke(0x0664, (uint8_t)n);
    cyc_mod_poke(0x0666, (uint8_t)n);
    for (unsigned i = 0; i < n; ++i) {
        cyc_mod_poke((uint16_t)(0x0500 + wp++), 1);
        cyc_mod_poke((uint16_t)(0x0500 + wp++), 0x21);
        cyc_mod_poke((uint16_t)(0x0500 + wp++), (uint8_t)(i < 16 ? 0x28 + i : 0x48 + i - 16));
        cyc_mod_poke((uint16_t)(0x0500 + wp++), (uint8_t)password[i]);
    }
    cyc_mod_poke(0x20, wp);
    injected = true;
}
static void power_on(void *ctx) {
    (void)ctx; frame = 0; injected = false;
    fax_link_power_on();
    fax_world_reset();
    if (compile_path[0]) {
        int n = chr_override_compile_dir(compile_path);
        exit(n < 0 ? 2 : 0);
    }
    if (text_enabled) {
        text_override_init();
        text_override_register_encoding("FAXANADU_1", title_encode, 0);
        text_override_register_encoding("FAXANADU_DIALOGUE", dialogue_encode, 0xFF);
        text_override_register_encoding("ASCII", ascii_encode, 0);
        text_override_load_json(text_path);
    }
    if (!tiles_enabled) {
        char path[1100];
        if (sidecar_path("tiles/manifest.json", path)) {
            FILE *f = fopen(path, "r");
            if (f) { fclose(f); tiles_enabled = sidecar_path("tiles", tiles_path); }
        }
    }
    if (tiles_enabled || tile_dump) {
        chr_override_init();
        if (tile_dump) chr_override_set_dump(1);
        if (tiles_enabled) chr_override_load_manifest(tiles_path);
    }
    if (!password_cli) {
        password[0] = saved[0] = 0;
        if (cyc_host_saves_enabled()) {
            if (read_password("faxanadu.srm", password)) snprintf(saved, sizeof(saved), "%s", password);
            else read_password("saves.txt", password);
        }
    }
}
static void frame_begin(void *ctx) {
    (void)ctx;
    fax_link_frame_begin();
    if (text_enabled) { text_override_reload_if_changed(); text_override_apply(); }
    if (tiles_enabled) chr_override_reload_if_changed();
    inject_password();
}
static void frame_end(void *ctx) {
    (void)ctx; ++frame;
    fax_link_frame_end();
    fax_world_step();
    if (tiles_enabled || tile_dump) chr_override_frame_end();
    if (!cyc_host_saves_enabled() || frame % 900) return;
    if (!(cyc_mod_peek(0x042C) | cyc_mod_peek(0x042D) | cyc_mod_peek(0x0437) | cyc_mod_peek(0x0439))) return;
    char mantra[25];
    if (generate_mantra(mantra)) save_mantra(mantra);
}
static bool option(void *ctx, const char *name, const char *value) {
    (void)ctx;
    if(!strncmp(name,"--world-",8))return fax_world_option(name,value);
    char *path = NULL;
    if (!strcmp(name, "--text-overrides")) { path = text_path; text_enabled = true; }
    else if (!strcmp(name, "--tiles")) { path = tiles_path; tiles_enabled = true; }
    else if (!strcmp(name, "--tile-compile")) path = compile_path;
    else if (!strcmp(name, "--tile-dump")) { tile_dump = true; return true; }
    if (path) {
        if (!value || strlen(value) >= 1100) return false;
        snprintf(path, 1100, "%s", value); return true;
    }
    if (strcmp(name, "--password") || !parse_password(value, password)) return false;
    password_cli = true; injected = false; return true;
}
#ifdef CYC_WITH_SDL
static void mantra_now(int id, const char *line) {
    (void)line; char mantra[25], fields[128];
    if (!generate_mantra(mantra)) { cyc_tcp_err(id, "mantra encoder failed"); return; }
    snprintf(fields, sizeof(fields), "\"mantra\":\"%s\",\"len\":%u", mantra, (unsigned)strlen(mantra));
    cyc_tcp_ok(id, fields);
}
static void mantra_save(int id, const char *line) {
    (void)line; char mantra[25];
    if (!cyc_host_saves_enabled()) { cyc_tcp_err(id, "saves disabled by --no-save"); return; }
    if (!generate_mantra(mantra) || !save_mantra(mantra)) { cyc_tcp_err(id, "mantra save failed"); return; }
    mantra_now(id, line);
}
static void tcp_setup(void *ctx) {
    (void)ctx;
    cyc_tcp_register("mantra_now", "Read current progress without changing the machine", mantra_now);
    cyc_tcp_register("mantra_save", "Persist the current progress mantra", mantra_save);
    fax_link_tcp_setup();
    fax_world_tcp_setup();
}
#endif
static const uint32_t *present(void *ctx,int *w,int *h) {
    (void)ctx;const uint32_t *native=fax_link_present(w,h);
    const uint32_t *world=fax_world_present(w,h,native?native:cyc_frame_argb());
    return world?world:native;
}
static void audio_mix(void *ctx,int16_t *samples,size_t count) {
    (void)ctx;fax_link_audio_mix(samples,count);
}
static void event(void *ctx,const void *e,int player) {
    (void)ctx;(void)player;fax_link_event(e);
    fax_world_event(e);
}
static void load_setting(void *ctx,const char *key,const char *value) {
    (void)ctx;fax_link_load_setting(key,value);
}
static void save_settings(void *ctx,FILE *f) {(void)ctx;fax_link_save_settings(f);}
static void state_loaded(void *ctx) {(void)ctx;fax_world_loaded();}
const CycHostExtras *cyc_host_extras(void) {
    static const CycHostOption options[] = {
        { "--password", true, "Prefill a 1..24 character mantra (spaces allowed)" },
        { "--text-overrides", true, "Text replacement JSON, with hot reload" },
        { "--tiles", true, "Tile override directory, with hot reload" },
        { "--tile-dump", false, "Dump unique CHR transfers as PNG and binary assets" },
        { "--tile-compile", true, "Compile tile PNGs to CHR caches and exit" },
        { "--world-view", true, "World camera: off, seamless or atlas" },
        { "--world-size", true, "Fixed development viewport WxH; omit for adaptive Fit" },
    };
    static const CycHostExtras extras = {
        .present=present,.audio_rate=44100,.audio_mix=audio_mix,.event=event,
        .load_setting=load_setting,.save_settings=save_settings,
        .state_loaded=state_loaded,
        .power_on = power_on, .frame_begin = frame_begin, .frame_end = frame_end,
        .options = options, .option_count = sizeof(options) / sizeof(options[0]), .option = option,
#ifdef CYC_WITH_SDL
        .tcp_setup = tcp_setup,
#endif
    };
    return &extras;
}
