#!/usr/bin/env python3
"""Search ROM for code that loads specific 16-bit addresses (LE pointer references)."""

ROM_PATH = "F:/Projects/nesrecomp-release/FaxanaduRecomp/baserom.nes"

with open(ROM_PATH, "rb") as f:
    rom = f.read()

# Bank layout: 16 PRG banks of 16KB each, starting at ROM offset 16
PRG_BASE = 16
BANK_SIZE = 16384

def rom_offset_to_bank_addr(rom_pos):
    if rom_pos < PRG_BASE:
        return (-1, rom_pos)
    offset = rom_pos - PRG_BASE
    bank = offset // BANK_SIZE
    addr = (offset % BANK_SIZE) + 0x8000
    return (bank, addr)

def search_addr(target_addr, label):
    lo = target_addr & 0xFF
    hi = (target_addr >> 8) & 0xFF
    pattern = bytes([lo, hi])
    print(f"\n=== References to {label} (${target_addr:04X} -> {lo:02x} {hi:02x}) ===")
    pos = PRG_BASE
    while True:
        pos = rom.find(pattern, pos)
        if pos == -1:
            break
        bank, addr = rom_offset_to_bank_addr(pos)
        # Show context: 4 bytes before, the 2 pointer bytes, 4 bytes after
        ctx_start = max(PRG_BASE, pos - 6)
        ctx = rom[ctx_start:pos + 8]
        # Try to identify the instruction at pos-1 (LDA#, LDX#, LDY# = A9/A2/A0, or JMP/JSR = 4C/20)
        preceding = rom[pos - 1] if pos > 0 else 0
        instr_hint = {0xA9: "LDA #", 0xA2: "LDX #", 0xA0: "LDY #",
                      0x4C: "JMP", 0x20: "JSR", 0xAD: "LDA abs",
                      0x85: "STA zp", 0x8D: "STA abs"}.get(preceding, f"?{preceding:02x}")
        print(f"  bank{bank:2d} ${addr:04X}: preceding byte=${preceding:02x} ({instr_hint}), "
              f"ctx={ctx.hex()}")
        pos += 1

# The key addresses we want to find references to
search_addr(0x9DBD, "START string")
search_addr(0x9DC3, "CONTINUE string")
search_addr(0x91BE, "Mantra dialogue string")

# Also search for the string block base $9DB0
search_addr(0x9DB0, "menu string block base")
search_addr(0x9DA0, "menu text area base")
