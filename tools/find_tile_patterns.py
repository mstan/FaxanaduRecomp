#!/usr/bin/env python3
"""Search all ROM banks for START/CONTINUE tile patterns."""
ROM = 'F:/Projects/nesrecomp-release/FaxanaduRecomp/baserom.nes'
PRG_BASE = 16
BANK_SIZE = 16384
with open(ROM, 'rb') as f:
    rom = f.read()

START = bytes([0xf2, 0xf3, 0xe0, 0xf1, 0xf3])
CONT  = bytes([0xe2, 0xee, 0xed, 0xf3, 0xe8, 0xed, 0xf4, 0xe4])

for bank in range(16):
    data = rom[PRG_BASE + bank*BANK_SIZE : PRG_BASE + (bank+1)*BANK_SIZE]
    for pat, name in [(START, 'START'), (CONT, 'CONTINUE')]:
        pos = 0
        while True:
            pos = data.find(pat, pos)
            if pos == -1:
                break
            addr = 0x8000 + pos
            ctx = data[max(0, pos-8):pos+len(pat)+8]
            print('bank%d $%04X: %s ctx=%s' % (bank, addr, name, ctx.hex()))
            pos += 1
