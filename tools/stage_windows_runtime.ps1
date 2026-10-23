param([Parameter(Mandatory)][string]$BuildDir, [string]$RedistDir)
$ErrorActionPreference = 'Stop'
$build = (Resolve-Path -LiteralPath $BuildDir).Path
$bin = if (Test-Path -LiteralPath (Join-Path $build 'Release/FaxanaduRecomp.exe')) { Join-Path $build 'Release' } else { $build }
$required = @('msvcp140.dll', 'vcruntime140.dll', 'vcruntime140_1.dll')
if (-not $RedistDir -and @($required | Where-Object { -not (Test-Path -LiteralPath (Join-Path $bin $_)) }).Count -eq 0) { return }

# Read the configured compiler's install directory; never crawl a drive or
# copy runtime DLLs from System32. Accept an explicit licensed redist directory.
$candidates = @()
if ($RedistDir) { $candidates += $RedistDir }
if ($env:VCToolsRedistDir) { $candidates += Join-Path $env:VCToolsRedistDir 'x64/Microsoft.VC143.CRT' }
$cmakeFiles = Join-Path $build 'CMakeFiles'
foreach ($version in @(Get-ChildItem -LiteralPath $cmakeFiles -Directory)) {
    $compilerFile = Join-Path $version.FullName 'CMakeCXXCompiler.cmake'
    if (-not (Test-Path -LiteralPath $compilerFile)) { continue }
    $text = Get-Content -LiteralPath $compilerFile -Raw
    $match = [regex]::Match($text, 'set\(CMAKE_CXX_COMPILER "(.+?/VC)/Tools/MSVC/')
    if (-not $match.Success) { continue }
    $redistRoot = Join-Path $match.Groups[1].Value 'Redist/MSVC'
    if (-not (Test-Path -LiteralPath $redistRoot)) { continue }
    foreach ($redist in @(Get-ChildItem -LiteralPath $redistRoot -Directory | Sort-Object Name -Descending)) {
        $candidates += Join-Path $redist.FullName 'x64/Microsoft.VC143.CRT'
    }
}
foreach ($candidate in $candidates) {
    $missing = @($required | Where-Object { -not (Test-Path -LiteralPath (Join-Path $candidate $_)) })
    if ($missing.Count) { continue }
    foreach ($dll in $required) { Copy-Item -LiteralPath (Join-Path $candidate $dll) -Destination (Join-Path $bin $dll) -Force }
    Write-Output "Staged x64 VC runtimes from $candidate"
    return
}
throw 'Missing licensed x64 Visual C++ redistributables. Supply -RedistDir with Microsoft.VC143.CRT.'
