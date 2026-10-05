param([string]$Rom, [string]$BuildDir='build_release', [string]$EngineRoot, [string]$RecompUi, [switch]$SkipBuild)
$ErrorActionPreference='Stop'
$root=Split-Path -Parent $PSScriptRoot
if (-not $EngineRoot) { $EngineRoot=Join-Path $root 'nesrecomp' }
if (-not $Rom) {
    $images=@(Get-ChildItem -LiteralPath $root -File | Where-Object { $_.Extension -ieq '.nes' })
    if ($images.Count -eq 1) { $Rom=$images[0].FullName }
}
& (Join-Path $EngineRoot 'tools/package_cycle_windows.ps1') -ProjectRoot $root -Target 'FaxanaduRecomp' -Title 'Faxanadu' -BuildDir $BuildDir -Rom $Rom -EngineRoot $EngineRoot -RecompUi $RecompUi -SkipBuild:$SkipBuild -GameNotes ''
