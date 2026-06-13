# Faxanadu — macOS (Apple Silicon) build

Native arm64 macOS build of Faxanadu, attached to release **v2.1.0** as
`FaxanaduRecomp-macos-arm64.zip`.

## What this is
- The original game statically recompiled to native arm64 (no emulator core shipped).
- Self-contained `.app`: SDL2 bundled via `@executable_path`, ad-hoc codesigned.
- Verified by manual play on Apple Silicon (looks/sounds correct on the golden path).

## Install
1. Download `FaxanaduRecomp-macos-arm64.zip` from the **v2.1.0** release and unzip.
2. First launch: right-click `Faxanadu.app` -> Open (ad-hoc signed), or
   `xattr -dr com.apple.quarantine "Faxanadu.app"`.
3. ROM not included — supply your own dump: Faxanadu (USA) .nes dump
4. Run: `"Faxanadu.app/Contents/MacOS/Faxanadu" /path/to/rom`

## Build it yourself
`scripts/release-mac.sh` reproduces this artifact (build -> .app -> zip);
`scripts/release-mac.sh --publish` re-attaches it to the latest release.
Requires: `brew install cmake ninja sdl2 dylibbundler` on Apple Silicon.
