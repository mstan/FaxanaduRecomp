/*
 * verify_mode.c — Dual-execution verification mode
 *
 * Modeled after snesrecomp-v2/src/common_cpu_infra.c:RtlRunFrameCompare()
 */
#include "verify_mode.h"
#include "nes_snapshot.h"
#include "nes_runtime.h"
#include "debug_server.h"

#include <stdio.h>
#include <string.h>

#ifdef ENABLE_FCEUX_ORACLE
#include "fceux_bridge.h"
#endif

RunMode  g_run_mode = RUN_MODE_NATIVE;
static uint64_t s_divergence_count = 0;
static int s_fceux_initialized = 0;

void verify_mode_init(const char *rom_path) {
#ifdef ENABLE_FCEUX_ORACLE
    if (g_run_mode == RUN_MODE_NATIVE) return;

    int rc = fceux_bridge_init(rom_path);
    if (rc != 0) {
        fprintf(stderr, "[verify] FCEUX init failed (rc=%d), falling back to native\n", rc);
        g_run_mode = RUN_MODE_NATIVE;
        return;
    }
    s_fceux_initialized = 1;
    fprintf(stderr, "[verify] FCEUX oracle initialized (mode=%s)\n",
            g_run_mode == RUN_MODE_VERIFY ? "verify" : "emulated");
#else
    (void)rom_path;
    if (g_run_mode != RUN_MODE_NATIVE) {
        fprintf(stderr, "[verify] FCEUX oracle not compiled in, falling back to native\n");
        g_run_mode = RUN_MODE_NATIVE;
    }
#endif
}

int verify_mode_run_nmi(void) {
    if (g_run_mode == RUN_MODE_NATIVE) {
        /* Pure native: just call the recompiled NMI */
        func_NMI();
        return 1;
    }

#ifdef ENABLE_FCEUX_ORACLE
    if (!s_fceux_initialized) {
        func_NMI();
        return 1;
    }

    if (g_run_mode == RUN_MODE_EMULATED) {
        /* Pure FCEUX: run one frame via oracle, then copy RAM state back
         * so the native runtime (PPU renderer, etc.) has correct data. */
        fceux_bridge_run_frame(g_controller1_buttons);

        /* Extract FCEUX state into our runtime */
        fceux_bridge_get_ram(g_ram);
        fceux_bridge_get_sram(g_sram);
        fceux_bridge_get_oam(g_ppu_oam);
        fceux_bridge_get_palette(g_ppu_pal);
        fceux_bridge_get_nametable(g_ppu_nt);

        uint8_t a, x, y, s, p;
        uint16_t pc;
        fceux_bridge_get_cpu(&a, &x, &y, &s, &p, &pc);
        g_cpu.A = a;
        g_cpu.X = x;
        g_cpu.Y = y;
        g_cpu.S = s;
        return 1;
    }

    /* VERIFY mode: run both, compare */
    static NESSnapshot snap_before, snap_native, snap_emulated;

    /* 1. Capture state before NMI */
    nes_snapshot_capture(&snap_before);

    /* 2. Run FCEUX oracle frame */
    fceux_bridge_run_frame(g_controller1_buttons);

    /* 3. Extract FCEUX post-frame state as "emulated" result */
    fceux_bridge_get_ram(snap_emulated.ram);
    fceux_bridge_get_sram(snap_emulated.sram);
    fceux_bridge_get_oam(snap_emulated.ppu_oam);
    fceux_bridge_get_palette(snap_emulated.ppu_pal);

    /* 4. Restore pre-NMI state */
    nes_snapshot_restore(&snap_before);

    /* 5. Run native recompiled NMI */
    func_NMI();

    /* 6. Capture native post-frame state */
    nes_snapshot_capture(&snap_native);

    /* 7. Compare RAM (primary comparison target) */
    SnapshotDiff diffs[32];
    int diff_count = 0;

    /* Compare work RAM */
    for (int i = 0; i < 0x0800; i++) {
        if (snap_native.ram[i] != snap_emulated.ram[i]) {
            if (diff_count < 32) {
                diffs[diff_count].addr   = (uint16_t)i;
                diffs[diff_count].val_a  = snap_native.ram[i];
                diffs[diff_count].val_b  = snap_emulated.ram[i];
                diffs[diff_count].region = "ram";
            }
            diff_count++;
        }
    }

    int passed = (diff_count == 0);

    if (!passed) {
        s_divergence_count++;
        if (s_divergence_count <= 10) {
            fprintf(stderr, "[verify] DIVERGENCE at frame %llu: %d byte(s) differ in RAM\n",
                    (unsigned long long)g_frame_count, diff_count);
            int show = diff_count < 8 ? diff_count : 8;
            for (int i = 0; i < show; i++) {
                fprintf(stderr, "  [%s $%04X] native=0x%02X oracle=0x%02X\n",
                        diffs[i].region, diffs[i].addr,
                        diffs[i].val_a, diffs[i].val_b);
            }
            if (diff_count > 8)
                fprintf(stderr, "  ... and %d more\n", diff_count - 8);
        }
    }

    /* The native result is kept (we're already in native state after func_NMI).
     * This means the game continues from native execution.
     * If you want oracle-as-ground-truth, restore snap_emulated instead. */

    return passed;
#else
    func_NMI();
    return 1;
#endif
}

uint64_t verify_mode_get_divergence_count(void) {
    return s_divergence_count;
}
