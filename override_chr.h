/*
 * override_chr.h — CHR / PNG tile-sheet asset override (FUTURE WORK stub).
 *
 * Architecture sketch (not yet implemented):
 *
 *   The NES PPU reads tile graphics from g_chr_ram[0x2000] (already exposed in
 *   nes_runtime.h).  Overriding graphics is therefore a single memcpy from a
 *   decoded PNG/tile-sheet into the appropriate offset within that buffer.
 *
 *   Planned interface:
 *
 *     chr_override_load_png(const char *path, int chr_offset, int num_tiles)
 *       Decode PNG → 1bpp or 2bpp NES format → write into g_chr_ram[chr_offset].
 *       chr_offset in bytes (0x0000–0x1FFF).
 *       num_tiles = number of 8x8 tiles (16 bytes each in NES CHR format).
 *
 *     chr_override_reload_if_changed()
 *       Same hot-reload pattern as text_override_reload_if_changed().
 *
 *   JSON-driven CHR override format (proposed):
 *     [
 *       { "path": "ui_font.png", "chr_offset": "0000", "tiles": 96 },
 *       { "path": "portraits.png", "chr_offset": "0600", "tiles": 32 }
 *     ]
 *
 *   PNG encoding conventions:
 *     - 1-bit (black/white) or 4-color indexed PNG → mapped to NES 2bpp CHR.
 *     - Tile order: left-to-right, top-to-bottom in 8px grid.
 *     - Each tile = 16 bytes: 8 bytes plane0 + 8 bytes plane1.
 *
 *   Dependencies:
 *     A PNG decode library (stb_image recommended — single-header, no deps).
 *     Add stb_image.h to the source tree and #define STB_IMAGE_IMPLEMENTATION
 *     in exactly one .c file.
 *
 * Status: STUB ONLY — this header documents the planned interface.
 *   g_chr_ram is already writable.  The PNG decode + NES format conversion
 *   is the remaining work.  Implement in override_chr.c when needed.
 */
#pragma once
