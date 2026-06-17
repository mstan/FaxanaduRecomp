# FaxanaduRecomp v2.2.0 — Password (Mantra) Save System + HUD fix

## Highlights

### Automatic password (mantra) saves
Faxanadu saves progress with a "mantra" (password) rather than battery SRAM.
This release captures your mantra **automatically** as you play — stored in
`faxanadu.srm` next to the exe — and **auto-fills it on the password screen**
when you choose CONTINUE. No more copying mantras by hand. Every distinct mantra
is also appended to a timestamped `faxanadu_mantra_log.txt`, so you can roll back
to any earlier point in your playthrough.

### Editable mantra in the launcher
The pre-boot launcher's **SAVE panel** now shows your current mantra and lets you
**edit it — or paste an older/shared one — behind a confirmation step**, so you
can jump to a specific save state from the launcher before the game even boots.

### HUD corruption fix
Fixed the status bar filling with garbage tiles after a left/right screen
transition. The sprite-0 HUD-split was failing to activate on screens whose base
nametable is NT1, so the HUD region fell through to the game background; the HUD
now renders correctly on every screen, both walk directions. (Framework fix in
NESRecomp — also benefits other NES titles.)

## Install
Download `FaxanaduRecomp-windows-x64.zip`, extract anywhere, and run
`FaxanaduRecomp.exe`. On first launch, select your legally-obtained **Faxanadu
(USA)** ROM — **no ROM is included**. The path is remembered afterward.

Controls (configurable in `keybinds.ini`): arrows = D-Pad, Z = A, X = B,
Enter = Start, Tab = Select. F5 turbo, F6/F7 save/load state.
