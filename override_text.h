/*
 * override_text.h — Runtime text override system for nesrecomp games.
 *
 * Architecture:
 *   The NES PPU DMA write buffer ($0500) is populated each frame by game code,
 *   then drained to the PPU by the NMI handler ($CF3C in Faxanadu's fixed bank).
 *   This module intercepts the buffer BEFORE the NMI drains it, finds known
 *   tile byte sequences, and replaces them with override content in-place.
 *
 * Hook point:
 *   Call text_override_apply() from game_on_frame() — after game code fills
 *   the buffer, before NMI drains it.
 *
 * Encoding:
 *   Games use game-specific tile indices, not ASCII.  The caller provides a
 *   tile_encode_fn to convert ASCII override strings into tile bytes.
 *   For Faxanadu tile-encoded text (title/menu): A=0xE0, space=0x20, null=0x00.
 *   For Faxanadu dialogue text (ASCII bank12):    tile = ASCII byte directly.
 *
 * Keying:
 *   Overrides are keyed by the tile byte pattern of the ORIGINAL string.
 *   This is content-addressable — no caller knowledge required.
 *
 * Variable-length:
 *   If replacement_len < pattern_len: remaining tiles are padded with space_tile.
 *   If replacement_len > pattern_len: the packet count is extended IF the
 *   extra bytes fit within the current packet boundary (i.e., no adjacent packet
 *   is clobbered). Otherwise the extra bytes are silently truncated.
 *   For full variable-length support, the caller should control the PPU layout
 *   (e.g., write a wider blank region before the text render).
 *
 * Portability:
 *   Depends only on nes_runtime.h (for g_ram). To adapt to another game:
 *     1. Provide the correct PPU DMA buffer address (default $0500).
 *     2. Provide the correct read/write pointer RAM addresses ($001F/$0020).
 *     3. Register overrides with the game's tile encoding.
 */

#pragma once
#include <stdint.h>

/* Maximum number of simultaneous overrides. */
#define TEXT_OVERRIDE_MAX 32

/* Maximum length of a pattern or replacement string (in tile bytes). */
#define TEXT_OVERRIDE_MAX_LEN 64

/* Opaque tile-encoding function: converts one ASCII char to a tile byte.
 * Return 0xFF if the character has no tile representation (will be skipped). */
typedef uint8_t (*tile_encode_fn)(char ch);

/* -------------------------------------------------------------------------
 * Lifecycle
 * ---------------------------------------------------------------------- */

/* Initialise the override system.  Call once from game_on_init(). */
void text_override_init(void);

/* Apply all registered overrides to the PPU DMA buffer.
 * Call from game_on_frame(), before NMI fires.
 * Scans the $0500 write buffer and replaces matching tile patterns in-place. */
void text_override_apply(void);

/* -------------------------------------------------------------------------
 * Registration (raw tile bytes)
 * ---------------------------------------------------------------------- */

/* Register a raw tile-byte override.
 * pattern/pattern_len:         the original tile bytes to search for.
 * replacement/replacement_len: the bytes to write instead. */
void text_override_register(const uint8_t *pattern,     int pattern_len,
                             const uint8_t *replacement, int replacement_len);

/* -------------------------------------------------------------------------
 * Registration (ASCII strings + encoder)
 * ---------------------------------------------------------------------- */

/* Register an override from human-readable ASCII strings.
 * original:  ASCII string matching the original text (e.g. "START").
 * override:  ASCII string to display instead (e.g. "BEGIN").
 * encode:    tile_encode_fn for this game's character set.
 *
 * Returns 1 on success, 0 if encoding failed or table is full. */
int text_override_register_ascii(const char *original, const char *override,
                                 tile_encode_fn encode);

/* -------------------------------------------------------------------------
 * ROM-level patching (works for any render path, including direct $2007 writes)
 * ---------------------------------------------------------------------- */

/* Patch tile bytes directly in the PRG ROM shadow buffer.
 * bank:        PRG bank number (0-based, 16KB banks).
 * prg_addr:    NES address within that bank ($8000-$BFFF).
 * replacement: tile bytes to write.
 * rep_len:     number of bytes to write.
 *
 * Must be called from game_on_init() after ROM is loaded.
 * The patch is permanent for the lifetime of the process.
 * If replacement is shorter than the original string, only those bytes
 * are patched; the caller is responsible for null-termination if needed. */
void text_override_patch_prg(int bank, uint16_t prg_addr,
                              const uint8_t *replacement, int rep_len);

/* Convenience: patch an ASCII string into the PRG ROM using the given encoder.
 * original_len: how many bytes of the original data to overwrite (for safe
 *               bounds checking — caller must know the original string length).
 * Returns 1 on success, 0 if encoding fails or address is invalid. */
int text_override_patch_prg_ascii(int bank, uint16_t prg_addr,
                                   int original_len,
                                   const char *replacement,
                                   tile_encode_fn encode);

/* -------------------------------------------------------------------------
 * Diagnostics
 * ---------------------------------------------------------------------- */

/* Dump the current $0500 buffer contents to stdout (for debugging).
 * Shows raw packets and attempts to decode tile bytes using the provided
 * encoder (may be NULL to show hex only). */
void text_override_dump_buffer(tile_encode_fn encode);
