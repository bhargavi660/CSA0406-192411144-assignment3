from pathlib import Path

try:
    print(Path("/proc/self/maps").read_text())
except (FileNotFoundError, PermissionError) as exc:
    print(f"/proc/self/maps unavailable: {exc}")
