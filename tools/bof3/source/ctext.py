"""C source text helpers shared by the analysis and rename tools."""

from __future__ import annotations

import subprocess
from pathlib import Path

#: Files the tools read: tracked C and headers under ``src/`` and ``include/``.
SOURCE_DIRS = ("src", "include")


def tracked(root: Path, *paths: str) -> list[str]:
    """Return the tracked files under ``paths`` (default: the C sources), repo-relative."""
    out = subprocess.run(
        ["git", "ls-files", "-z", "--", *(paths or SOURCE_DIRS)],
        cwd=root,
        capture_output=True,
        text=True,
        check=True,
    ).stdout
    return [name for name in out.split("\0") if name]


def tracked_c(root: Path) -> list[str]:
    return [name for name in tracked(root) if name.endswith((".c", ".h"))]


def read(root: Path, name: str) -> str:
    return (root / name).read_text(encoding="utf-8", errors="replace")


def mask(text: str) -> str:
    """Blank comments, strings and character literals; newlines and length stay."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c == "/" and text[i + 1 : i + 2] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
        elif c == "/" and text[i + 1 : i + 2] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
        elif c in "\"'":
            j = i + 1
            while j < n and text[j] != c and text[j] != "\n":
                j += 2 if text[j] == "\\" else 1
            j += 1
        else:
            i += 1
            continue
        for k in range(i, min(j, n)):
            if out[k] != "\n":
                out[k] = " "
        i = j
    return "".join(out)


def split_args(params: str) -> list[str]:
    """Split a parameter list at its top-level commas; ``void`` and empty give ``[]``."""
    params = params.strip()
    if params in ("", "void"):
        return []
    parts, depth, current = [], 0, ""
    for ch in params:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            parts.append(current.strip())
            current = ""
        else:
            current += ch
    parts.append(current.strip())
    return parts
