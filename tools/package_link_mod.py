"""Create the data-only Play as Link package. Never reads a ROM or asset dump."""
import argparse
from pathlib import Path
import zipfile

root = Path(__file__).resolve().parents[1]
ap = argparse.ArgumentParser(description=__doc__)
ap.add_argument("--out", required=True, type=Path)
args = ap.parse_args()
manifest = root / "mods/preloaded/packages/faxanadu.gameplay.zelda2-link/1.0.0/manifest.toml"
readme = """Play as Link (Experimental) for FaxanaduRecomp

Install this .nesmod through Mods in a compatible FaxanaduRecomp build.
Select your Zelda II: The Adventure of Link (USA) ROM, enable Play as Link,
and launch your unmodified Faxanadu USA ROM. Both ROMs stay on your computer.

A: Jump. B: Sword. Down: Crouch. Air Up/Down: Upstab/Downstab.
Select: Spell picker. A confirms and B cancels. Up+B: Cast selected spell.
Start: Faxanadu inventory (B cancels). Down+Start: Use selected Faxanadu item.
C: Cast shortcut. V: Spell picker shortcut. Both can be rebound in config.ini.
Sword beams require full health. Spells use Faxanadu MP. All abilities are
available immediately; Faxanadu equipment, quest gates and mantras remain native.

This archive contains metadata and this readme only. The trusted gameplay
plugin is linked into the compatible game executable. No Nintendo ROM,
graphics, music, sound samples, patches, or executable code are in this package.
"""
args.out.parent.mkdir(parents=True, exist_ok=True)
with zipfile.ZipFile(args.out, "w", zipfile.ZIP_DEFLATED) as archive:
    archive.writestr("manifest.toml", manifest.read_bytes())
    archive.writestr("README.txt", readme)
print(args.out)
