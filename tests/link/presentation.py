"""Frame-by-frame native HUD, beam alignment and transition visibility checks.

Supply stock USA checkpoints, including an assisted supported right-hand exit
with no invulnerability. Outputs and exact command lines stay under --out.
"""
import argparse
import json
import os
from pathlib import Path
import struct
import subprocess
import zlib
from integration import fixture, ram, record


def png_rows(path):
    data = path.read_bytes()
    assert data[:8] == b'\x89PNG\r\n\x1a\n'
    pos = 8
    compressed = bytearray()
    header = None
    while pos < len(data):
        size, tag = struct.unpack_from('>I4s', data, pos)
        body = data[pos + 8:pos + 8 + size]
        if tag == b'IHDR':
            header = struct.unpack('>IIBBBBB', body)
        if tag == b'IDAT':
            compressed += body
        pos += 12 + size
    width, height, depth, color, _, _, interlace = header
    assert (width, height, depth, interlace) == (256, 240, 8, 0)
    assert color in (2, 6)
    stride = width * (3 if color == 2 else 4) + 1
    rows = zlib.decompress(compressed)
    assert len(rows) == stride * height
    return rows, stride


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    for name in ('exe', 'faxanadu-rom', 'mods-root', 'baseline-state', 'scroll-state', 'out'):
        ap.add_argument('--' + name, required=True, type=Path)
    args = ap.parse_args()
    out = args.out.resolve()
    if os.name == 'nt' and out.drive.lower() == 'c:':
        raise SystemExit('Use F: or G: for test output')
    out.mkdir(parents=True, exist_ok=True)
    env = dict(os.environ, TEMP=str(out), TMP=str(out), SDL_AUDIODRIVER='dummy', LNG_TEST_HIDDEN='1')
    report = []

    def run(tag, state, duration, events, mode='native'):
        folder = out / tag / mode
        folder.mkdir(parents=True, exist_ok=True)
        start = struct.unpack_from('<I', state.read_bytes(), 28)[0]
        route = folder / 'input.txt'
        route.write_text(''.join(f'{start + f} {buttons}\n' for f, buttons in events))
        cmd = [str(args.exe.resolve()), str(args.faxanadu_rom.resolve()), '--no-save',
               '--mods-root', str(args.mods_root.resolve()), '--load-state', str(state),
               '--frames', str(start + duration), '--input', str(route),
               '--present-out', str(folder / 'picture.png'), '--present-every', '1',
               '--screenshot', str(folder / 'native.png'), '--shot-every', '1']
        if mode == 'interp':
            cmd += ['--interp-only']
        for tick in range(duration):
            cmd += ['--save-state', f'{start + tick}:{folder}/{tick}.cycstate']
        (folder / 'command.json').write_text(json.dumps(cmd, indent=2))
        with (folder / 'run.log').open('w') as log:
            p = subprocess.run(cmd, cwd=folder, env=env, stdout=log, stderr=subprocess.STDOUT,
                               timeout=180, creationflags=subprocess.CREATE_NO_WINDOW if os.name == 'nt' else 0)
        assert p.returncode == 0, (folder, p.returncode)
        for tick in range(duration):
            native, stride = png_rows(folder / f'native_{start + tick:05d}.png')
            presented, other_stride = png_rows(folder / f'picture_{start + tick:05d}.png')
            assert stride == other_stride and native[:32 * stride] == presented[:32 * stride], (tag, tick, 'HUD changed')
        return folder

    full = out / 'full.cycstate'
    fixture(args.baseline_state.resolve(), full, {0x431:80, 0x432:0, 0x39a:80, 0xad:0})
    for crouch in (False, True):
        tag = 'crouch-beam' if crouch else 'standing-beam'
        events = [(0, '-'), (10, 'DOWN B' if crouch else 'B'), (11, 'DOWN' if crouch else '-'), (30, '-')]
        a = run(tag, full, 38, events)
        b = run(tag, full, 38, events, 'interp')
        seen = 0
        for tick in range(38):
            data = (a / f'{tick}.cycstate').read_bytes()
            assert data == (b / f'{tick}.cycstate').read_bytes(), (tag, tick, 'backend state mismatch')
            state = record(data)
            for slot in range(4):
                pos = 48 + slot * 16
                life, kind = struct.unpack_from('<HB', state, pos + 12)
                if not life or kind != 1:
                    continue
                py = struct.unpack_from('<i', state, pos + 4)[0] / 256
                world_y = ram(data)[0xa1]
                assert py - world_y == (10 if crouch else 0), (tag, tick, py, world_y)
                if state[29] == (7 if crouch else 5):
                    seen += 1
                    draw_y = struct.unpack_from('<h', state, 44)[0]
                    assert py + 32 == draw_y + (10 if crouch else 0), (tag, 'sprite origin mismatch')
        assert seen, (tag, 'No visible sword/beam overlap sampled')
        report.append(dict(case=tag,overlap_frames=seen,hud='native pixels unchanged',parity=True))

    a = run('right-transition', args.scroll_state.resolve(), 110, [(0, 'RIGHT'), (35, '-')])
    b = run('right-transition', args.scroll_state.resolve(), 110, [(0, 'RIGHT'), (35, '-')], 'interp')
    scroll_frames = 0
    for tick in range(110):
        data = (a / f'{tick}.cycstate').read_bytes()
        assert data == (b / f'{tick}.cycstate').read_bytes(), ('scroll', tick, 'backend state mismatch')
        memory, state = ram(data), record(data)
        if memory[0x54] < 4 and memory[0xad] == 0:
            scroll_frames += 1
            assert state[28], ('scroll', tick, 'Player sprite disappeared during native wait')
    assert scroll_frames > 20
    report.append(dict(case='right-transition',scroll_frames=scroll_frames,missing_draw_frames=0,parity=True))
    (out / 'report.json').write_text(json.dumps(report, indent=2))
    print('PASS native HUD pixels, standing/crouching source beam heights, continuous transition sprite and per-frame backend parity')


if __name__ == '__main__':
    main()
