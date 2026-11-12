#!/usr/bin/env python3
"""Count readability debt in the C under ``src/`` and gate it on the files a change touches.

    tools/quality.py                  one row per image directory, then the total
    tools/quality.py --queue [-n 30]  files worst first, with the score and the metrics
    tools/quality.py --diff BASE      compare BASE with ``--to`` (default HEAD); exit 1 when a
                                      touched file got worse in a gated metric
    tools/quality.py --markdown       write docs/subsystems.md with a fresh debt table to build/subsystems.md
    tools/quality.py --markdown --update   rewrite the table of docs/subsystems.md itself (the scheduled action)

Metrics, counted inside ``MATCH`` function bodies unless noted:

- ``addr``    matched functions still named ``func_<ADDR>``
- ``names``   ``D_<ADDR>``, ``unk_<hex>`` and ``FIELD(...)`` tokens: an offset access is an unnamed
              member, so turning one into an ``unk_<OFF>`` member keeps the count; the
              per-function ratchet also counts raw width casts and constant indexes into a
              byte-pointer local (``panel[0x10]``) the same way
- ``casts``   lines with a raw width cast: ``*(u8 *)p``, ``((u8 *)p)[n]``, ``(u8 *)p + 0x10``
- ``harmful`` ``FAKE_REG``, ``FAKE_OPAQUE``, ``FAKE_USE``, ``FAKE_CLOBBER_*``
- ``notes``   ``FAKE:`` notes (whole file)
- ``pasted``  functions with two or more statements whose name and body also stand in a ``.c``
              file of another image: one ``Name.h`` is the rule (docs/conventions.md, Shared bodies)
- ``twins``   the same, under another name; sharing needs one evidence name first (trended)

A body that is only local declarations and one statement-macro call is already the shared form, so
its copies count in neither ``pasted`` nor ``twins``.

The gate sums ``casts``, ``harmful`` and ``pasted`` over the touched files, so a body moved
between them nets to zero. ``addr`` and ``names`` compare functions, not totals, over the touched
files: ``names`` fails when a function present before and after (same name) holds more
placeholder tokens; ``addr`` fails when a body that was named before is now named ``func_<ADDR>``.
A new ``MATCH`` body is exempt from both, since its first name and globals are the lane's start.
``notes`` and ``twins`` are trended, not gated (``--gate`` changes the set). A file the change did
not touch never counts, so old debt never blocks. ``BASE`` is compared at its merge-base with
``--to``, so work that landed on ``BASE`` since the branch point never counts as a regression.

A commit message line ``Quality-Allowed: <path> <metric>`` accepts one metric rise in one file,
for a fake helper that is the best try after the plain forms failed (keep its ``FAKE:`` note).
"""

from __future__ import annotations

import argparse
import collections
import json
import re
import subprocess
from collections.abc import Iterable, Iterator
from pathlib import Path

from bof3.source.ctext import mask

ROOT = Path(__file__).resolve().parent.parent
METRICS = ("addr", "names", "casts", "harmful", "notes", "twins", "pasted")
GATED = ("casts", "harmful", "pasted", "addr", "names")
PER_FUNCTION = ("addr", "names")
TOTALS = ("casts", "harmful", "pasted")
SUBSYSTEMS = (
    ("Executable", "src/engine/slus"),
    ("Game", "src/engine/game"),
    ("Logo", "src/logo"),
    ("Shared bodies", "src/shared"),
    ("Area", "src/overlays/area"),
    ("Battle", "src/overlays/battle"),
    ("Battle magic", "src/overlays/bmagic"),
    ("Boss", "src/overlays/boss"),
    ("Fairy Village", "src/overlays/commu"),
    ("Menu", "src/overlays/menu"),
    ("Player character", "src/overlays/plchar"),
    ("Scenario", "src/overlays/scenario"),
    ("Title", "src/overlays/title"),
)
SUBSYSTEMS_DOC = ROOT / "docs" / "subsystems.md"
TABLE_BEGIN = "<!-- quality:begin (tools/quality.py --markdown) -->"
TABLE_END = "<!-- quality:end -->"
WEIGHT = {
    "addr": 1,
    "names": 1,
    "casts": 2,
    "harmful": 3,
    "notes": 1,
    "twins": 1,
    "pasted": 4,
}

FUNC = re.compile(r"^MATCH\s[^;{}()]*?\b(\w+)\s*\([^;{}]*\)\s*\{", re.M)
ADDR_NAME = re.compile(r"func_[0-9A-Fa-f]{8}")
PLACEHOLDER = re.compile(r"\b(?:D_[0-9A-Fa-f]{8}|unk_[0-9A-Fa-f]+|FIELD(?=\s*\())\b")
WIDTH = r"(?:volatile\s+)?(?:u|s)(?:8|16|32)\s*\*\s*"
RAW_CAST = re.compile(
    rf"\*\s*\(+\s*{WIDTH}\)"  # *(u8 *)p, *((u32 *)((u8 *)p + 4))
    rf"|\(\(\s*{WIDTH}\)[^()]*\)\s*\["  # ((u8 *)p)[n]
    rf"|\(\s*{WIDTH}\)\s*\w+\s*\+\s*(?:0x)?[0-9]"  # (u8 *)p + 0x10
)
# A byte-pointer local (`u8* panel`), whose constant indexes are unnamed members.
# A byte-pointer local, declared plainly or through a register pin (`FAKE_REG(u8*, p, "v0")`).
BYTE_LOCAL = re.compile(r"\b[us]8\s*\*\s*,?\s*(\w+)\s*[;=,)]")
# The pre-rename spellings stay in the pattern so a base revision counts the same helpers.
HARMFUL = re.compile(
    r"\b(?:FAKE_REG|FAKE_OPAQUE|FAKE_USE|FAKE_CLOBBER_\w+"
    r"|MATCH_FAKE_PIN|MATCH_REG|MATCH_FAKE_OPAQUE|MATCH_FAKE_USE|CLOBBER_\w+)\b"
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
    """Return ``text`` with comments and strings blank, keeping the line count."""
    return mask(text)


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


ADDR_TOKEN = re.compile(r"\b(?:D|func|jtbl)_[0-9A-F]{8}\b")


def shape(name: str, body: str) -> str:
    """Return the body with its own name, address names and spacing removed, the key twins share.

    Two copies that differ only in the ``D_<ADDR>`` or ``func_<ADDR>`` they name (each image's own
    table) share a key, the way ripwire's type-2 clones do.
    """
    body = ADDR_TOKEN.sub("$A", body.replace(name, "@"))
    return re.sub(r"\s+", " ", body).strip()


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


def merge_base(base: str, to: str) -> str:
    """Return the commit ``to`` branched from ``base`` at, or ``base`` when there is none."""
    out = subprocess.run(
        ["git", "merge-base", base, "HEAD" if to == "WORK" else to],
        cwd=ROOT, capture_output=True, text=True, check=False,
    )  # fmt: skip
    return out.stdout.strip() if out.returncode == 0 and out.stdout.strip() else base


def touched(base: str, to: str) -> set[str]:
    """Return the paths that differ between ``base`` and ``to``; a renamed file lists both paths,
    so its metrics move with it."""
    cmd = ["git", "diff", "--name-only", "--no-renames", base] + (
        [] if to == "WORK" else [to]
    )
    out = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True, check=True)
    return set(out.stdout.split())


ALLOWED = re.compile(r"^Quality-Allowed:\s*(\S+)\s+(\w+)", re.M)


def allowed(base: str, to: str) -> set[tuple[str, str]]:
    """Return the ``(path, metric)`` pairs that commits between ``base`` and ``to`` accept."""
    out = subprocess.run(
        ["git", "log", "--format=%B", f"{base}..{'HEAD' if to == 'WORK' else to}"],
        cwd=ROOT, capture_output=True, text=True, check=False,
    )  # fmt: skip
    return set(ALLOWED.findall(out.stdout))


def worse(
    old: dict[str, dict[str, int]],
    new: dict[str, dict[str, int]],
    changed: Iterable[str],
    gate: Iterable[str] = TOTALS,
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


def functions(
    files: dict[str, str], paths: Iterable[str]
) -> dict[str, tuple[int, str, bool]]:
    """Return ``name -> (most placeholder tokens in one copy, body shape, is func_<ADDR>)`` for the
    ``MATCH`` functions in ``paths``; copies of one name (a body pasted into images) keep the worst."""
    out: dict[str, tuple[int, str, bool]] = {}
    for path in sorted(set(paths) & files.keys()):
        for name, body in bodies(strip_comments(files[path])):
            tokens = unnamed(body)
            prior = out.get(name, (0, "", False))
            out[name] = (
                max(tokens, prior[0]),
                shape(name, body),
                bool(ADDR_NAME.fullmatch(name)),
            )
    return out


def unnamed(body: str) -> int:
    """Return the unnamed accesses in ``body``: placeholder tokens, raw width casts and constant
    indexes into a byte-pointer local, so a byte view turned into an ``unk_<OFF>`` member keeps
    the count."""
    views = sum(
        len(re.findall(rf"\b{name}\s*\[\s*(?:0x[0-9A-Fa-f]+|[0-9]+)\s*\]", body))
        for name in set(BYTE_LOCAL.findall(body))
    )
    return len(PLACEHOLDER.findall(body)) + len(RAW_CAST.findall(body)) + views


def placeholders(
    files: dict[str, str], paths: Iterable[str]
) -> dict[tuple[str, str], int]:
    """Return ``(path, name) -> most placeholder tokens in one copy`` for the ``MATCH`` functions
    in ``paths``."""
    out: dict[tuple[str, str], int] = {}
    for path in sorted(set(paths) & files.keys()):
        for name, body in bodies(strip_comments(files[path])):
            out[path, name] = max(unnamed(body), out.get((path, name), 0))
    return out


def ratchet(
    old: dict[str, str],
    new: dict[str, str],
    changed: Iterable[str],
    gate: Iterable[str] = PER_FUNCTION,
) -> list[str]:
    """Return one line per function that got worse in the touched files, by name.

    ``names`` compares a function present in both revisions, in the same file, or in its new
    file when the body moved. ``addr`` flags a ``func_<ADDR>``
    function whose body was matched under a real name before. A new ``MATCH`` body is exempt.
    """
    changed = list(changed)
    before, after = functions(old, changed), functions(new, changed)
    named = {sh for _, sh, addr in before.values() if not addr}
    lines = []
    # Overlays reuse addresses, so one func_<ADDR> name can be two functions in two images:
    # compare the copy in the same file, and fall back to the name only for a body that moved.
    was, now = placeholders(old, changed), placeholders(new, changed)
    gone = {name for path, name in was.keys() - now.keys()}
    for path, name in sorted(now):
        tokens = now[path, name]
        prior = was.get((path, name))
        if prior is None and name in gone and name in before:
            prior = before[name][0]
        if "names" in gate and prior is not None and tokens > prior:
            lines.append(f"{name}: names {prior} -> {tokens}")
    for name, (_, sh, addr) in sorted(after.items()):
        if "addr" in gate and addr and name not in before and sh in named:
            lines.append(f"{name}: addr named -> func_<ADDR>")
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


def by_subsystem(rows: dict[str, dict[str, int]]) -> dict[str, dict[str, int]]:
    """Merge the file rows into one row per subsystem of docs/subsystems.md."""
    grouped: dict[str, dict[str, dict[str, int]]] = collections.defaultdict(dict)
    for path, row in rows.items():
        name = next(
            (n for n, prefix in SUBSYSTEMS if path.startswith(prefix + "/")), "Other"
        )
        grouped[name][path] = row
    return {name: totals(members) for name, members in grouped.items()}


def markdown_table(rows: dict[str, dict[str, int]]) -> str:
    """Return the debt table of docs/subsystems.md, one row per subsystem, then the total."""
    cols = ("funcs", "addr", "names", "casts", "harmful", "twins", "pasted")
    heads = (
        "Matched functions",
        "`addr`",
        "`names`",
        "`casts`",
        "`harmful`",
        "`twins`",
        "`pasted`",
    )
    groups = by_subsystem(rows)
    order = [n for n, _ in SUBSYSTEMS if n in groups] + (
        ["Other"] if "Other" in groups else []
    )
    body = [[name, *(str(groups[name][c]) for c in cols)] for name in order]
    total = totals(rows)
    body.append(["Total", *(str(total[c]) for c in cols)])
    table = [["Subsystem", *heads], *body]
    width = [max(len(r[i]) for r in table) for i in range(len(heads) + 1)]
    lines = [
        "| "
        + " | ".join(
            (cell.ljust(width[i]) if i == 0 else cell.rjust(width[i]))
            for i, cell in enumerate(r)
        )
        + " |"
        for r in table
    ]
    rule = ["-" * width[0], *("-" * (w - 1) + ":" for w in width[1:])]
    lines.insert(1, "| " + " | ".join(rule) + " |")
    return "\n".join(lines)


def write_markdown(source: Path, target: Path, rows: dict[str, dict[str, int]]) -> bool:
    """Write ``source`` with a fresh table between its markers to ``target``; return True when it differs."""
    text = source.read_text()
    head, _, rest = text.partition(TABLE_BEGIN)
    _, _, tail = rest.partition(TABLE_END)
    if not rest or not tail:
        raise SystemExit(
            f"quality: {source} lacks the {TABLE_BEGIN} / {TABLE_END} markers"
        )
    new = f"{head}{TABLE_BEGIN}\n\n{markdown_table(rows)}\n\n{TABLE_END}{tail}"
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(new)
    return new != text


def ranked(
    rows: dict[str, dict[str, int]], limit: int
) -> list[tuple[str, dict[str, int]]]:
    """Return the scored rows worst first."""
    ordered = sorted(rows.items(), key=lambda kv: (-score(kv[1]), kv[0]))
    return [(key, row) for key, row in ordered[:limit] if score(row)]


def queue_rows(rows: dict[str, dict[str, int]], limit: int) -> list[dict]:
    """Return the queue rows as objects keyed like the table columns."""
    return [
        {"file": key, "score": score(row), **{c: row[c] for c in ("funcs", *METRICS)}}
        for key, row in ranked(rows, limit)
    ]


def table(rows: dict[str, dict[str, int]], limit: int, label: str) -> str:
    """Return the rows worst first as aligned text."""
    cols = ("funcs", *METRICS)
    out = [f"{'score':>6} " + " ".join(f"{c:>7}" for c in cols) + f"  {label}"]
    for key, row in ranked(rows, limit):
        out.append(
            f"{score(row):>6} " + " ".join(f"{row[c]:>7}" for c in cols) + f"  {key}"
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
    parser.add_argument(
        "--jsonl", action="store_true", help="with --queue: one JSON object per line"
    )
    parser.add_argument(
        "--markdown",
        action="store_true",
        help="write docs/subsystems.md with a fresh table to build/subsystems.md",
    )
    parser.add_argument(
        "--update",
        action="store_true",
        help="with --markdown: rewrite docs/subsystems.md",
    )
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
        base = merge_base(args.diff, args.to)
        old_files, new_files = rev_files(base), rev_files(args.to)
        changed = touched(base, args.to)
        accepted = allowed(base, args.to)
        # The metrics are counted once per revision; the gate reads them per metric.
        old_rows, new_rows = scan(old_files), scan(new_files)
        found = []
        for metric in gate:
            left = {p for p in changed if (p, metric) not in accepted}
            if metric in PER_FUNCTION:
                found += ratchet(old_files, new_files, left, [metric])
            else:
                found += worse(old_rows, new_rows, left, [metric])
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
    if args.markdown:
        target = SUBSYSTEMS_DOC if args.update else ROOT / "build" / "subsystems.md"
        changed = write_markdown(SUBSYSTEMS_DOC, target, rows)
        print(
            f"quality: {target.relative_to(ROOT)} written, "
            f"docs/subsystems.md {'is stale' if changed else 'is current'}"
        )
        return 0
    if args.queue:
        if args.jsonl:
            for row in queue_rows(rows, args.n):
                print(json.dumps(row, ensure_ascii=False))
        else:
            print(table(rows, args.n, "file"))
        return 0
    print(table(by_image(rows), 10**6, "directory"))
    total = totals(rows)
    print("total  " + " ".join(f"{m}={total[m]}" for m in ("funcs", *METRICS)))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
