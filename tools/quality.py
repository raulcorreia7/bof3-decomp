#!/usr/bin/env python3
"""Count readability debt in the C under ``src/`` and gate it on the files a change touches.

    tools/quality.py                  one row per image directory, then the total
    tools/quality.py --queue [-n 30]  files worst first, with the score and the metrics
    tools/quality.py --diff BASE      compare BASE with ``--to`` (default HEAD); exit 1 when a
                                      touched file got worse in a gated metric

Metrics, counted inside ``MATCH`` function bodies unless noted:

- ``addr``    matched functions still named ``func_<ADDR>``
- ``names``   ``D_<ADDR>`` and ``unk_<hex>`` tokens
- ``casts``   lines with a raw width cast: ``*(u8 *)p``, ``((u8 *)p)[n]``, ``(u8 *)p + 0x10``
- ``harmful`` ``MATCH_FAKE_PIN``, ``MATCH_REG``, ``MATCH_FAKE_OPAQUE``, ``MATCH_FAKE_USE``, ``CLOBBER_*``
- ``notes``   ``FAKE:`` notes (whole file)
- ``pasted``  functions with two or more statements whose name and body also stand in a ``.c``
              file of another image: one ``Name.h`` is the rule (docs/conventions.md, Shared bodies)
- ``twins``   the same, under another name; sharing needs one evidence name first (trended)

A body that is only local declarations and one statement-macro call is already the shared form, so
its copies count in neither ``pasted`` nor ``twins``.

The gate sums each metric over the touched files, so a body moved between them nets to zero.
It covers ``casts``, ``harmful`` and ``pasted``. A new match may add a ``func_`` name or a ``D_``
reference, so ``addr``, ``names``, ``notes`` and ``twins`` are trended, not gated (``--gate``
changes the set). A file the change did not touch never counts, so old debt never blocks.
"""

from __future__ import annotations

import argparse
import collections
import re
import subprocess
from collections.abc import Iterable, Iterator
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
METRICS = ("addr", "names", "casts", "harmful", "notes", "twins", "pasted")
GATED = ("casts", "harmful", "pasted")
WEIGHT = {
    "addr": 1,
    "names": 1,
    "casts": 2,
    "harmful": 3,
    "notes": 1,
    "twins": 1,
    "pasted": 4,
}

COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
FUNC = re.compile(r"^MATCH\s[^;{}()]*?\b(\w+)\s*\([^;{}]*\)\s*\{", re.M)
ADDR_NAME = re.compile(r"func_[0-9A-Fa-f]{8}")
PLACEHOLDER = re.compile(r"\b(?:D_[0-9A-Fa-f]{8}|unk_[0-9A-Fa-f]+)\b")
WIDTH = r"(?:volatile\s+)?(?:u|s)(?:8|16|32)\s*\*\s*"
RAW_CAST = re.compile(
    rf"\*\s*\(\s*{WIDTH}\)"  # *(u8 *)p
    rf"|\(\(\s*{WIDTH}\)[^()]*\)\s*\["  # ((u8 *)p)[n]
    rf"|\(\s*{WIDTH}\)\s*\w+\s*\+\s*(?:0x)?[0-9]"  # (u8 *)p + 0x10
)
HARMFUL = re.compile(
    r"\b(?:MATCH_FAKE_PIN|MATCH_REG|MATCH_FAKE_OPAQUE|MATCH_FAKE_USE|CLOBBER_\w+)\b"
)
NOTE = re.compile(r"FAKE:")
# A local declaration (`u8 i`, `Actor* actor = g_CurrentActor`) and a statement-macro call.
DECL = re.compile(
    r"(?!return\b|goto\b|case\b)(?:(?:const|volatile|static|register)\s+)*"
    r"[A-Za-z_]\w*[\s*]+\w+(?:\[[^\]]*\])?(?:\s*=.*)?",
    re.S,
)
MACRO_CALL = re.compile(r"[A-Z][A-Z0-9_]*\s*\(.*\)", re.S)


def strip_comments(text: str) -> str:
    """Return ``text`` without comments, keeping the line count."""
    return COMMENT.sub(lambda m: "\n" * m.group().count("\n"), text)


def bodies(text: str) -> Iterator[tuple[str, str]]:
    """Yield ``(name, body)`` for each ``MATCH`` definition in comment-free ``text``."""
    for found in FUNC.finditer(text):
        depth, end = 1, found.end()
        while depth and end < len(text):
            depth += (text[end] == "{") - (text[end] == "}")
            end += 1
        yield found.group(1), text[found.end() : end - 1]


def macro_body(body: str) -> bool:
    """Return whether ``body`` is local declarations and one statement-macro call.

    That is the shared form docs/conventions.md prescribes, so its copies are neither pasted nor
    twins.
    """
    steps = [s.strip() for s in body.split(";") if s.strip()]
    rest = [s for s in steps if not DECL.fullmatch(s)]
    return len(rest) == 1 and bool(MACRO_CALL.fullmatch(rest[0]))


def shape(name: str, body: str) -> str:
    """Return the body with its own name and spacing removed, the key twins share."""
    return re.sub(r"\s+", " ", body.replace(name, "@")).strip()


def image_of(path: str) -> str:
    """Return the directory that holds ``path``, the image a row reports."""
    return path.rsplit("/", 1)[0] if "/" in path else "."


def scan(files: dict[str, str]) -> dict[str, dict[str, int]]:
    """Return the metrics of each file in ``files`` (path to text)."""
    rows: dict[str, dict[str, int]] = {}
    seen: dict[str, list[tuple[str, str]]] = collections.defaultdict(list)
    for path, text in files.items():
        clean = strip_comments(text)
        row = dict.fromkeys(METRICS, 0)
        row["funcs"] = 0
        row["lines"] = 0
        row["notes"] = len(NOTE.findall(text))
        for name, body in bodies(clean):
            row["funcs"] += 1
            row["lines"] += body.count("\n")
            row["addr"] += bool(ADDR_NAME.fullmatch(name))
            row["names"] += len(PLACEHOLDER.findall(body))
            row["casts"] += sum(
                bool(RAW_CAST.search(line)) for line in body.split("\n")
            )
            row["harmful"] += len(HARMFUL.findall(body))
            if path.endswith(".c") and body.count(";") >= 2 and not macro_body(body):
                seen[shape(name, body)].append((path, name))
        rows[path] = row
    for members in seen.values():
        if len({image_of(p) for p, _ in members}) < 2:
            continue
        for path, name in members:
            peers = {image_of(p) for p, n in members if n == name}
            rows[path]["pasted" if len(peers) > 1 else "twins"] += 1
    return rows


def work_files(root: Path = ROOT) -> dict[str, str]:
    """Return every C file under ``src/`` in the working tree of ``root``."""
    return {
        str(p.relative_to(root)): p.read_text(encoding="utf-8", errors="ignore")
        for p in sorted((root / "src").rglob("*"))
        if p.suffix in (".c", ".h")
    }


def rev_files(rev: str) -> dict[str, str]:
    """Return every C file under ``src/`` at Git revision ``rev`` (``WORK`` is the tree)."""
    if rev == "WORK":
        return work_files()
    names = subprocess.run(
        ["git", "ls-tree", "-r", "--name-only", rev, "src"],
        cwd=ROOT, capture_output=True, text=True, check=True,
    ).stdout.split()  # fmt: skip
    names = [n for n in names if n.endswith((".c", ".h"))]
    blobs = subprocess.run(
        ["git", "cat-file", "--batch"],
        cwd=ROOT, input="".join(f"{rev}:{n}\n" for n in names).encode(),
        capture_output=True, check=True,
    ).stdout  # fmt: skip
    files, pos = {}, 0
    for name in names:
        eol = blobs.index(b"\n", pos)
        size = int(blobs[pos:eol].split()[-1])
        files[name] = blobs[eol + 1 : eol + 1 + size].decode(errors="ignore")
        pos = eol + 1 + size + 1
    return files


def touched(base: str, to: str) -> set[str]:
    """Return the paths that differ between ``base`` and ``to``."""
    cmd = ["git", "diff", "--name-only", base] + ([] if to == "WORK" else [to])
    out = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, check=True)
    return set(out.stdout.split())


def worse(
    old: dict[str, dict[str, int]],
    new: dict[str, dict[str, int]],
    changed: Iterable[str],
    gate: Iterable[str] = GATED,
) -> list[str]:
    """Return one line per touched file whose gated metric rose, for each metric whose total
    over the touched files rose; a body moved between touched files nets to zero."""
    paths = sorted(set(changed) & (old.keys() | new.keys()))
    lines = []
    for metric in gate:
        before = {p: old.get(p, {}).get(metric, 0) for p in paths}
        after = {p: new.get(p, {}).get(metric, 0) for p in paths}
        if sum(after.values()) > sum(before.values()):
            lines += [
                f"{p}: {metric} {before[p]} -> {after[p]}"
                for p in paths
                if after[p] > before[p]
            ]
    return lines


def score(row: dict[str, int]) -> int:
    """Return the weighted debt of one row."""
    return sum(WEIGHT[m] * row[m] for m in METRICS)


def totals(rows: dict[str, dict[str, int]]) -> dict[str, int]:
    """Return the sum of every column over ``rows``."""
    out = collections.Counter()
    for row in rows.values():
        out.update(row)
    return {k: out[k] for k in (*METRICS, "funcs", "lines")}


def by_image(rows: dict[str, dict[str, int]]) -> dict[str, dict[str, int]]:
    """Merge the file rows into one row per directory."""
    grouped: dict[str, dict[str, dict[str, int]]] = collections.defaultdict(dict)
    for path, row in rows.items():
        grouped[image_of(path)][path] = row
    return {image: totals(members) for image, members in grouped.items()}


def table(rows: dict[str, dict[str, int]], limit: int, label: str) -> str:
    """Return the rows worst first as aligned text."""
    cols = ("funcs", *METRICS)
    out = [f"{'score':>6} " + " ".join(f"{c:>7}" for c in cols) + f"  {label}"]
    ranked = sorted(rows.items(), key=lambda kv: (-score(kv[1]), kv[0]))
    for key, row in ranked[:limit]:
        if score(row):
            out.append(
                f"{score(row):>6} "
                + " ".join(f"{row[c]:>7}" for c in cols)
                + f"  {key}"
            )
    return "\n".join(out)


def main(argv: list[str] | None = None) -> int:
    """Run one report, queue or gate."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--diff", metavar="BASE", help="gate touched files against BASE"
    )
    parser.add_argument("--to", default="HEAD", help="revision to gate, or WORK (HEAD)")
    parser.add_argument("--queue", action="store_true", help="list files worst first")
    parser.add_argument("-n", type=int, default=30, help="rows to show (30)")
    parser.add_argument(
        "--gate", default=",".join(GATED), help="metrics the gate checks"
    )
    args = parser.parse_args(argv)
    if args.diff:
        gate = [m for m in args.gate.split(",") if m]
        bad = [m for m in gate if m not in METRICS]
        if bad:
            parser.error(f"unknown metric: {', '.join(bad)}")
        old, new = scan(rev_files(args.diff)), scan(rev_files(args.to))
        found = worse(old, new, touched(args.diff, args.to), gate)
        for line in found:
            print(line)
        if found:
            print(
                f"quality: {len(found)} touched-file metrics rose against {args.diff}"
            )
            return 1
        print(f"quality: no touched file got worse against {args.diff}")
        return 0
    rows = scan(rev_files("WORK"))
    if args.queue:
        print(table(rows, args.n, "file"))
        return 0
    print(table(by_image(rows), 10**6, "directory"))
    total = totals(rows)
    print("total  " + " ".join(f"{m}={total[m]}" for m in ("funcs", *METRICS)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
