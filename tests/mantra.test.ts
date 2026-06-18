/**
 * Mantra (synthetic-SRAM) capture regression tests for Faxanadu.
 *
 * Same type of test as MetroidNESRecomp/tests/password.test.ts: the save-anywhere
 * capture runs the game's own encoder (func_96FE_b12) OUT-OF-BAND every few
 * seconds. That must NEVER perturb live game state — otherwise it leaks
 * corruption that accumulates into a lockup (this is exactly what happened in
 * Metroid: the out-of-band encoder left g_cpu.S drifted and dirtied the 6502
 * stack page). Faxanadu's encoder is currently stack-balanced and its scratch
 * snapshot is sufficient; this test pins that so a future change to the capture
 * path (or a missed per-game discriminator) can't silently reintroduce drift.
 *
 *   1. CAPTURE IS SIDE-EFFECT-FREE — pause (no natural drift), snapshot CPU regs
 *      + all work RAM, trigger one capture (mantra_now), snapshot again, assert
 *      byte-for-byte identical and S unchanged.
 *   2. CAPTURE IS DETERMINISTIC — the same progress yields the same mantra.
 *
 * Drives the native build over the TCP debug server (Faxanadu default port 4370;
 * it only checks that debug.ini exists, it doesn't parse a port). Skipped (not
 * failed) when no built exe is present.
 *
 *   npx vitest run mantra
 */
import { describe, it, expect, beforeAll, afterAll } from "vitest";
import { spawn, execFileSync, type ChildProcess } from "child_process";
import { existsSync, readFileSync, writeFileSync, readdirSync } from "fs";
import { join, resolve, dirname } from "path";
import { createHash } from "crypto";
import net from "net";

const TESTS_DIR = import.meta.dirname;
const GAME_ROOT = resolve(TESTS_DIR, "..");
const PORT = 4370; // Faxanadu's default debug port (debug.ini presence enables it)

function findExe(): string | null {
  for (const rel of ["build_release", "build/Release"]) {
    const dir = join(GAME_ROOT, rel);
    if (!existsSync(dir)) continue;
    const exe = readdirSync(dir).find(
      (f) => f.endsWith("Recomp.exe") && !f.toLowerCase().startsWith("sdl")
    );
    if (exe) return join(dir, exe);
  }
  return null;
}

function findRom(): string | null {
  const cfgPath = join(TESTS_DIR, "test.config.json");
  const sha: string | undefined = existsSync(cfgPath)
    ? JSON.parse(readFileSync(cfgPath, "utf-8")).romSha256
    : undefined;
  const candidates = readdirSync(GAME_ROOT).filter((f) => f.toLowerCase().endsWith(".nes"));
  for (const f of candidates) {
    const data = readFileSync(join(GAME_ROOT, f));
    if (data.length < 17) continue;
    if (!sha) return join(GAME_ROOT, f);
    if (createHash("sha256").update(data.subarray(16)).digest("hex") === sha)
      return join(GAME_ROOT, f);
  }
  return candidates.length ? join(GAME_ROOT, candidates[0]) : null;
}

class Dbg {
  private buf = "";
  private waiters: ((line: string) => void)[] = [];
  constructor(private sock: net.Socket) {
    sock.setEncoding("utf-8");
    sock.on("data", (d: string) => {
      this.buf += d;
      let nl: number;
      while ((nl = this.buf.indexOf("\n")) >= 0) {
        const line = this.buf.slice(0, nl).trim();
        this.buf = this.buf.slice(nl + 1);
        const w = this.waiters.shift();
        if (w && line) w(line);
      }
    });
  }
  static connect(port: number, timeoutMs = 15000): Promise<Dbg> {
    return new Promise((res, rej) => {
      const deadline = Date.now() + timeoutMs;
      const tryConnect = () => {
        const s = net.connect(port, "127.0.0.1");
        s.once("connect", () => res(new Dbg(s)));
        s.once("error", () => {
          s.destroy();
          if (Date.now() > deadline) rej(new Error("debug server never came up"));
          else setTimeout(tryConnect, 300);
        });
      };
      tryConnect();
    });
  }
  cmd(obj: Record<string, unknown>): Promise<any> {
    return new Promise((res, rej) => {
      const t = setTimeout(() => rej(new Error("cmd timeout: " + JSON.stringify(obj))), 6000);
      this.waiters.push((line) => {
        clearTimeout(t);
        try { res(JSON.parse(line)); } catch { res({ raw: line }); }
      });
      (this as any).sock.write(JSON.stringify(obj) + "\n");
    });
  }
  close() { (this as any).sock.destroy(); }
}

const sleep = (ms: number) => new Promise((r) => setTimeout(r, ms));

async function readRamFull(d: Dbg): Promise<Buffer> {
  const out = Buffer.alloc(0x800);
  for (let base = 0; base < 0x800; base += 256) {
    const r = await d.cmd({ cmd: "read_ram", addr: base.toString(16), len: 256 });
    Buffer.from(r.hex, "hex").copy(out, base);
  }
  return out;
}

const exe = findExe();
const rom = findRom();
const ready = !!exe && !!rom;
let proc: ChildProcess | undefined;
let dbg: Dbg | undefined;

describe("Faxanadu mantra capture", () => {
  beforeAll(async () => {
    if (!ready) return;
    try { execFileSync("taskkill", ["/F", "/IM", "FaxanaduRecomp.exe"], { stdio: "ignore" }); } catch {}
    writeFileSync(join(dirname(exe!), "debug.ini"), "port=4370\n"); // presence enables the TCP server
    proc = spawn(exe!, [rom!], { cwd: dirname(exe!), stdio: "ignore", detached: false });
    dbg = await Dbg.connect(PORT);
    await sleep(2000); // let it boot past init
  }, 60000);

  afterAll(async () => {
    try { dbg?.cmd({ cmd: "quit" }); } catch {}
    dbg?.close();
    try { execFileSync("taskkill", ["/F", "/IM", "FaxanaduRecomp.exe"], { stdio: "ignore" }); } catch {}
    proc?.kill();
  });

  it.skipIf(!ready)("capture is side-effect-free (no stack/state corruption)", async () => {
    await dbg!.cmd({ cmd: "pause" });
    const r1 = await dbg!.cmd({ cmd: "get_registers" });
    const before = await readRamFull(dbg!);

    const m = await dbg!.cmd({ cmd: "mantra_now" }); // out-of-band encoder
    expect(m.ok, "mantra_now failed — is this a mantra-save build?").toBe(true);

    const r2 = await dbg!.cmd({ cmd: "get_registers" });
    const after = await readRamFull(dbg!);
    await dbg!.cmd({ cmd: "continue" });

    expect(r2.S, `S drifted ${r1.S} -> ${r2.S} — capture not stack-balanced`).toBe(r1.S);
    // The 6502 stack ($0100-$01FF) grows down from S. Bytes at/below the entry
    // pointer ($0100..$0100+S) are FREE space the encoder may use as scratch
    // during its call (harmless — never read as live data). Exclude that region;
    // everything else (zero page, the LIVE stack above S, $0200-$07FF) plus S
    // itself must be untouched.
    const freeStackEnd = 0x100 + parseInt(r1.S, 16);
    const changed: string[] = [];
    for (let i = 0; i < 0x800; i++) {
      if (i >= 0x100 && i <= freeStackEnd) continue; // free stack scratch — harmless
      if (before[i] !== after[i]) changed.push(`$${i.toString(16).padStart(3, "0")}`);
    }
    expect(changed, `capture mutated live RAM at: ${changed.slice(0, 16).join(",")}`).toEqual([]);
  });

  it.skipIf(!ready)("capture is deterministic", async () => {
    const m1 = (await dbg!.cmd({ cmd: "mantra_now" })).mantra as string;
    const m2 = (await dbg!.cmd({ cmd: "mantra_now" })).mantra as string;
    expect(typeof m1).toBe("string");
    expect(m2, "same progress must yield the same mantra").toBe(m1);
  });
});
