# Windows runtime packaging (v2.3.2)

This patch packages the Microsoft C++ runtime DLLs required by the Windows x64
executable: `MSVCP140.dll`, `VCRUNTIME140.dll`, and `VCRUNTIME140_1.dll`.
The previous ZIP omitted them and required an existing VC redistributable.

The game executable and all other existing payload files are byte-for-byte
identical to v2.3.1; the patch adds the redistributable DLLs and this
packaging note. Existing renderers, settings, audio defaults, mods and saves
retain their previous behavior. No ROM, BIOS, player settings or saves ship.

The source pins the shared NESRecomp correction in
https://github.com/mstan/nesrecomp/pull/74 so future cycle builds stage the
compiler's redistributables beside the executable. Use the game's release
recipe, or `nesrecomp/tools/package_cycle_windows.ps1` for the generic package.
Runtime DLLs must come from the licensed Visual Studio redistributable directory.

Release reproduction: take `FaxanaduRecomp-USA-v2.3.1-windows-x64.zip` (SHA256
`4442cbb1b7f0be5b77bbf39a8b40a1289bddc66e6485642b0dfd7a1d14068e93`), preserve every original entry, and add this note as
`WINDOWS-RUNTIME.md` plus the three x64 runtime DLLs. Check the complete PE import
closure, launch the clean extraction, and compare hashes/screenshots to the
previous package. The retained release evidence records each added DLL's hash.

Tracking: `beads-2dw.1.97`.
