#!/usr/bin/env python3
"""Query the FaxanaduRecomp TCP debug server."""
import socket, json, sys, time

HOST, PORT = "127.0.0.1", 4370

def query(cmd, extra=None):
    s = socket.socket()
    s.settimeout(5)
    try:
        s.connect((HOST, PORT))
        payload = {"cmd": cmd, "id": 1}
        if extra:
            payload.update(extra)
        s.sendall((json.dumps(payload) + "\n").encode())
        data = b""
        while True:
            chunk = s.recv(4096)
            if not chunk:
                break
            data += chunk
            if b"\n" in chunk:
                break
        return json.loads(data.decode().strip())
    except Exception as e:
        return {"error": str(e)}
    finally:
        s.close()

if __name__ == "__main__":
    cmd = sys.argv[1] if len(sys.argv) > 1 else "faxanadu_state"
    result = query(cmd)
    print(json.dumps(result, indent=2))
