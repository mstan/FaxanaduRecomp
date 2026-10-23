param([string]$Rom, [string]$BuildDir='build_release', [string]$EngineRoot, [string]$RecompUi, [string]$RedistDir, [switch]$SkipBuild)
$ErrorActionPreference='Stop'
$root=Split-Path -Parent $PSScriptRoot
if (-not $EngineRoot) { $EngineRoot=Join-Path $root 'nesrecomp' }
if (-not $Rom) {
    $images=@(Get-ChildItem -LiteralPath $root -File | Where-Object { $_.Extension -ieq '.nes' })
    if ($images.Count -eq 1) { $Rom=$images[0].FullName }
}
$notes = @'
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
$package = Join-Path $buildPath 'Release/Play-as-Link.nesmod'
if (Test-Path -LiteralPath $package) {
    Copy-Item -LiteralPath $package -Destination (Join-Path $root 'release/Play-as-Link.nesmod') -Force
}
