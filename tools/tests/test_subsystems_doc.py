"""docs/subsystems.md names only directories, headers and records that exist."""

from __future__ import annotations

import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
MAP = (ROOT / "docs/subsystems.md").read_text().split("## Map")[1].split("## Debt")[0]
ROWS = [
    ln
    for ln in MAP.splitlines()
    if ln.startswith("| ") and not ln.startswith(("| Subsystem", "| -"))
]
CELLS = [[c.strip() for c in ln.strip("|").split("|")] for ln in ROWS]
TRACKED = subprocess.run(
    ["git", "ls-files"], cwd=ROOT, capture_output=True, text=True, check=True
).stdout.splitlines()


def spans(cell: str) -> list[str]:
    return re.findall(r"`([^`]+)`", cell)


def has_path(name: str) -> bool:
    if "<" in name or "*" in name:
        return True  # a pattern, not a file
    return any(f == name or f.endswith("/" + name) for f in TRACKED)


def test_src_directories_exist() -> None:
    for row in CELLS:
        name = spans(row[1])[0]
        assert (ROOT / "src" / name).is_dir(), name


def test_headers_exist() -> None:
    for row in CELLS:
        for name in spans(row[3]):
            if name.endswith(".h") and name != "Name.h":
                assert has_path(name), name


def test_records_are_defined() -> None:
    for row in CELLS:
        for name in spans(row[2]):
            if re.fullmatch(r"[A-Z][A-Za-z0-9]+", name):
                found = subprocess.run(
                    ["git", "grep", "-qw", name, "--", "include", "src"],
                    cwd=ROOT,
                    check=False,
                )
                assert found.returncode == 0, name
