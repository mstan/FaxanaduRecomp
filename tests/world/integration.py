"""Qualify a supported right-hand seam, backends and current-build restore.

Supply a current-build stock USA state positioned at x=240 on a real supported
right exit. State preparation/teleports are external prerequisites, not coverage
claims. Outputs are isolated and native mantra saves are disabled.
"""
import argparse
import csv
import hashlib
import importlib.util
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
import zlib

sys.dont_write_bytecode = True

helpers = Path(__file__).parents[1] / "link/integration.py"
spec = importlib.util.spec_from_file_location("state_helpers", helpers)
state = importlib.util.module_from_spec(spec)
spec.loader.exec_module(state)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for key in ("exe", "rom", "state", "out"):
        ap.add_argument("--" + key, type=Path, required=True)
    args = ap.parse_args()
    out = args.out.resolve()
    out.mkdir(parents=True, exist_ok=True)
    image = args.rom.read_bytes()
    assert image[:4] == b"NES\x1a" and zlib.crc32(image[16:]) == 0x57dd23d1
    original = args.state.read_bytes()
    mem = state.ram(original)
    assert mem[0x9e] == 240 and mem[0x54] == 255 and mem[0x67] != 255
    expected = mem[0x67]
    start = struct.unpack_from("<I", original, 28)[0]
    empty = out / "stock-mods"
    empty.mkdir(exist_ok=True)
    env = dict(os.environ, TEMP=str(out), TMP=str(out), SDL_AUDIODRIVER="dummy")

    def run(name, initial, first, duration, events, interp=False, sample=None):
        folder = out / name
        folder.mkdir(exist_ok=True)
        route = folder / "input.txt"
        route.write_text("".join(f"{first + f} {b}\n" for f, b in events))
        end = first + duration
        cmd = [str(args.exe.resolve()), str(args.rom.resolve()), "--no-save",
               "--mods-root", str(empty), "--world-view", "seamless", "--world-size", "512x320",
               "--load-state", str(initial), "--frames", str(end), "--input", str(route),
               "--hash-out", str(folder / "hash.txt"), "--present-out", str(folder / "picture.png"),
               "--save-state", f"{end - 1}:{folder}/final.cycstate"]
        if interp:
            cmd += ["--interp-only"]
        if sample is not None:
            cmd += ["--save-state", f"{first + sample}:{folder}/sample.cycstate"]
        (folder / "command.json").write_text(json.dumps(cmd, indent=2))
        with (folder / "run.log").open("w") as log:
            subprocess.run(cmd, cwd=folder, stdout=log, stderr=subprocess.STDOUT,
                           env=dict(env, NESRECOMP_WORLD_TRACE=str(folder / "world.csv")),
                           creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0,
                           timeout=180, check=True)
        return folder

    native = run("native", args.state.resolve(), start, 120, [(0, "RIGHT"), (45, "-")], sample=20)
    interp = run("interp", args.state.resolve(), start, 120, [(0, "RIGHT"), (45, "-")], True)
    replay = run("replay", native / "sample.cycstate", start + 21, 99, [(0, "RIGHT"), (24, "-")])
    records = list(csv.DictReader((native / "world.csv").open()))
    final = (native / "final.cycstate").read_bytes()
    results = dict(
        reached_neighbor=state.ram(final)[0x63] == expected,
        continuous=all(int(r["scroll"]) == 255 for r in records),
        handed_off=any(int(r["handoffs"]) > 0 for r in records),
        no_failures=all(int(r["failures"]) == 0 for r in records),
        native_interpreter_state=final == (interp / "final.cycstate").read_bytes(),
        native_interpreter_trace=(native / "hash.txt").read_bytes() == (interp / "hash.txt").read_bytes(),
        current_build_restore=final == (replay / "final.cycstate").read_bytes(),
        restored_picture=(native / "picture.png").read_bytes() == (replay / "picture.png").read_bytes(),
    )
    # Original Start pause and Select inventory must stop room simulation
    # without discarding the expanded picture. Exercise real input handlers.
    for name, button, bank in (("pause", "START", 14), ("inventory", "SELECT", 12)):
        paused = run(name, args.state.resolve(), start, 80, [(10, button), (15, "-")], sample=25)
        paused_interp = run(name + "-interp", args.state.resolve(), start, 80,
                            [(10, button), (15, "-")], True)
        paused_bytes = (paused / "final.cycstate").read_bytes()
        paused_mem = state.ram(paused_bytes)
        def mod_records(data):
            return [data[p:p+n] for tag, p, n in state.chunks(data) if tag == b"MOD "]
        results[name + "_expanded"] = struct.unpack_from(">II", (paused / "picture.png").read_bytes(), 16) == (512, 320)
        results[name + "_native_mode"] = paused_mem[0x100] == bank and bool(paused_mem[0x120]) == (name == "pause")
        results[name + "_world_frozen"] = mod_records(paused_bytes) == mod_records((paused / "sample.cycstate").read_bytes())
        results[name + "_backend_state"] = paused_bytes == (paused_interp / "final.cycstate").read_bytes()
    receipt = dict(checks=results, executable_sha256=hashlib.sha256(args.exe.read_bytes()).hexdigest(),
                   source_state_sha256=hashlib.sha256(original).hexdigest(), rom_crc32="57dd23d1")
    (out / "results.json").write_text(json.dumps(receipt, indent=2))
    print(json.dumps(receipt, indent=2))
    assert all(results.values()), results


if __name__ == "__main__":
    main()
