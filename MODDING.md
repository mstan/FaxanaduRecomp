# Faxanadu Modding Guide

FaxanaduRecomp supports modding text and tile graphics without rebuilding
the game.  Drop override files next to the executable and they are loaded
automatically on startup.

---

## Text Overrides

Replace in-game text strings by editing a JSON file.

### Quick start

1. Copy `text_overrides.json` next to the game executable.
2. Edit the `"replacement"` fields.  Leave `"replacement": ""` to keep
   the original text.
3. Launch the game with `--text-overrides text_overrides.json`.

The file hot-reloads: save changes and they appear in-game within ~1
second (no restart needed).

### JSON format

```json
[
  {
    "bank": 12,
    "addr": "9DBC",
    "encoding": "FAXANADU_1",
    "source": "START",
    "replacement": "BEGIN"
  }
]
```

| Field         | Description                                          |
|---------------|------------------------------------------------------|
| `bank`        | PRG ROM bank number (0-based decimal).               |
| `addr`        | NES address within the bank (hex, no `0x` prefix).   |
| `encoding`    | Text encoding: `FAXANADU_1`, `FAXANADU_DIALOGUE`, or `ASCII`. |
| `source`      | Original text (informational, ignored by the loader). |
| `replacement` | New text.  Empty string = keep original.             |

### Encodings

- **FAXANADU_1** -- Title/menu text (A-Z, space).
- **FAXANADU_DIALOGUE** -- NPC dialogue (printable ASCII, `\n` for line
  break).
- **ASCII** -- Plain ASCII (mantra screen, etc.).

### Finding text addresses

Use the included `tools/scan_text.py` to search the ROM for strings and
discover their bank/address locations.

---

## Tile Overrides

Replace sprite and background tile graphics by editing PNG files.

### Quick start

1. Run the game once with `--tile-dump` to extract all tile assets:
   ```
   FaxanaduRecomp.exe --tile-dump
   ```
   This creates a `tiles/` directory with PNG files and a
   `manifest.json`.

2. Open any PNG in an image editor (Paint, GIMP, Aseprite, etc.).
   Tiles use a 4-color grayscale palette:
   - Black (`#000000`) = palette index 0
   - Dark gray (`#555555`) = palette index 1
   - Light gray (`#AAAAAA`) = palette index 2
   - White (`#FFFFFF`) = palette index 3

3. Save your edits.  The game loads the `tiles/` directory
   automatically if `tiles/manifest.json` exists next to the
   executable.

4. Launch the game -- your modified tiles appear in-game.

### How it works

Each PNG represents a set of 8x8 NES tiles dumped from a single CHR RAM
transfer.  The `manifest.json` maps each PNG back to its PPU address,
transfer length, and content CRC so the runtime knows when and where to
apply each override.

For non-tile-aligned transfers (where the game writes partial tile data),
a companion `.bin` file preserves the leading/trailing bytes that the PNG
cannot represent.  Do not delete these `.bin` files.

### Manifest format

```json
{
  "overrides": [
    {
      "ppu_addr": "0x0400",
      "length": 1280,
      "crc": "0xD13AF8B1",
      "lead_bytes": 0,
      "trail_bytes": 0,
      "file": "asset_0000_addr0400.png"
    }
  ]
}
```

### CLI options

| Flag                    | Description                                    |
|-------------------------|------------------------------------------------|
| `--tile-dump`           | Dump tile assets as PNGs to `tiles/`.          |
| `--tiles DIR`           | Load tile overrides from DIR (default: `tiles`). |
| `--tile-compile DIR`    | Batch pre-compile PNGs to `.chr.bin` for faster loading. |

### Optimized loading

On first load, each PNG is JIT-converted to a `.chr.bin` cache file.
Subsequent launches load the cache directly.  To pre-compile for
distribution:

```
FaxanaduRecomp.exe --tile-compile tiles
```

### Hot reload

Tile overrides support hot reload.  Edit a PNG while the game is running
and save -- the change appears within ~1 second.

---

## Distributing a mod

A complete mod is a folder containing:

- `text_overrides.json` (optional, for text changes)
- `tiles/manifest.json` + PNG files (optional, for tile changes)
- Any companion `.bin` files for non-aligned assets

Users drop these files next to the game executable.  The game
auto-detects `tiles/manifest.json` on startup.  Text overrides require
the `--text-overrides` flag (or a future auto-detect addition).
