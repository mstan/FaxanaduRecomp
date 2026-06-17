# Release procedure

How to cut a FaxanaduRecomp Windows release. Per-version notes live in
`RELEASE_NOTES.md` (and on the GitHub release itself).

## Asset convention: one zip, only a zip

Every release ships exactly one asset — never a bare exe (it is broken without
`SDL2.dll` and the `launcher/` assets):

| asset | contents |
|---|---|
| `FaxanaduRecomp-windows-x64.zip` | `FaxanaduRecomp.exe` + `SDL2.dll` + `keybinds.ini` + `launcher/` + `README.txt` |

The zip never contains `debug.ini`, `config.ini`, a ROM (`baserom.nes`), or the
player's mantra save (`faxanadu.srm`) / logs.

## Steps

1. Make sure the tree is the release commit: game repo `master`, and the
   `nesrecomp/` junction checked out at the SHA in `nesrecomp.pin`. `generated/`
   is committed and valid for the pinned recompiler (the build re-regens it
   byte-identically anyway).

2. Build + stage the zip:

   ```powershell
   powershell -File tools\make_release.ps1            # builds + zips
   powershell -File tools\make_release.ps1 -SkipBuild # zip an existing build_release
   ```

   The zip lands in `release\` (gitignored). `make_release.ps1` calls
   `build_all.bat` (plain regen, `ENABLE_NESTOPIA_ORACLE=OFF`,
   `NESRECOMP_REVERSE_DEBUG=OFF`) and strips `debug.ini`.

3. Smoke-test the zip from a scratch directory (extract, run, point at a ROM,
   confirm the launcher + game boot and a save round-trips).

4. Tag and publish:

   ```powershell
   git tag vX.Y.Z ; git push origin master --tags
   gh release create vX.Y.Z release\FaxanaduRecomp-windows-x64.zip `
       --title "vX.Y.Z — <headline>" --notes-file RELEASE_NOTES.md
   ```

Linux / macOS builds use `tools/build-linux.sh` / `tools/build-macos.sh`; only
Windows is cut here.
