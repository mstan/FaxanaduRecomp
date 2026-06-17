<#
make_release.ps1 -- build the Windows release zip for FaxanaduRecomp.

Ships ONE windows zip (never a bare exe -- the exe needs SDL2.dll and the
launcher/ assets):

  FaxanaduRecomp-windows-x64.zip
      FaxanaduRecomp.exe + SDL2.dll + keybinds.ini + launcher/ + README.txt

The script builds build_release\ via build_all.bat (plain regen, oracle OFF,
reverse-debug OFF), then stages and zips. The zip lands in release\ (gitignored)
and never contains debug.ini, config.ini, a ROM (baserom.nes), or the player's
mantra save (faxanadu.srm) / logs.

Publish AFTER smoke-testing the zip from a scratch directory:

  gh release create vX.Y.Z release\FaxanaduRecomp-windows-x64.zip `
      --title "vX.Y.Z -- <headline>" --notes-file RELEASE_NOTES.md

Usage: powershell -File tools\make_release.ps1 [-SkipBuild]
#>
param(
  [switch]$SkipBuild
)
$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $PSScriptRoot
$bin  = Join-Path $root 'build_release'
$out  = Join-Path $root 'release'
New-Item -ItemType Directory -Force $out | Out-Null

if (-not $SkipBuild) {
  & cmd /c (Join-Path $root 'build_all.bat')
  if ($LASTEXITCODE -ne 0) { throw "build_all.bat failed ($LASTEXITCODE)" }
}

$exe = Join-Path $bin 'FaxanaduRecomp.exe'
if (-not (Test-Path $exe)) { throw "missing $exe -- run build_all.bat first" }

$readme = @'
Faxanadu - Static Recompilation
================================

A native PC build of Faxanadu, produced by statically recompiling the NES
ROM's 6502 code to C with the NESRecomp framework (github.com/mstan/nesrecomp).

No ROM is included. On first launch, select your legally-obtained Faxanadu
(USA) ROM. The path is remembered for future launches.

PASSWORD / MANTRA SAVE
----------------------
Faxanadu saves progress with a "mantra" (password) rather than battery-backed
SRAM. This build captures your mantra automatically as you play and stores it
in faxanadu.srm next to the exe, then auto-fills it on the password screen when
you choose CONTINUE -- so you can resume without ever copying a mantra by hand.
The pre-boot launcher's SAVE panel shows your current mantra and lets you edit
it (or paste an older one, with a confirmation step) to roll back to an earlier
point. A rolling history of captured mantras is also kept in
faxanadu_mantra_log.txt.

Controls: arrow keys = D-Pad, Z = A, X = B, Enter = Start, Tab = Select.
F5 turbo, F6 save state, F7 load state. Gamepads are supported; all bindings
are configurable in keybinds.ini.
'@

$stage = Join-Path $out 'stage'
if (Test-Path $stage) { Remove-Item -Recurse -Force $stage }
New-Item -ItemType Directory -Force $stage | Out-Null

Copy-Item $exe $stage
foreach ($extra in 'SDL2.dll', 'keybinds.ini') {
  $p = Join-Path $bin $extra
  if (Test-Path $p) { Copy-Item $p $stage }
}
# The pre-boot GUI launcher (and its SAVE/mantra panel) needs its assets.
$launcher = Join-Path $bin 'launcher'
if (Test-Path $launcher) { Copy-Item -Recurse $launcher (Join-Path $stage 'launcher') }

$readme | Out-File -Encoding ascii (Join-Path $stage 'README.txt')

# Belt-and-braces: never ship debug/dev artifacts, a ROM, or the player's save.
foreach ($banned in 'debug.ini', 'config.ini', 'baserom.nes', 'faxanadu.srm',
                    'faxanadu_mantra_log.txt', 'rom.cfg', 'dispatch_misses.log') {
  $p = Join-Path $stage $banned
  if (Test-Path $p) { Remove-Item $p }
}

$zip = Join-Path $out 'FaxanaduRecomp-windows-x64.zip'
if (Test-Path $zip) { Remove-Item $zip }
Compress-Archive -Path (Join-Path $stage '*') -DestinationPath $zip
Remove-Item -Recurse -Force $stage
Write-Host "staged $zip"
