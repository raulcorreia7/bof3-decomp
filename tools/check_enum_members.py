#!/usr/bin/env python3
"""Fail when a struct or union member in include/ or src/ has an enum type.

The retail compiler gives an enum the width of an int, so an enum member moves the layout. A member
keeps a fixed-width integer, and an anonymous enum names its values.
"""

import re
import subprocess
import sys
from pathlib import Path

COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
ENUM_DEF = re.compile(
    r"typedef\s+enum\s*(?:\w+\s*)?\{[^{}]*\}\s*(\w+)\s*;|\benum\s+(\w+)\s*\{"
)
AGGREGATE = re.compile(r"\b(?:struct|union)\s*\w*\s*\{")


def tracked():
    out = subprocess.check_output(["git", "ls-files", "include", "src"], text=True)
    return [
        f
        for f in out.split("\n")
        if f.endswith((".c", ".h")) and not f.startswith("include/psyq/")
    ]


def strip(text):
    return COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group()), text)


def bodies(text):
    """Yield (offset, body) of every struct or union body, nested ones included in their parent."""
    for m in AGGREGATE.finditer(text):
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += {"{": 1, "}": -1}.get(text[i], 0)
            i += 1
        yield m.end(), text[m.end() : i - 1]


def find_members(files):
    """Return (file, line) for each struct or union member with an enum type; files maps path to text."""
    files = {f: strip(t) for f, t in files.items()}
    names = {
        m.group(1) or m.group(2) for t in files.values() for m in ENUM_DEF.finditer(t)
    }
    alternatives = "|".join(sorted(names)) or "(?!)"
    typed = re.compile(
        r"^\s*(?:const\s+|volatile\s+)*(?:enum\s+\w+|("
        + alternatives
        + r"))\s*\**\s*\w+\s*(?:\[[^\]]*\])?\s*(?::\s*\d+\s*)?;",
        re.M,
    )
    found = set()
    for f, text in files.items():
        for start, body in bodies(text):
            for m in typed.finditer(body):
                skipped = len(m.group()) - len(m.group().lstrip())
                found.add((f, text.count("\n", 0, start + m.start() + skipped) + 1))
    return sorted(found)


def main():
    if len(sys.argv) > 1 and sys.argv[1] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    files = {f: Path(f).read_text(errors="replace") for f in tracked()}
    bad = find_members(files)
    for f, line in bad:
        print(f"{f}:{line}: struct member has an enum type")
    if bad:
        print(
            "check-enum-members: use a fixed-width integer and an anonymous enum for the values",
            file=sys.stderr,
        )
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
