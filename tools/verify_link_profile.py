"""Verify every Link hook content key against the supported owner ROM."""
import argparse
import json
from pathlib import Path
import tomllib
import zlib

ap = argparse.ArgumentParser(description=__doc__)
ap.add_argument("--rom", required=True, type=Path)
args = ap.parse_args()
root = Path(__file__).resolve().parents[1]
data = args.rom.read_bytes()
assert data[:4] == b"NES\x1a" and len(data) == 262160
data = data[16:]
assert zlib.crc32(data) == 0x57dd23d1, "Faxanadu USA ROM required"
config = tomllib.loads((root / "game.toml").read_text(encoding="utf-8"))
hooks = [h for h in config["mod_function_hook"] if h["id"].startswith("faxanadu.link.")]
assert len(hooks) == 19
for hook in hooks:
    offset = hook["bank"] * 16384 + (hook["addr"] & 0x3fff)
    key = bytes.fromhex(hook["bytes"])
    assert data[offset:offset + len(key)] == key, hook["id"]
profile = json.loads((root / "mods/zelda2/profile.json").read_text())
assert profile["rom_crc32"] == "57dd23d1"
assert int(profile["symbols"]["Player_HitSpriteWithWeapon"], 16) < 0x883a < 0x88d0
print(f"PASS {len(hooks)} ROM-bound Link hooks")
