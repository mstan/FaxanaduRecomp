# Windows release procedure

Build the cycle backend from the pinned `nesrecomp` and `recomp-ui` submodules
using an original Faxanadu USA ROM. No ROM or player data ships.

```powershell
powershell -File tools/make_release.ps1 -Rom <USA-ROM>
# Or package an already validated cycle build:
powershell -File tools/make_release.ps1 -Rom <USA-ROM> -BuildDir <build> -SkipBuild
```

The single release asset is `release/FaxanaduRecomp-windows-x64.zip`. It contains
the executable, SDL2 and licensed Visual C++ runtimes, launcher assets, licenses,
instructions, and the preloaded mod catalog. Both Seamless and Play as Link are
disabled by default and marked Experimental. No developer profile, ROM path,
native save, save state, log or extracted owner graphics belongs in the ZIP.

Extract into an isolated directory and verify the launcher, first-row Seamless
entry and Experimental badge, disabled default, enabled catalog path, gameplay
and current-build save/load. Verify the PE runtime dependency closure. Automated
launches are hidden and muted; preserve the owner's saves and settings.

After validation and the owner's merge/release authorization, merge to `master`,
push the pinned engine commit before the game commit, and publish:

```powershell
git tag vX.Y.Z
git push origin master vX.Y.Z
gh release create vX.Y.Z release/FaxanaduRecomp-windows-x64.zip `
  --title "vX.Y.Z - <headline>" --notes-file RELEASE_NOTES.md
```

Keep one current Faxanadu ZIP in `G:/Nextcloud/Games/NES`. Verify a replacement
before removing superseded Faxanadu archives; preserve saves and other games.
Keep release evidence and checksum records in the workspace.
