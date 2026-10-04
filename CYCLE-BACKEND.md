# Cycle backend

The default CMake backend is `cycle`; `-DNESRECOMP_BACKEND=legacy` retains the
function runtime. Both build with the pinned engine and UI submodules.

```powershell
cmake -S . -B build-cycle -DNESRECOMP_ROM="C:/ROMs/Faxanadu (USA).nes"
cmake --build build-cycle --config Release
```

Use the USA image with data CRC32 `57DD23D1`. ROMs and generated code are not
distributed. `NESRECOMP_ROOT`, `NESRECOMP_RECOMP_UI` and
`NESRECOMP_HOST_COMPILER` allow local checkout/compiler overrides. Regenerate
legacy `generated/faxanadu_*.c` from this ROM and `game.toml` before a legacy build.

The cycle adapter preserves the game's mantra format and existing
`faxanadu.srm` text saves, timestamped `faxanadu_mantra_log.txt` history,
`saves.txt` fallback and `--password` override. Automatic capture checks progress
every 900 frames, matching the old implementation. It calls the ROM's bank
switch and encoder on an isolated machine, then restores CPU, memory, mapper
and clocks exactly. The launcher retains its Mantra editor. `--no-save`
disables sidecar loading/writing and that editor; an explicit `--password`
still works. Cycle save states use `.cycstate` and do not replace legacy states.

Optional text and tile tools remain available: `--text-overrides <json>`,
`--tiles <dir>`, `--tile-dump`, `--tile-compile <dir>`, and executable-relative
`tiles/manifest.json` autodetection. Existing encodings, manifests, PNG/cache
formats and hot reload are retained. PRG text edits use the cycle interpreter
so generated constants cannot bypass a replacement. Ordinary play stays native.
The cycle TCP server uses `--tcp <port>` and offers `mantra_now` and
`mantra_save` alongside the shared runtime commands. The old verify/oracle
debug surface remains available in legacy builds.

Validation on 2026-10-04: 1,800 gameplay frames match native, interpreter and
TriCNES traces/memory/CPU at alignments 0, 1 and 2. Native/interpreter hardware
hashes and saved-state continuation match exactly. Repeated mantra captures
leave complete state files identical, including unused stack bytes. The game
accepts a captured mantra and resumes in town. Private-directory tests cover
save/history dirty checks, automatic capture with controlled progress, restart
prefill, CLI precedence, `--no-save`, legacy fallback, text replacement, tile
round trips, visible custom tiles and PNG compilation. The actual launcher's
Mantra editor and no-save omission were visually checked. Both backends compile.

The owner played the cycle preview in town and confirmed it plays correctly.
These checks
cover the tested routes, rather than every area, boss or ending. No merge has
occurred.
