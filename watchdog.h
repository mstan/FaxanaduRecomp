/*
 * watchdog.h — Frame timeout detection
 *
 * Detects infinite loops in recompiled code by checking elapsed time
 * at loop back-edges. If a frame exceeds WATCHDOG_TIMEOUT_SECS,
 * dumps the recomp call stack and longjmps out.
 */
#pragma once

#include <setjmp.h>

/* A natively-recompiled frame runs in microseconds; anything spending this long
 * inside ONE non-advancing frame is a genuine infinite loop. Kept well above any
 * real frame so there are no false positives, but low enough that the forced
 * recovery below turns a stuck frame into a brief hitch instead of a long freeze. */
#define WATCHDOG_TIMEOUT_SECS 1.0

/* Jump buffer for watchdog abort. Set before calling game code. */
extern jmp_buf g_watchdog_jmp;

/* Call at the start of each NMI frame. */
void watchdog_frame_start(void);

/* Call at loop back-edges in generated code.
 * If timeout exceeded, dumps stack and longjmps. */
void watchdog_check(void);
