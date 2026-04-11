/*
 * override_text.h — Runtime text override system for nesrecomp games.
 *
 * Architecture:
 *   Two intercept mechanisms for different NES rendering paths:
 *
 *   1. PRG ROM patch — text_override_patch_prg_*()
 *      Writes replacement bytes directly into the heap PRG ROM shadow buffer
 *      via runner_get_prg_bank_rw().  Works for ANY rendering path (direct
 *      $2007 writes, $0500 DMA queue, etc.) because every renderer reads from
 *      the same source data.
 *
 *   2. PPU DMA buffer scan — text_override_apply()
 *      Scans the $0500 write buffer in game_on_frame() before NMI drains it.
 *      Targets the $F842 dialogue rendering path.
 *
 * JSON override file:
 *   Load from a JSON file next to the exe with text_override_load_json().
 *   Hot-reload is supported: call text_override_reload_if_changed() from
 *   game_on_frame() and the file is re-applied automatically within ~1 second
 *   of an on-disk change.
 *
 * Encoding registry:
 *   Tile encoders are registered by name so the JSON file can reference them.
 *   Register from extras.c before calling text_override_load_json().
 *
 * Variable-length:
 *   Replacements may be shorter or longer than the original string.  The null
 *   terminator is always written immediately after the encoded replacement.
 *   The renderer reads until null, so longer strings render if the nametable
 *   has room.  Overwriting adjacent ROM data is the modder's responsibility.
 *
 * Portability:
 *   Core logic depends only on nes_runtime.h (g_ram, runner_get_prg_bank_rw).
 *   Game-specific encoders and the JSON file path live in extras.c.
 */
#pragma once
#include <stdint.h>

/* Maximum simultaneous override registrations. */
#define TEXT_OVERRIDE_MAX     32
/* Maximum tile bytes in a single replacement (null terminator is appended implicitly). */
#define TEXT_OVERRIDE_MAX_LEN 64
/* Maximum named encodings that can be registered. */
#define TEXT_OVERRIDE_MAX_ENC 16

/* Opaque tile-encoding function: converts one ASCII char to a tile byte.
 * Return 0xFF if the character has no tile representation (call will fail). */
typedef uint8_t (*tile_encode_fn)(char ch);

/* =========================================================================
 * Lifecycle
 * ====================================================================== */

/* Initialise (clear all state).  Call once from game_on_init(). */
void text_override_init(void);

/* Apply PPU DMA buffer overrides.  Call from game_on_frame() before NMI. */
void text_override_apply(void);

/* =========================================================================
 * Encoding registry
 * ====================================================================== */

/* Register a named tile encoder.  Must be done before text_override_load_json().
 * name: identifier used in the JSON "encoding" field (e.g. "fax_menu").
 * fn:   the game-specific encoder function. */
void text_override_register_encoding(const char *name, tile_encode_fn fn);

/* Look up a registered encoder by name.  Returns NULL if not found. */
tile_encode_fn text_override_find_encoding(const char *name);

/* =========================================================================
 * JSON override file
 * ====================================================================== */

/* Load overrides from a JSON file and apply them to the PRG ROM shadow.
 * path: full path to the JSON file.
 * Returns number of entries applied, or -1 on file/parse error.
 *
 * JSON format:
 *   [
 *     { "bank": 12, "addr": "9DBD", "encoding": "FAXANADU_1", "source": "START", "replacement": "BEGIN" },
 *     ...
 *   ]
 *
 * Fields:
 *   bank        — PRG bank number (0-based decimal integer).
 *   addr        — NES address within the bank (hex string, no "0x" prefix).
 *   encoding    — name of a registered tile_encode_fn.
 *   source      — (informational) original text at this address; ignored by the loader.
 *   replacement — ASCII string to substitute.
 *
 * The original string length is detected automatically (null-terminator scan)
 * and cached; subsequent reloads use the cached length. */
int text_override_load_json(const char *path);

/* Check if the JSON file has been modified since last load; reload if so.
 * Designed to be called every frame from game_on_frame() — only performs
 * a stat() check every 60 calls (≈1 second at 60 fps). */
void text_override_reload_if_changed(void);

/* =========================================================================
 * PRG ROM patching (raw)
 * ====================================================================== */

/* Patch tile bytes directly into the PRG ROM shadow buffer.
 * bank:        PRG bank number (0-based, 16KB banks).
 * prg_addr:    NES address within that bank ($8000–$BFFF).
 * replacement: tile bytes to write.
 * rep_len:     number of bytes.
 * Call from game_on_init() or text_override_load_json(). */
void text_override_patch_prg(int bank, uint16_t prg_addr,
                              const uint8_t *replacement, int rep_len);

/* Patch from an ASCII string + encoder.
 * Encodes replacement and writes it followed by an implicit null terminator.
 * Replacement may be longer than the original string — the renderer reads until
 * the null, so extra characters render if the nametable has room.  Writing past
 * adjacent ROM data is the caller's responsibility.
 * Returns 1 on success, 0 on encode error. */
int text_override_patch_prg_ascii(int bank, uint16_t prg_addr,
                                   const char *replacement,
                                   tile_encode_fn encode);

/* Identical to text_override_patch_prg_ascii — kept for JSON loader symmetry. */
int text_override_patch_prg_auto(int bank, uint16_t prg_addr,
                                  const char *replacement,
                                  tile_encode_fn encode);

/* =========================================================================
 * PPU DMA buffer pattern registration (for $0500 path)
 * ====================================================================== */

/* Register a raw tile-byte pattern override for the $0500 buffer scanner. */
void text_override_register(const uint8_t *pattern,     int pattern_len,
                             const uint8_t *replacement, int replacement_len);

/* Register a buffer-scan override from ASCII strings + encoder. */
int text_override_register_ascii(const char *original, const char *override_str,
                                  tile_encode_fn encode);

/* =========================================================================
 * Diagnostics
 * ====================================================================== */

/* Dump $0500 buffer contents to stdout. */
void text_override_dump_buffer(tile_encode_fn encode);
