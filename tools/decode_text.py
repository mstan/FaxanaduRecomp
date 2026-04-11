#!/usr/bin/env python3
"""Decode all text data blocks in Faxanadu bank12."""

ROM_PATH = "F:/Projects/nesrecomp-release/FaxanaduRecomp/baserom.nes"
PRG_BASE = 16
BANK_SIZE = 16384

with open(ROM_PATH, "rb") as f:
    rom = f.read()

def bank_addr_to_rom(bank, addr):
    return PRG_BASE + bank * BANK_SIZE + (addr - 0x8000)

def rom_slice(bank, start_addr, length):
    off = bank_addr_to_rom(bank, start_addr)
    return rom[off:off+length]

BANK = 12

# ------------------------------------------------------------------
# Encoding A=0xE0: uppercase letters A-Z = 0xE0-0xF9, space=0x20,
# null terminator=0x00
# ------------------------------------------------------------------
TILE_BASE = 0xE0  # tile for 'A'

TILE_CHARMAP = {}
for i in range(26):
    TILE_CHARMAP[TILE_BASE + i] = chr(ord('A') + i)
TILE_CHARMAP[0x20] = ' '
TILE_CHARMAP[0x00] = '\x00'  # terminator

def decode_tile_str(data, offset):
    """Decode a null-terminated tile-encoded string from data[offset:]."""
    out = []
    i = offset
    while i < len(data):
        b = data[i]
        if b == 0x00:
            return ''.join(out), i + 1
        out.append(TILE_CHARMAP.get(b, f'[{b:02x}]'))
        i += 1
    return ''.join(out), i

# ------------------------------------------------------------------
# Item name table: 13-char ASCII, 0x0D terminated
# Find start by scanning backward from 0x9C80 for known item names
# ------------------------------------------------------------------

print("=" * 60)
print("ITEM NAME TABLE (ASCII, 13-char + 0x0D)")
print("=" * 60)

# Item table: known to contain "ROD", "CRYSTAL", etc.
# Scan the whole bank for 0x0D-terminated 13-char ASCII blocks
data_off = bank_addr_to_rom(BANK, 0x8000)
bank_data = rom[data_off:data_off + BANK_SIZE]

# Find item table start: look for first 13-char block ending in 0x0D
# The item names are 13 chars + 0x0D = 14 bytes per entry
ITEM_ENTRY_SIZE = 14

# Scan from beginning of bank for sequences of valid ASCII + 0x0D
print("\nScanning for item name table entries (13 ASCII + 0x0D)...")
item_start = None
for i in range(0, len(bank_data) - 14, 1):
    chunk = bank_data[i:i+14]
    if chunk[13] == 0x0D and all(0x20 <= b <= 0x7E for b in chunk[:13]):
        if item_start is None:
            item_start = i
            print(f"\nFirst item at bank12 offset 0x{i:04x} = addr 0x{0x8000+i:04x}")
        # Decode all consecutive items
        break

if item_start is not None:
    i = item_start
    while i + 14 <= len(bank_data):
        chunk = bank_data[i:i+14]
        if chunk[13] == 0x0D and all(0x20 <= b <= 0x7E for b in chunk[:13]):
            name = chunk[:13].decode('ascii').rstrip()
            print(f"  0x{0x8000+i:04x}: '{name}'")
            i += 14
        else:
            print(f"  (table ends at 0x{0x8000+i:04x})")
            break

# ------------------------------------------------------------------
# Tile-encoded string block (A=0xE0): START, CONTINUE, etc.
# Known start around 0x9DBD
# ------------------------------------------------------------------
print("\n" + "=" * 60)
print("TILE-ENCODED STRINGS (A=0xE0, null-terminated)")
print("=" * 60)

# Scan for null-terminated tile strings starting around 0x9DBD
scan_start_addr = 0x9D00
scan_end_addr   = 0x9F00
off = bank_addr_to_rom(BANK, scan_start_addr)
data = rom[off:off + (scan_end_addr - scan_start_addr)]

i = 0
in_string_block = False
while i < len(data):
    addr = scan_start_addr + i
    b = data[i]
    # Check if this looks like start of a tile string
    if b in TILE_CHARMAP or b == 0x20:
        # Try to decode a string from here
        s, end_i = decode_tile_str(data, i)
        if len(s) >= 3 and not s.startswith(' '):  # plausible string
            print(f"  0x{addr:04x}: '{s}' (raw: {data[i:i+len(s)+1].hex()})")
            i = end_i
            continue
    i += 1

# ------------------------------------------------------------------
# Show full hex+annotation of the transition zone 0x9DAD-0x9E20
# ------------------------------------------------------------------
print("\n" + "=" * 60)
print("RAW DUMP: 0x9DAD-0x9E50 (post item-table data block)")
print("=" * 60)
for addr in range(0x9DAD, 0x9E50, 16):
    off = bank_addr_to_rom(BANK, addr)
    chunk = rom[off:off+16]
    hex_str = ' '.join(f'{b:02x}' for b in chunk)
    # Try ASCII decode
    asc = ''.join(chr(b) if 0x20 <= b <= 0x7E else '.' for b in chunk)
    # Try tile decode
    til = ''.join(TILE_CHARMAP.get(b, '.') for b in chunk)
    print(f"  {addr:04x}: {hex_str:<47}  ascii={asc}  tile={til}")
