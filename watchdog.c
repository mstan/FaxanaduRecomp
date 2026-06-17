/*
 * watchdog.c — Frame timeout detection
 *
 * When a frame exceeds WATCHDOG_TIMEOUT_SECS, logs the call stack and
 * forces a VBlank trigger to break out of spin-wait loops. Does NOT
 * longjmp (unsafe from deeply nested generated code).
 */
#include "watchdog.h"
#include "nes_runtime.h"

#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef RECOMP_STACK_TRACKING
#include "recomp_stack.h"
#endif

/* Watchdog globals (extern'd by runner's debug_server.c) */
extern int         g_watchdog_triggered;
extern uint32_t    g_watchdog_frame;
extern const char *g_watchdog_stack_dump;

static char s_watchdog_stack_buf[2048] = "";

jmp_buf g_watchdog_jmp;
static clock_t s_frame_start = 0;

void watchdog_frame_start(void) {
    s_frame_start = clock();
}

void watchdog_check(void) {
    /* Tick the VBlank budget on every backward branch so that tight loops
     * without memory access still get VBlank callbacks. This is the primary
     * mechanism for preventing stuck frames. */
    maybe_trigger_vblank(0);

    /* Reset the timer whenever the frame actually advances. watchdog_frame_start()
     * is declared but never wired up by the runner/recompiler, so the timer used
     * to reset only on timeout — making this fire every ~WATCHDOG_TIMEOUT_SECS of
     * WALL-CLOCK during normal play and dump whatever call stack happened to be
     * running (pure noise that looked like a stall but wasn't). Keying to
     * g_frame_count means "elapsed" now measures time spent inside a SINGLE
     * non-advancing frame, so the watchdog only trips on a genuinely stuck one. */
    static uint64_t s_timed_frame = (uint64_t)-1;
    if (g_frame_count != s_timed_frame) {
        s_timed_frame = g_frame_count;
        s_frame_start = clock();
        return;
    }

    clock_t now = clock();
    double elapsed = (double)(now - s_frame_start) / CLOCKS_PER_SEC;
    if (elapsed <= WATCHDOG_TIMEOUT_SECS) return;

    /* Genuinely stuck frame (no NMI for >timeout). Report once per frame. */
    static uint64_t s_last_reported_frame = (uint64_t)-1;
    if (g_frame_count != s_last_reported_frame) {
        s_last_reported_frame = g_frame_count;

        fprintf(stderr, "\n=== WATCHDOG: frame %llu stuck %.2fs (vblank_depth=%d) ===\n",
                (unsigned long long)g_frame_count, elapsed, runtime_get_vblank_depth());

        /* Populate watchdog globals for debug_server watchdog_status command */
        g_watchdog_triggered = 1;
        g_watchdog_frame = (uint32_t)g_frame_count;

        int spos = 0;
#ifdef RECOMP_STACK_TRACKING
        fprintf(stderr, "Call stack (most recent first):\n");
        for (int i = g_recomp_stack_top - 1; i >= 0; i--) {
            const char *fn = g_recomp_stack[i] ? g_recomp_stack[i] : "(null)";
            fprintf(stderr, "  [%d] %s\n", i, fn);
            spos += snprintf(s_watchdog_stack_buf + spos,
                             sizeof(s_watchdog_stack_buf) - spos,
                             "[%d] %s\\n", i, fn);
        }
#else
        fprintf(stderr, "(no stack tracking compiled in)\n");
        spos += snprintf(s_watchdog_stack_buf + spos,
                         sizeof(s_watchdog_stack_buf) - spos,
                         "(no stack tracking compiled in)");
#endif
        g_watchdog_stack_dump = s_watchdog_stack_buf;

        fprintf(stderr, "CPU: A=%02X X=%02X Y=%02X S=%02X bank=%d\n",
                g_cpu.A, g_cpu.X, g_cpu.Y, g_cpu.S, g_current_bank);
        fprintf(stderr, "=== forcing VBlank recovery (depth reset) ===\n\n");
    }

    /* ACTUALLY recover (the old code only logged): a frame this stuck means no
     * NMI is firing — typically because s_vblank_depth is pinned at
     * MAX_VBLANK_DEPTH from a nesting imbalance, so maybe_trigger_vblank() bails
     * out early forever. Reset the depth so the next backward branch's
     * maybe_trigger_vblank() fires the NMI at a safe loop boundary (s_ops_count is
     * already well past budget) and the frame advances. */
    runtime_reset_vblank_depth();
    s_frame_start = clock();
}
