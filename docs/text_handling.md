# Faxanadu Text Handling

This document describes how Faxanadu stores and renders text, and how the
runtime text override system works for modding and localization.

---

## Text Rendering Paths

Faxanadu has **two completely separate text rendering paths**. They use
different source data, different encodings, and different render mechanisms.
Understanding which path a string uses is essential for overriding it.

### Path 1 — Title / Menu Text (direct PPU write)

**Where:** Bank 12, around `$9DBD`  
**Encoding:** FAXANADU_1 (see below)  
**Renderer:** Code at bank 12 `$9E10` — `LDA ($EC),Y` → `STA $2007`

The title screen and main menu strings are rendered by a tight loop that
reads tile bytes from a pointer in zero page (`$EC`/`$ED`) and writes them
directly to the PPU data register (`$2007`). This loop **does not use the
`$0500` DMA buffer** — it writes to the PPU immediately during NMI.

Because the source data is read straight from PRG ROM, the only way to
override these strings is to patch the PRG ROM shadow buffer in RAM (see
[Override System](#override-system) below).

**Known strings:**

| NES Address | Content          |
|-------------|------------------|
| `$9DBD`     | `START`          |
| `$9DC3`     | `CONTINUE`       |
| `$9DD2`     | `HUDSON SOFT`    |
| `$9DDF`     | `UNDER LICENSE FROM FALCOM` |
| `$9DF9`     | `LICENSED TO NINTENDO`      |

Note: the byte at `$9DBC` is a leading space (`0x20`) that precedes `START`
as part of menu layout. Overrides target `$9DBD` (the `S`), not `$9DBC`.

---

### Path 2 — NPC / Dialogue Text ($0500 DMA buffer)

**Where:** Bank 13 (primary), bank 12 `$91BE` (Mantra screen)  
**Encoding:** FAXANADU_DIALOGUE (see below)  
**Renderer:** Subroutine at `$F842` (fixed bank) → writes to `$0500` PPU DMA queue

NPC dialogue and in-game messages are processed by a dedicated text renderer
(`$F842`) that reads strings from banked ROM and queues tile writes into the
`$0500` DMA buffer. The buffer is drained to the PPU during NMI by the
processor at `$CF3C`.

---

## Encodings

### FAXANADU_1

Used for title screen and menu text. Uppercase letters only.

| Byte range  | Meaning         |
|-------------|-----------------|
| `0xE0`      | `A`             |
| `0xE1`      | `B`             |
| …           | …               |
| `0xF9`      | `Z`             |
| `0x20`      | Space           |
| `0x00`      | Null terminator |

Each string is null-terminated. Strings are stored contiguously in PRG ROM
with no padding between them.

### FAXANADU_DIALOGUE

Used for all NPC dialogue, shop text, and in-game messages (bank 13).

Regular letters, digits, and punctuation are stored as **plain ASCII**
(`0x20`–`0x7E`). Spacing and layout are handled by control tokens:

| Byte   | Meaning                                               |
|--------|-------------------------------------------------------|
| `0xFD` | Word space (primary — used between most words)        |
| `0xFE` | Space variant (used for word-wrap budget differences) |
| `0xFC` | Line break within the same dialogue box               |
| `0xFF` | **Entry terminator** — ends this NPC line; the next entry begins immediately |

Each dialogue entry is `0xFF`-terminated. Multiple entries are stored
back-to-back with no padding. There is no explicit count or index table
in the data itself — the renderer locates entries by following pointers
set up by the game engine at runtime.

### ASCII (Mantra screen)

The Mantra entry/display screen at bank 12 `$91BE` uses plain null-terminated
ASCII (`0x00` terminator). Multiple dialogue lines within a single "screen"
are stored as **one long null-terminated block** with spaces used as internal
padding to position text on fixed display rows. Do not attempt to split this
block — the spacing is load-bearing for the renderer's line layout.

---

## Multi-line Dialogue

Within a single dialogue box, `0xFC` marks the boundary between display lines.
A full NPC exchange that fills multiple lines or scroll pages uses `0xFC`
for line breaks within a box and `0xFF` to end the whole entry.

Example (bank 13 `$87FB`):

```
I've been on a long journey.
I came back to my home town to find it is almost deserted.
The gate is closed, people are gone,
and the walls are crumbling.
I wonder what happened.
```

In the ROM this is stored as one `0xFF`-terminated entry. The `\n` characters
in the `source` field of override JSON represent `0xFC` bytes.

**When writing replacement text**, preserve the relative structure of `0xFC`
line breaks. The renderer assumes fixed box geometry — lines that are too long
will overflow into adjacent nametable cells.

---

## Override System

Text is overridden at runtime by patching the **PRG ROM shadow buffer** — the
heap-allocated copy of the ROM that the recompiler reads from. The disk ROM
file is never modified.

The override loader (`override_text.c`) reads `text_overrides.json` from the
current working directory at startup and re-checks it every ~1 second for
hot-reload. See `override_text.h` for the full API.

### JSON Format

```json
[
  {
    "bank":        12,
    "addr":        "9DBD",
    "encoding":    "FAXANADU_1",
    "source":      "START",
    "replacement": "BEGIN"
  },
  {
    "bank":        13,
    "addr":        "8300",
    "encoding":    "FAXANADU_DIALOGUE",
    "source":      "Hello. Could I help you with anything. | What would you like?",
    "replacement": ""
  }
]
```

| Field         | Required | Description                                                         |
|---------------|----------|---------------------------------------------------------------------|
| `bank`        | yes      | PRG bank number (0-based, 16 KB banks)                              |
| `addr`        | yes      | NES address within the bank (`$8000`–`$BFFF`), hex string           |
| `encoding`    | yes      | Registered encoder name (`FAXANADU_1`, `FAXANADU_DIALOGUE`, etc.)   |
| `source`      | no       | Original text — informational only, ignored by the loader            |
| `replacement` | yes      | Text to substitute. Empty string (`""`) skips this entry            |

In `source` and `replacement` fields, `\n` represents a `0xFC` line-break
token for FAXANADU_DIALOGUE strings.

### Replacement Length

Replacements may be **any length**. The null/`0xFF` terminator is written
implicitly after the encoded replacement. The renderer reads until the
terminator, so:

- **Shorter than original:** renders correctly; bytes after the new
  terminator are ignored by the renderer.
- **Longer than original:** the extra bytes overwrite adjacent ROM shadow
  data. The renderer still stops at the new terminator. Whether the extra
  characters actually display depends on the nametable geometry for that
  string. **The modder is responsible for staying within the visible area.**

Debug builds emit a warning to stderr when a replacement exceeds the
original string's length.

---

## Tools

### `tools/scan_text.py`

Scans the ROM and emits a `text_overrides.json` template with `source`
populated and `replacement` empty.

```
python tools/scan_text.py [ROM] [OUTPUT] [--min-len N] [--banks 12,13]
```

### `tools/text_overrides.json`

Pre-generated template containing all 199 verified text strings:
5 menu strings (FAXANADU_1), 1 Mantra screen block (ASCII), and
193 NPC dialogue entries (FAXANADU_DIALOGUE). All `replacement` fields
are empty — fill in the ones you want to change, then copy the file
next to `FaxanaduRecomp.exe`. That is the exact filename the game looks
for by default.
