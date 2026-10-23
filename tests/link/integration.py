"""Headless Link integration campaign using a stock post-intro checkpoint.

All fixtures and evidence go under --out. HP/MP grants are journaled; no
quest, enemy, or victory flags are set. Games run without saving progress.
"""
import argparse
import csv
import hashlib
import json
import os
from pathlib import Path
import shutil
import struct
import subprocess
import zlib

ROOT = Path(__file__).resolve().parents[2]
PACKAGE = "faxanadu.gameplay.zelda2-link"
FEATURE = "play-as-link"
RECORD = b"faxanadu.zelda2.adapter"


def chunks(data):
    assert data[:8] == b"CYCSTATE" and struct.unpack_from("<I", data, 8)[0] in (2, 4)
    pos = 32
    while pos < len(data):
        tag, size = struct.unpack_from("<4sI", data, pos)
        pos += 8
        assert pos + size <= len(data)
        yield tag, pos, size
        pos += size
        if tag == b"END ":
            assert pos == len(data)
            return
    raise AssertionError("Missing END chunk")


def ram(data):
    pos, size = next((p, n) for t, p, n in chunks(data) if t == b"HW  ")
    assert size == 2072, "Unqualified hardware ABI"
    return data[pos + 23:pos + 23 + 2048]


def record(data):
    return next((data[p + 64:p + n] for t, p, n in chunks(data)
                 if t == b"MOD " and data[p:p + 64].split(b"\0")[0] == RECORD), b"")


def fixture(source, target, writes):
    original = source.read_bytes()
    data = bytearray(original)
    pos, size = next((p, n) for t, p, n in chunks(data) if t == b"HW  ")
    assert size == 2072
    changes = []
    for address, value in writes.items():
        changes.append(dict(address=f"{address:04x}", before=data[pos + 23 + address], after=value))
        data[pos + 23 + address] = value
    target.write_bytes(data)
    target.with_suffix(".fixture.json").write_text(json.dumps(dict(
        source=str(source), source_sha256=hashlib.sha256(original).hexdigest(),
        purpose="HP/MP grants for ability tests; no progress or success flags changed", changes=changes), indent=2))


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ("exe", "faxanadu-rom", "zelda2-rom", "baseline-state", "out"):
        ap.add_argument("--" + name, required=True, type=Path)
    args = ap.parse_args()
    out = args.out.resolve()
    if os.name == "nt" and out.drive.lower() == "c:":
        raise SystemExit("Use F: or G: for QA output")
    out.mkdir(parents=True, exist_ok=True)
    owner = args.zelda2_rom.resolve()
    image = owner.read_bytes()
    assert hashlib.sha1(image[16:] if image[:4] == b"NES\x1a" else image).hexdigest() == "11333adb723a5975e0ecca3aee8f4747aa8d2d26"
    assert zlib.crc32(args.faxanadu_rom.read_bytes()[16:]) == 0x57dd23d1
    catalog = out / "catalog"
    shutil.copytree(ROOT / "mods/preloaded/packages", catalog / "packages", dirs_exist_ok=True)
    selection = f'''[[feature]]
package_id = "{PACKAGE}"
id = "{FEATURE}"
enabled = true
[[resource]]
package_id = "{PACKAGE}"
id = "zelda2-us"
path = {json.dumps(owner.as_posix())}
'''
    (catalog / "state.toml").write_text(selection)
    env = dict(os.environ, TEMP=str(out), TMP=str(out), SDL_AUDIODRIVER="dummy", LNG_TEST_HIDDEN="1")
    report = []

    def run(tag, source, end, route, saves=(), mode="native", catalog_root=catalog, expected=0):
        folder = out / tag
        folder.mkdir(exist_ok=True)
        cmd = [str(args.exe.resolve()), str(args.faxanadu_rom.resolve()), "--no-save", "--load-state", str(source),
               "--frames", str(end), "--input", str(route), "--hash-out", str(folder / "hash.txt"),
               "--present-out", str(folder / "picture.png"), "--save-state", f"{end - 1}:{folder}/final.cycstate"]
        if catalog_root:
            cmd += ["--mods-root", str(catalog_root)]
        if mode == "interp":
            cmd += ["--interp-only"]
        for frame, path in saves:
            cmd += ["--save-state", f"{frame}:{path}"]
        (folder / "command.json").write_text(json.dumps(cmd, indent=2))
        with (folder / "run.log").open("w") as log:
            p = subprocess.run(cmd, cwd=folder, env=dict(env, NESRECOMP_FTRING_DUMP=str(folder / "controller.csv")),
                               stdout=log, stderr=subprocess.STDOUT, timeout=180,
                               creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0)
        if expected == 0:
            assert p.returncode == 0, (tag, (folder / "run.log").read_text())
        else:
            assert p.returncode != 0, tag
        return folder

    base = args.baseline_state.resolve()
    assert not record(base.read_bytes()), "Supply an unmodified stock checkpoint"
    first = struct.unpack_from("<I", base.read_bytes(), 28)[0]
    source = out / "full.cycstate"
    fixture(base, source, {0x431:80, 0x432:0, 0x39a:80})
    costs = [10, 5, 32, 25, 10, 10, 10, 40]
    names = ["shield", "jump", "life", "fairy", "fire", "reflect", "spell", "thunder"]
    for index, name in enumerate(names):
        current = source
        if index == 2:
            current = out / "injured.cycstate"
            fixture(source, current, {0x431:32})
        at = first + 20
        events = [(first, "-"), (first + 10, "SELECT"), (first + 11, "-")]
        for _ in range(index):
            events += [(at, "DOWN"), (at + 1, "-")]
            at += 3
        events += [(at, "A"), (at + 1, "-"), (at + 10, "UP B"), (at + 11, "-")]
        if index == 3:
            events += [(at + 20, "UP RIGHT"), (at + 50, "-")]
        else:
            events += [(at + 22, "B"), (at + 23, "-"), (at + 40, "A"), (at + 50, "-")]
        route = out / f"{name}.input"
        route.write_text("".join(f"{f} {b}\n" for f, b in sorted(events)))
        end = at + 100
        checkpoints = [(first + 14, out / f"{name}-picker.cycstate"), (at + 30, out / f"{name}-active.cycstate")]
        native = run(name + "-native", current, end, route, checkpoints)
        interp = run(name + "-interp", current, end, route, mode="interp")
        data = (native / "final.cycstate").read_bytes()
        assert data == (interp / "final.cycstate").read_bytes(), (name, "native/interpreter state")
        assert (native / "hash.txt").read_bytes() == (interp / "hash.txt").read_bytes(), (name, "machine traces")
        assert (native / "picture.png").read_bytes() == (interp / "picture.png").read_bytes(), (name, "presentation")
        mem = ram(data)
        assert mem[0x39a] == 80 - costs[index], (name, "MP cost", mem[0x39a])
        assert mem[0x431] == (47 if index == 2 else 80), (name, "HP", mem[0x431])
        rec = record(data)
        assert rec[17] == index and rec[18] == 0
        if index in (0, 1, 3, 4, 5):
            assert rec[16] == 1 << index, (name, "effect")
        for slot, (_, checkpoint) in enumerate(checkpoints):
            resumed = run(name + f"-resume-{slot}", checkpoint, end, route)
            assert (resumed / "final.cycstate").read_bytes() == data, (name, "continuation", slot)
        rows = list(csv.DictReader((native / "controller.csv").open()))
        assert not any(row["jump_phase"] == "2" and row["buttons"] == "0x80" for row in rows[:20]), "Spell confirmation leaked into jump"
        report.append(dict(spell=name, cost=costs[index], native_interpreter="passed", picker_continuation="passed", active_continuation="passed"))
        print(name, "passed", flush=True)

    # Installed but disabled is identical to a stock launch.
    disabled = out / "disabled"
    shutil.copytree(ROOT / "mods/preloaded/packages", disabled / "packages", dirs_exist_ok=True)
    route = out / "stock.input"
    route.write_text(f"{first} -\n{first + 10} RIGHT\n{first + 40} -\n")
    stock = run("stock", base, first + 80, route, catalog_root=None)
    off = run("disabled", base, first + 80, route, catalog_root=disabled)
    assert (stock / "final.cycstate").read_bytes() == (off / "final.cycstate").read_bytes()
    # Reject an incompatible mod record before applying it.
    corrupt = bytearray((out / "fire-native/final.cycstate").read_bytes())
    pos = next(p + 64 for tag, p, n in chunks(corrupt) if tag == b"MOD " and corrupt[p:p + 64].split(b"\0")[0] == RECORD)
    struct.pack_into("<I", corrupt, pos, 0xdeadbeef)
    bad = out / "invalid.cycstate"
    bad.write_bytes(corrupt)
    run("invalid-state", bad, first + 500, route, expected=1)
    wrong = out / "wrong-owner"
    shutil.copytree(catalog, wrong, dirs_exist_ok=True)
    (wrong / "state.toml").write_text(selection.replace(json.dumps(owner.as_posix()), json.dumps(args.faxanadu_rom.resolve().as_posix())))
    rejected = run("wrong-owner", base, first + 80, route, catalog_root=wrong)
    assert "[Link] Zelda II Link active" not in (rejected / "run.log").read_text()
    assert not record((rejected / "final.cycstate").read_bytes())
    (out / "report.json").write_text(json.dumps(dict(abilities=report, default_disabled="passed", invalid_state="rejected", wrong_owner="activation refused"), indent=2))
    print("PASS integration campaign", flush=True)


if __name__ == "__main__":
    main()
