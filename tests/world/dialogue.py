"""Real NPC/locked-door dialogue: retain actors, colors, and current-build state.

Inputs are stock USA states positioned for Up interactions, with no temporary
player invincibility (which intentionally blinks). Requires Pillow for pixel QA.
This tests the visible scene as well as viewport geometry and guest state.
"""
import argparse
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

from PIL import Image

sys.dont_write_bytecode = True
spec = importlib.util.spec_from_file_location("state_helpers", Path(__file__).parents[1] / "link/integration.py")
state = importlib.util.module_from_spec(spec)
spec.loader.exec_module(state)


def world(data):
    return next(data[p+64:p+n] for tag, p, n in state.chunks(data)
                if tag == b"MOD " and data[p:p+64].split(b"\0")[0] == b"faxanadu.world")


def core(data):
    return [data[p-8:p+n] for tag, p, n in state.chunks(data) if tag != b"MOD "]


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for key in ("exe", "rom", "npc-state", "door-state", "out"):
        ap.add_argument("--" + key, type=Path, required=True)
    args = ap.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    empty = out / "stock-mods"
    empty.mkdir(exist_ok=True)
    checks = {}

    def run(name, source, duration=260, first=None, interp=False, mode="seamless"):
        folder = out / name
        folder.mkdir(exist_ok=True)
        start = struct.unpack_from("<I", source.read_bytes(), 28)[0] if first is None else first
        end = start + duration
        route = folder / "input.txt"
        events = [(10, "UP"), (18, "-"), (110, "B"), (118, "-")]
        if first is not None:
            events = [(110 - 41, "B"), (118 - 41, "-")]
        route.write_text("".join(f"{start+f} {b}\n" for f, b in events))
        cmd = [str(args.exe.resolve()), str(args.rom.resolve()), "--no-save", "--mods-root", str(empty),
               "--world-view", mode, "--world-size", "512x320", "--load-state", str(source),
               "--frames", str(end), "--input", str(route), "--present-out", str(folder / "frame.png"),
               "--present-every", "1", "--hash-out", str(folder / "hash.txt"),
               "--save-state", f"{end-1}:{folder}/final.cycstate"]
        if first is None:
            for f in (9, 15, 40, 80, 120):
                cmd += ["--save-state", f"{start+f}:{folder}/{f}.cycstate"]
        if interp:
            cmd += ["--interp-only"]
        (folder / "command.json").write_text(json.dumps(cmd, indent=2))
        with (folder / "run.log").open("w") as log:
            subprocess.run(cmd, cwd=folder, stdout=log, stderr=subprocess.STDOUT,
                           env=dict(os.environ, SDL_AUDIODRIVER="dummy", TEMP=str(out), TMP=str(out)),
                           creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0,
                           check=True, timeout=180)
        return folder

    for name, source in (("npc", args.npc_state.resolve()), ("door", args.door_state.resolve())):
        assert state.ram(source.read_bytes())[0xad] == 0, "Use a visible, nonblinking player"
        folder = run(name, source)
        interp = run(name + "-interp", source, interp=True)
        native = run(name + "-original", source, mode="off")
        samples = [(f, (folder / f"{f}.cycstate").read_bytes()) for f in (9, 15, 40, 80, 120)]
        poses = []
        for f, b in samples:
            d = world(b)
            stride = (len(d)-32)//83
            active = d[10]-1
            r = d[32+active*stride:32+(active+1)*stride]
            poses.append((f, d, r))
        frozen = [r[0x700:0x800] for f, d, r in poses if 15 <= f <= 80]
        checks[name+"_complete_frozen_actors"] = len(set(frozen)) == 1 and any(32 <= frozen[0][i]+1 < 240 for i in range(4, 256, 4))
        def visible(oam):
            return sorted(oam[i:i+4] for i in range(4, 256, 4) if 32 <= oam[i]+1 < 240)
        checks[name+"_opens_without_pose_jump"] = visible(poses[0][2][0x700:0x800]) == visible(frozen[0])
        checks[name+"_script_lifetime"] = all(d[19] == (15 <= f <= 80) for f, d, r in poses)
        # This fixture's actors stand below the message. Compare every frame
        # there, including the extended bounds; dimensions alone miss erasure.
        paths = sorted(folder.glob("frame_*.png"))
        images = [Image.open(p).convert("RGB") for p in paths]
        ypos = poses[1][2][0xa1] + 112  # floor-aligned 512x320 view
        box = (0, ypos, 512, min(ypos+40, 320))
        checks[name+"_visible_pose_stable"] = all(im.crop(box).tobytes() == images[15].crop(box).tobytes() for im in images[16:101])
        checks[name+"_adaptive_every_frame"] = all(im.size == (512, 320) for im in images)
        final = (folder / "final.cycstate").read_bytes()
        checks[name+"_guest_matches_original"] = core(final) == core((native / "final.cycstate").read_bytes())
        checks[name+"_backend_state"] = final == (interp / "final.cycstate").read_bytes()
        checks[name+"_backend_trace"] = (folder / "hash.txt").read_bytes() == (interp / "hash.txt").read_bytes()
        start = struct.unpack_from("<I", source.read_bytes(), 28)[0]
        replay = run(name+"-restore", folder / "40.cycstate", first=start+41, duration=219)
        checks[name+"_dialogue_restore"] = final == (replay / "final.cycstate").read_bytes()
        checks[name+"_restored_picture"] = (folder / "frame.png").read_bytes() == (replay / "frame.png").read_bytes()
        # Old cached room palettes may contain a building/portrait palette.
        # Poison every neighboring sprite palette without changing the scene.
        poison = bytearray((folder / "40.cycstate").read_bytes())
        p, n = next((p, n) for tag, p, n in state.chunks(poison) if tag == b"MOD " and poison[p:p+64].split(b"\0")[0] == b"faxanadu.world")
        d = world(poison)
        stride = (len(d)-32)//83
        for i in range(83):
            if i != d[10]-1:
                offset = p+64+32+i*stride+2048+8192+16
                poison[offset:offset+16] = bytes([0x30])*16
        path = out / (name+"-stale-sprites.cycstate")
        path.write_bytes(poison)
        fault = run(name+"-stale-sprites", path, first=start+41, duration=219)
        checks[name+"_global_sprite_colors"] = (fault / "frame.png").read_bytes() == (replay / "frame.png").read_bytes()
        checks[name+"_palette_keeps_execution"] = core((fault / "final.cycstate").read_bytes()) == core(final)
        # Retain per-frame hashes and representative raw pictures, not movies
        # full of uncompressed disposable PNGs.
        for folder in (folder, interp, native, replay, fault):
            paths = sorted(folder.glob("frame_*.png"))
            (folder / "frames.json").write_text(json.dumps([dict(file=p.name, sha256=hashlib.sha256(p.read_bytes()).hexdigest()) for p in paths], indent=2))
            for i, p in enumerate(paths):
                if i not in {0, 9, 15, 40, 80, 100, 110, 120, len(paths)-1}:
                    p.unlink()
    receipt = dict(executable_sha256=hashlib.sha256(args.exe.read_bytes()).hexdigest(), checks=checks)
    (out / "results.json").write_text(json.dumps(receipt, indent=2))
    print(json.dumps(receipt, indent=2))
    assert all(checks.values()), checks


if __name__ == "__main__":
    main()
