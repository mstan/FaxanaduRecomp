# FaxanaduRecomp

Static recompilation of Faxanadu (NES) for native PC.
Built with [NESRecomp](https://github.com/yourusername/nesrecomp) framework.

## Prerequisites

- Windows 10+, Visual Studio 2022
- CMake 3.20+
- SDL2 (bundled in `nesrecomp/runner/external/SDL2/`)

## Build

```
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release
```

## Run

Place your Faxanadu ROM as `baserom.nes` in the `build/Release/` directory, then:

```
build/Release/FaxanaduRecomp.exe
```

The launcher will prompt for a ROM file if none is found, and verifies the CRC32
against the expected value (`0x42C4EC66`) before starting.

## Game-specific Options

```
FaxanaduRecomp.exe [ROM] --password STRING
```

`--password STRING` — Auto-fill the Faxanadu mantra (password) on the password entry screen.
Example: `--password "k8fPcv?,TwSYzGZQhMIQhCEA"`

## Input Scripts and Save States

```
FaxanaduRecomp.exe baserom.nes --script C:/temp/my_session.txt
FaxanaduRecomp.exe baserom.nes --loadstate C:/temp/quicksave.sav
```

## Architecture

This is a **static recompiler**, not an emulator. The 6502 machine code in the ROM
has been translated to C by [NESRecomp](nesrecomp/) and compiled to native x64.

| File | Purpose |
|------|---------|
| `extras.c` | Faxanadu-specific hooks (password injection) |
| `game.cfg` | Recompiler config (dispatch tables, trampolines) |
| `baserom_annotations.csv` | Address annotations for generated code |
| `generated/faxanadu_full.c` | Recompiled 6502 code (committed) |
| `generated/faxanadu_dispatch.c` | Dispatch table (committed) |
| `reference/` | Reference screenshots for visual regression |
