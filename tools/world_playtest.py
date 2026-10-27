"""Launch a prepared local world-preview checklist. No native saves are written."""
import argparse
from datetime import datetime, timezone
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
import os
from pathlib import Path
import socket
import subprocess
import threading
import time
import webbrowser


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--setup", type=Path, required=True, help="Prepared setup.json")
    ap.add_argument("--hidden", action="store_true", help="Muted automated helper verification")
    args = ap.parse_args()
    setup = args.setup.resolve()
    root = setup.parent
    config = json.loads(setup.read_text())
    notes = root / "observations.json"
    checks = config["checks"]

    def tcp(cmd, **kw):
        with socket.create_connection(("127.0.0.1", config["tcp_port"]), 5) as s:
            s.settimeout(10)
            with s.makefile("rwb", buffering=0) as f:
                f.write((json.dumps(dict(cmd=cmd, **kw)) + "\n").encode())
                response = json.loads(f.readline())
            if not response.get("ok"):
                raise RuntimeError(response)
            return response

    class Handler(BaseHTTPRequestHandler):
        def log_message(self, *_):
            pass

        def do_GET(self):
            body = (root / "checklist.html").read_bytes()
            self.send_response(200)
            self.send_header("Content-Type", "text/html; charset=utf-8")
            self.end_headers()
            self.wfile.write(body)

        def do_POST(self):
            try:
                length = int(self.headers.get("Content-Length", 0))
                if not 0 < length <= 8192:
                    raise ValueError("Invalid request size")
                data = json.loads(self.rfile.read(length))
                kind = data["action"]
                if kind == "load":
                    check = next(c for c in checks if c["id"] == data["check"])
                    tcp("menu", open=True)
                    tcp("load_state", path=str(root / check["state"]))
                    tcp("menu", open=True)
                elif kind == "resume":
                    tcp("menu", open=False)
                elif kind == "note":
                    check = next(c for c in checks if c["id"] == data["check"])
                    if data["result"] not in ("Pass", "Fail", "Deferred"):
                        raise ValueError("Invalid result")
                    observations = json.loads(notes.read_text()) if notes.exists() else {}
                    observations[check["id"]] = dict(result=data["result"], note=data.get("note", ""),
                                                   at=datetime.now(timezone.utc).isoformat())
                    notes.write_text(json.dumps(observations, indent=2))
                else:
                    raise ValueError("Unknown action")
                response = dict(ok=True)
            except Exception as error:
                response = dict(ok=False, error=str(error))
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.end_headers()
            self.wfile.write(json.dumps(response).encode())

    # Isolated display/audio preferences, never inherited from an owner profile.
    profile = root / "profile.ini"
    profile.write_text("[Display]\nWindowScale=3\nFullscreen=0\nIntegerScale=0\n"
                       "[Audio]\nEnabled=1\nVolume=" + ("0" if args.hidden else "100") + "\n")
    cmd = [config["exe"], config["rom"], "--no-save", "--world-view", "seamless",
           "--tcp", str(config["tcp_port"]), "--config", str(profile)]
    if args.hidden:
        cmd.append("--hidden")
    env = dict(os.environ, NESRECOMP_NO_LAUNCHER="1")
    if args.hidden:
        env.update(SDL_AUDIODRIVER="dummy", LNG_TEST_HIDDEN="1")
    else:
        env.pop("SDL_AUDIODRIVER", None)
        env.pop("LNG_TEST_HIDDEN", None)
    with (root / "playtest.log").open("w") as log:
        game = subprocess.Popen(cmd, cwd=root, env=env, stdout=log, stderr=subprocess.STDOUT,
                                creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0)
        for _ in range(100):
            try:
                tcp("ping")
                break
            except OSError:
                if game.poll() is not None:
                    raise RuntimeError("Game exited; see playtest.log")
                time.sleep(.1)
        else:
            game.terminate()
            raise RuntimeError("Game did not start its local debug interface")
        tcp("menu", open=True)
        tcp("window_size", w=1280, h=720)
        tcp("load_state", path=str(root / checks[0]["state"]))
        tcp("menu", open=True)
        server = ThreadingHTTPServer(("127.0.0.1", config["http_port"]), Handler)
        thread = threading.Thread(target=server.serve_forever, daemon=True)
        thread.start()
        url = f"http://127.0.0.1:{config['http_port']}"
        print(url, flush=True)
        if not args.hidden:
            webbrowser.open(url)
        try:
            game.wait()
        finally:
            server.shutdown()
            server.server_close()


if __name__ == "__main__":
    main()
