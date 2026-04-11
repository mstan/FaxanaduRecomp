#!/usr/bin/env python3
"""Search Faxanadu ROM for text strings in various tile encodings."""
import sys

ROM_PATH = "F:/Projects/nesrecomp-release/FaxanaduRecomp/baserom.nes"

with open(ROM_PATH, "rb") as f:
    rom = f.read()

print(f"ROM size: {len(rom)} bytes")
prg_banks = rom[4]
chr_banks = rom[5]
print(f"PRG banks (16KB): {prg_banks}, CHR banks (8KB): {chr_banks}")

# Try many A-base offsets for uppercase letters
targets = ["START", "CONTINUE"]
bases = list(range(0, 256, 1))  # brute force all 256 possible A-offsets

for target in targets:
    print(f"\n=== Searching for '{target}' ===")
    found_any = False
    for base in bases:
        chars = [base + (ord(c) - ord('A')) for c in target]
        if any(c > 255 for c in chars):
            continue
        pattern = bytes(chars)
        pos = 0
        while True:
            pos = rom.find(pattern, pos)
            if pos == -1:
                break
            found_any = True
            bank_num = (pos - 16) // 16384 if pos >= 16 else -1
            bank_offset = (pos - 16) % 16384 + 0x8000 if pos >= 16 else pos
            ctx = rom[max(0, pos - 4):pos + len(target) + 4]
            print(f"  A=0x{base:02X}: ROM 0x{pos:05x} bank{bank_num} addr 0x{bank_offset:04x} "
                  f"bytes={pattern.hex()} ctx={ctx.hex()}")
            pos += 1
    if not found_any:
        print("  (not found in any encoding)")

# Also search for "START" where letters might have gaps or different mapping
# Try lowercase too
print("\n=== Searching ASCII 'Start' (mixed case) ===")
for target_bytes in [b"Start", b"start", b"START", b"CONTINUE", b"Continue"]:
    pos = rom.find(target_bytes)
    if pos != -1:
        bank_num = (pos - 16) // 16384 if pos >= 16 else -1
        print(f"  '{target_bytes.decode()}' found at ROM 0x{pos:05x} bank{bank_num}")
