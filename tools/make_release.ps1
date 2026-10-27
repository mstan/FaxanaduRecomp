param([string]$Rom, [string]$BuildDir='build_release', [string]$EngineRoot, [string]$RecompUi, [string]$RedistDir, [switch]$SkipBuild)
$ErrorActionPreference='Stop'
$root=Split-Path -Parent $PSScriptRoot
if (-not $EngineRoot) { $EngineRoot=Join-Path $root 'nesrecomp' }
if (-not $Rom) {
    $images=@(Get-ChildItem -LiteralPath $root -File | Where-Object { $_.Extension -ieq '.nes' })
    if ($images.Count -eq 1) { $Rom=$images[0].FullName }
}
$notes = @'
Optional experimental Seamless mod: open Mods and enable Seamless, the first
mod in the list and marked Experimental. Connected rooms form a continuous
world with moving neighboring actors and adaptive Fit to screen.
Resize the window freely. Mouse wheel changes pixel zoom; F4 shows the map.
Start pauses, Select opens native inventory, B closes it.
Doors and scripted region changes retain their native transitions.
Seamless passed a preliminary owner playtest; cross-room combat/projectiles
and broader progression coverage remain incomplete. It is disabled by default
and cannot be combined with Play as Link. Both mods are local-play only.

Optional experimental Play as Link mod: open Mods, select your Zelda II USA ROM,
enable Play as Link (marked Experimental), then launch Faxanadu. Both original ROMs remain on your computer.
A jumps, B uses the sword, Down crouches; airborne Up/Down stab vertically.
Select opens magic; A confirms, B cancels. Up+B casts. C and V are optional
cast/picker shortcuts (config.ini [Game] LinkCastKey / LinkPickerKey).
Start opens the Faxanadu inventory; Down+Start uses the selected native item.
All eight spells are unlocked and use native MP. Sword beams require full HP.
The mod is disabled by default. Native equipment, quests and mantras remain.
'@
$buildPath = if ([IO.Path]::IsPathRooted($BuildDir)) { $BuildDir } else { Join-Path $root $BuildDir }
if (-not $SkipBuild) {
    & (Join-Path $PSScriptRoot 'build.ps1') -Rom $Rom -BuildDir $buildPath -EngineRoot $EngineRoot -RecompUi $RecompUi
    if ($LASTEXITCODE) { throw 'Cycle build failed.' }
}
& (Join-Path $PSScriptRoot 'stage_windows_runtime.ps1') -BuildDir $buildPath -RedistDir $RedistDir
& (Join-Path $EngineRoot 'tools/package_cycle_windows.ps1') -ProjectRoot $root -Target 'FaxanaduRecomp' -Title 'Faxanadu' -BuildDir $buildPath -Rom $Rom -EngineRoot $EngineRoot -RecompUi $RecompUi -SkipBuild -GameNotes $notes
