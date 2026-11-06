#!/usr/bin/env python3
"""Fail when an enum or a run of `#define` constants is not sorted by value, ascending.

    tools/check_sorted.py [PATH ...]      default: include and src

An enum member without `=` takes the previous value plus one. An enum or run whose values cannot be
evaluated here (a sizeof, a cast, a name from another header) is skipped. A run is consecutive
`#define NAME value` lines.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

ENUM = re.compile(r"\benum\b\s*\w*\s*\{(.*?)\}", re.S)
MEMBER = re.compile(r"([A-Za-z_]\w*)\s*(?:=\s*([^,]+))?(?:,|$)")
DEFINE = re.compile(r"^#define\s+([A-Za-z_]\w*)\s+(.+?)\s*$")
SAFE = re.compile(r"^[\w\s()+\-*|&<>~^]*$")
Item = tuple[str, int, int]


def strip_comments(text: str) -> str:
    text = re.sub(
        r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), text, flags=re.S
    )
    return re.sub(r"//[^\n]*", "", text)


def value(expr: str, names: dict[str, int]) -> int | None:
    expr = re.sub(r"\b(0[xX][0-9A-Fa-f]+|\d+)[uUlL]+\b", r"\1", expr.strip())
    if not SAFE.match(expr):
        return None
    expr = re.sub(
        r"\b[A-Za-z_]\w*\b", lambda m: str(names.get(m.group(0), m.group(0))), expr
    )
    if re.search(r"[A-Za-z_]", re.sub(r"\b0[xX][0-9A-Fa-f]+\b", "", expr)):
        return None
    try:
        return int(
            eval(expr, {"__builtins__": {}}, {})
        )  # arithmetic only, filtered by SAFE
    except Exception:
        return None


def first_unsorted(items: list[Item]) -> tuple[int, str, str] | None:
    """Return the line and both names of the first descent in (name, line, value) items."""
    for (an, _, av), (bn, bl, bv) in zip(items, items[1:], strict=False):
        if bv < av:
            return bl, an, bn
    return None


def check_text(text: str, path: str = "") -> list[str]:
    clean = strip_comments(text)
    found: list[str] = []
    for m in ENUM.finditer(clean):
        names: dict[str, int] = {}
        items: list[Item] = []
        current: int | None = -1
        for member in MEMBER.finditer(m.group(1)):
            name, expr = member.group(1), member.group(2)
            current = value(expr, names) if expr else current + 1
            if current is None:
                items = []
                break
            names[name] = current
            line = clean.count("\n", 0, m.start(1) + member.start(1)) + 1
            items.append((name, line, current))
        bad = first_unsorted(items)
        if bad:
            found.append(f"{path}:{bad[0]}: enum member {bad[2]} sorts before {bad[1]}")

    run: list[Item] = []
    defined: dict[str, int] = {}

    def flush() -> None:
        bad = first_unsorted(run)
        if bad:
            found.append(f"{path}:{bad[0]}: #define {bad[2]} sorts before {bad[1]}")
        run.clear()

    for number, line_text in enumerate(clean.split("\n"), 1):
        m = DEFINE.match(line_text)
        v = value(m.group(2), defined) if m else None
        if m and v is not None:
            defined[m.group(1)] = v
            run.append((m.group(1), number, v))
        else:
            flush()
    flush()
    return found


def main(argv: list[str]) -> int:
    roots = [Path(a) for a in argv] or [Path("include"), Path("src")]
    found: list[str] = []
    for root in roots:
        files = (
            [root]
            if root.is_file()
            else sorted(p for p in root.rglob("*") if p.suffix in {".h", ".c"})
        )
        for path in files:
            found += check_text(path.read_text(errors="replace"), str(path))
    if found:
        print("\n".join(found))
    print(f"check_sorted: {len(found)} unsorted")
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
