#!/usr/bin/env python3
"""
scan_text.py — Scan a Faxanadu PRG ROM for text strings and emit a text_overrides.json template.

Every detected string gets an entry with "source" populated and "replacement" left empty.
Fill in replacements for strings you want to override; entries with empty replacement
are ignored by the loader.

Encodings
---------
FAXANADU_1        bank12 menu/title text.  A=0xE0, space=0x20.  Null-terminated (0x00).
ASCII             Null-terminated plain ASCII.  Mostly false positives outside known regions.
FAXANADU_DIALOGUE bank13 NPC dialogue.  Plain ASCII letters/punctuation plus control bytes:
                    0xFD = word space
                    0xFE = space variant (word-wrap budget differs from 0xFD)
                    0xFC = line break within the same dialogue box
                  Entries are 0xFF-terminated.  Each 0xFF ends one NPC line/exchange.
                  source field renders control bytes as readable characters:
                    0xFD / 0xFE -> space,  0xFC -> \\n

Usage:
    python tools/scan_text.py [ROM] [OUTPUT] [--min-len N] [--banks 12,13]

    ROM      Path to iNES ROM file  (default: baserom.nes)
    OUTPUT   Output JSON path       (default: text_overrides_full.json)
    --min-len N     Minimum string character count to record  (default: 4)
    --banks A,B,…   Comma-separated bank numbers to scan  (default: all)

Examples:
    python tools/scan_text.py
    python tools/scan_text.py baserom.nes all_text.json --min-len 3
    python tools/scan_text.py baserom.nes --banks 12,13
"""

import sys
import os
import json

# iNES constants
INES_HEADER_SIZE = 16
PRG_BANK_SIZE    = 0x4000   # 16 KB per bank
NES_BANK_BASE    = 0x8000   # switchable banks mapped here at runtime

# ---------------------------------------------------------------------------
# Encoding definitions.
# Each entry: (name, tile_map, terminator)
#   tile_map:   byte -> display char.  Bytes not in the map break a string.
#   terminator: byte that ends a string (not included in output).
# ---------------------------------------------------------------------------

# Faxanadu dialogue tile map: printable ASCII + control tokens.
_DIALOGUE_MAP = {i: chr(i) for i in range(0x21, 0x7F)}  # '!' through '~'
_DIALOGUE_MAP[0x20] = ' '   # regular space (rare in dialogue, but valid)
_DIALOGUE_MAP[0xFC] = '\n'  # line break within dialogue box
_DIALOGUE_MAP[0xFD] = ' '   # word space (primary)
_DIALOGUE_MAP[0xFE] = ' '   # space variant

ENCODINGS = [
    # (name,                tile_map,                                              terminator)
    ("FAXANADU_1",         {**{0xE0+i: chr(ord('A')+i) for i in range(26)}, 0x20:' '}, 0x00),
    ("ASCII",              {i: chr(i) for i in range(0x20, 0x7F)},                     0x00),
    ("FAXANADU_DIALOGUE",  _DIALOGUE_MAP,                                               0xFF),
]


# ---------------------------------------------------------------------------
# Scanner
# ---------------------------------------------------------------------------

def scan_bank(bank_data, bank_num, enc_name, tile_map, terminator, min_len):
    """
    Slide over bank_data looking for strings that consist entirely of bytes
    present in tile_map, terminated by `terminator`.
    Returns a list of entry dicts.
    """
    results = []
    size    = len(bank_data)
    offset  = 0

    while offset < size:
        chars = []
        pos   = offset

        while pos < size:
            b = bank_data[pos]
            if b == terminator:
                break
            if b not in tile_map:
                break
            chars.append(tile_map[b])
            pos += 1

        length = len(chars)
        # Strip leading/trailing whitespace from source for length check,
        # but keep the full string for the output.
        hit = (length >= min_len
               and pos < size
               and bank_data[pos] == terminator
               and ''.join(chars).strip())  # must have non-whitespace content

        if hit:
            nes_addr = NES_BANK_BASE + offset
            results.append({
                "bank":        bank_num,
                "addr":        f"{nes_addr:04X}",
                "encoding":    enc_name,
                "source":      ''.join(chars).strip(),
                "replacement": "",
            })
            offset = pos + 1    # skip past terminator, no overlapping matches
        else:
            offset += 1

    return results


# ---------------------------------------------------------------------------
# Entry point
# ---------------------------------------------------------------------------

def main():
    rom_path    = "baserom.nes"
    output_path = "text_overrides_full.json"
    min_len     = 4
    bank_filter = None  # None = all banks

    args       = sys.argv[1:]
    positional = 0
    i          = 0
    while i < len(args):
        a = args[i]
        if a == "--min-len" and i + 1 < len(args):
            min_len = int(args[i + 1])
            i += 2
        elif a == "--banks" and i + 1 < len(args):
            bank_filter = {int(b) for b in args[i + 1].split(',')}
            i += 2
        elif not a.startswith('--'):
            if positional == 0:
                rom_path = a
            elif positional == 1:
                output_path = a
            positional += 1
            i += 1
        else:
            print(f"Unknown argument: {a}", file=sys.stderr)
            i += 1

    if not os.path.exists(rom_path):
        print(f"Error: ROM not found: {rom_path}", file=sys.stderr)
        sys.exit(1)

    with open(rom_path, 'rb') as f:
        rom = f.read()

    if rom[:4] != b'NES\x1a':
        print("Error: not an iNES ROM (bad magic)", file=sys.stderr)
        sys.exit(1)

    prg_banks = rom[4]
    print(f"ROM: {prg_banks} PRG banks x 16KB  ({prg_banks * 16} KB PRG total)")

    entries = []
    for bank_num in range(prg_banks):
        if bank_filter is not None and bank_num not in bank_filter:
            continue

        bank_offset = INES_HEADER_SIZE + bank_num * PRG_BANK_SIZE
        bank_data   = rom[bank_offset : bank_offset + PRG_BANK_SIZE]

        for enc_name, tile_map, terminator in ENCODINGS:
            found = scan_bank(bank_data, bank_num, enc_name, tile_map, terminator, min_len)
            if found:
                print(f"  bank {bank_num:2d}  {enc_name:<20s}  {len(found):4d} strings")
            entries.extend(found)

    # Sort by bank, then by NES address within the bank
    entries.sort(key=lambda e: (e['bank'], int(e['addr'], 16)))

    with open(output_path, 'w', encoding='utf-8') as f:
        json.dump(entries, f, indent=2, ensure_ascii=False)

    print(f"\n{len(entries)} total strings -> {output_path}")


if __name__ == '__main__':
    main()
