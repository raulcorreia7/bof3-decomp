#!/usr/bin/env python3
"""Check declaration and symbol ordering.

Headers follow docs/layout.md#header-layout: constants and enums first, one block per record in
table order, an ID enum in value order, ASSERT_OFFSETs in offset order then ASSERT_SIZE, and
prototypes in address order. config/symbols/<image>.toml rows are in address order. A file lists data and
functions in address order. docs/conventions.md#values adds #define runs by topic, ids and flags by
value, offsets in layout order and arguments in natural order.

A finding marked fixable is a move of prototypes, asserts, symbols.toml rows, enum values or extern
blocks, which changes no value or definition. The other rules are reported as `[manual]`: a move
would change an implicit value, depends on table order only the owner knows, or crosses source files.

Usage:
    python3 tools/order_check.py [PATH ...]
    python3 tools/order_check.py --diff REF
"""

from __future__ import annotations

import argparse
import re
import sys
from dataclasses import dataclass, field

from bof3.adapters.git import changed_files, ls_files, merge_base
from bof3.core.paths import ROOT
from bof3.symbols import SPLIT

ADDR_NAME = re.compile(r"\b(?:func|D|jtbl|jpt|L|s_gap)_([0-9A-Fa-f]{6,8})\b")
ADDR_COMMENT = re.compile(
    r"/\*\s*(?:(?:func|D|jtbl|jpt|L|s_gap)_|0x)?([0-9A-Fa-f]{6,8})\s*\*/"
)
ASSERT_OFFSET = re.compile(r"^ASSERT_OFFSET\(\s*(\w+)\s*,\s*(\w+)\s*,\s*([^)]*)\)")
ASSERT_SIZE = re.compile(r"^ASSERT_SIZE\(\s*(\w+)\s*,")
ENUM_START = re.compile(r"^\s*(?:typedef\s+)?enum\s*\w*\s*\{")
ENUM_CLOSE = re.compile(r"^\s*\}\s*\w*\s*;")
RETURN = (
    r"(?:void|s\d+|u\d+|bool|char|short|int|long|float|double|signed|unsigned|"
    r"Callback|VECTOR|SVECTOR|DVECTOR|RECT|[\w:]+\*)"
)
PROTOTYPE = re.compile(
    rf"^\s*(?:static\s+|extern\s+)?(?:const\s+|volatile\s+)*{RETURN}\s+\**\w+\s*\([^;]*\)\s*;\s*$"
)
EXTERN = re.compile(r"^\s*extern\s+.*;\s*$")
ENUM_MEMBER = re.compile(
    r"^\s*([A-Z][A-Z0-9_]*)\s*=\s*([^,]+?)\s*,?\s*(?:/\*.*?\*/)?\s*$"
)
ROW = re.compile(r"^([A-Za-z_]\w*)\s*=\s*\{.*\baddr\s*=\s*(0[xX][0-9A-Fa-f]+)")
OBJECT_DEF = re.compile(
    r"^(?:static\s+)?(?:const\s+|volatile\s+)*\w+\s+\**(D_\w+|g_\w+|s_\w+)\s*(?:\[[^\]]*\])?\s*="
)
FUNC_DEF = re.compile(r"^(?:MATCH|NON_MATCHING)\s+.*?\b(func_[0-9A-Fa-f]+|\w+)\s*\(")
DECL_FUNC_NAME = re.compile(r"\b([A-Za-z_]\w*)\s*\(")
UNNAMED_PARAM = re.compile(r"\barg\d+\b")

COMMENT_LINE = ("/*", "*", "*/", "//")


@dataclass
class Finding:
    """One broken rule. A fixable finding replaces lines[start:end] with `new`."""

    path: str
    line: int
    rule: str
    detail: str
    fixable: bool = False
    start: int = 0
    end: int = 0
    new: list[str] = field(default_factory=list)

    def render(self) -> str:
        tail = "" if self.fixable else " [manual]"
        return f"{self.path}:{self.line}: {self.rule}: {self.detail}{tail}"


def is_comment(line: str) -> bool:
    stripped = line.strip()
    return not stripped or stripped.startswith(COMMENT_LINE)


def comment_start(
    lines: list[str], i: int, floor: int, hash_comments: bool = False
) -> int:
    """First line of the comment block attached to declaration line `i`."""
    if i == floor or not lines[i - 1].strip():
        return i
    j = i - 1
    while j >= floor and (
        is_comment(lines[j]) or (hash_comments and lines[j].lstrip().startswith("#"))
    ):
        j -= 1
    first = j + 1
    if first == i:
        return i
    block = "".join(lines[first:i]).strip()
    if (
        block.startswith("/*")
        and block.endswith("*/")
        and block.count("/*") == block.count("*/")
    ):
        return first
    if all(line.strip().startswith("//") for line in lines[first:i]):
        return first
    if hash_comments and all(line.strip().startswith("#") for line in lines[first:i]):
        return first
    return i


def address_of(lines: list[str], i: int, floor: int) -> int | None:
    """Address of a declaration: its name, its attached comment, then its trailing comment."""
    m = ADDR_NAME.search(lines[i])
    if m:
        return int(m.group(1), 16)
    for line in lines[comment_start(lines, i, floor) : i]:
        m = ADDR_COMMENT.search(line)
        if m:
            return int(m.group(1), 16)
    m = ADDR_COMMENT.search(lines[i])
    return int(m.group(1), 16) if m else None


def numeric(text: str) -> int | None:
    """Value of a literal, a `1 << n` flag, or a `A +/- B` expression of literals."""
    text = text.strip()
    if re.fullmatch(r"0[xX][0-9A-Fa-f]+|\d+", text):
        return int(text, 0)
    m = re.fullmatch(r"1\s*<<\s*(\d+)", text)
    if m:
        return 1 << int(m.group(1))
    m = re.fullmatch(
        r"(0[xX][0-9A-Fa-f]+|\d+)\s*([+-])\s*(0[xX][0-9A-Fa-f]+|\d+)", text
    )
    if m:
        a, b = int(m.group(1), 0), int(m.group(3), 0)
        return a + b if m.group(2) == "+" else a - b
    return None


def sort_finding(
    path: str,
    lines: list[str],
    items: list[tuple[int, int]],
    order: list[int],
    rule: str,
    detail: str,
) -> Finding | None:
    """Build a finding that places `items[order[pos]]` in slot `pos` of the same region."""
    if order == list(range(len(items))):
        return None
    lo = items[0][0]
    hi = items[-1][1]
    prefix = lines[lo : items[0][0]]
    gaps = [lines[items[j][1] : items[j + 1][0]] for j in range(len(items) - 1)]
    suffix = lines[items[-1][1] : hi]
    new = list(prefix)
    for pos, src in enumerate(order):
        a, b = items[src]
        new.extend(lines[a:b])
        if pos < len(gaps):
            new.extend(gaps[pos])
    new.extend(suffix)
    first_bad = next(pos for pos in range(len(order)) if order[pos] != pos)
    return Finding(
        path,
        items[first_bad][0] + 1,
        rule,
        detail,
        fixable=True,
        start=lo,
        end=hi,
        new=new,
    )


def item_regions(
    lines: list[str], is_item, floor: int = 0
) -> list[list[tuple[int, int]]]:
    """Consecutive declarations separated only by blanks and comments."""
    spans: list[tuple[int, int]] = []
    for i in range(floor, len(lines)):
        if is_item(i):
            spans.append((comment_start(lines, i, floor), i + 1))
    regions: list[list[tuple[int, int]]] = []
    for a, b in spans:
        if regions and all(is_comment(line) for line in lines[regions[-1][-1][1] : a]):
            regions[-1].append((a, b))
        else:
            regions.append([(a, b)])
    return regions


def check_sorted_items(
    path: str,
    lines: list[str],
    regions: list[list[tuple[int, int]]],
    rule: str,
    detail: str,
    anchor=None,
) -> list[Finding]:
    """Sort the keyed items of each region; an unkeyed item anchors the items around it."""
    findings: list[Finding] = []
    for items in regions:
        if len(items) < 2:
            continue
        pinned = [bool(anchor and anchor(span)) for span in items]
        keys = [
            None if pinned[i] else address_of(lines, span[1] - 1, span[0])
            for i, span in enumerate(items)
        ]
        if all(key is None for key in keys):
            continue
        if any(pinned):
            # Moving the other items shifts a pinned declaration's line; the formatter then
            # re-aligns it and check-names/check-tree read that as new debt.
            known = [key for key in keys if key is not None]
            if known != sorted(known):
                findings.append(
                    Finding(
                        path,
                        items[0][0] + 1,
                        rule,
                        f"{detail} (pinned declaration in the run)",
                    )
                )
            continue
        order: list[int] = []
        run: list[int] = []
        for idx, key in enumerate(keys):
            if key is None:
                order.extend(sorted(run, key=lambda j: (keys[j], j)))
                run = []
                order.append(idx)
            else:
                run.append(idx)
        order.extend(sorted(run, key=lambda j: (keys[j], j)))
        finding = sort_finding(path, lines, items, order, rule, detail)
        if finding:
            findings.append(finding)
    return findings


def _anchor(lines: list[str], dupes, span: tuple[int, int]) -> bool:
    line = lines[span[1] - 1]
    if UNNAMED_PARAM.search(line):
        return True
    name = DECL_FUNC_NAME.search(line)
    return bool(name and name.group(1) in dupes)


def check_prototypes(path: str, lines: list[str], dupes=frozenset()) -> list[Finding]:
    """Prototype runs are in address order."""
    regions = item_regions(lines, lambda i: bool(PROTOTYPE.match(lines[i])))
    return check_sorted_items(
        path,
        lines,
        regions,
        "prototypes",
        "prototypes out of address order",
        lambda span: _anchor(lines, dupes, span),
    )


def check_externs(path: str, lines: list[str], dupes=frozenset()) -> list[Finding]:
    """Extern declarations are in address order within a section; an `extern` prototype is anchored like a plain one."""
    regions = item_regions(lines, lambda i: bool(EXTERN.match(lines[i])))
    return check_sorted_items(
        path,
        lines,
        regions,
        "externs",
        "externs out of address order",
        lambda span: "(" in lines[span[1] - 1] and _anchor(lines, dupes, span),
    )


def check_asserts(path: str, lines: list[str]) -> list[Finding]:
    """Each record's ASSERT_OFFSETs are in offset order, then ASSERT_SIZE."""
    findings: list[Finding] = []
    i = 0
    while i < len(lines):
        if not (ASSERT_OFFSET.match(lines[i]) or ASSERT_SIZE.match(lines[i])):
            i += 1
            continue
        end = i + 1
        while end < len(lines) and (
            is_comment(lines[end])
            or ASSERT_OFFSET.match(lines[end])
            or ASSERT_SIZE.match(lines[end])
        ):
            end += 1
        group: list[tuple[int, str, str]] = []
        for j in range(i, end):
            m = ASSERT_OFFSET.match(lines[j])
            if m:
                group.append((j, "offset", m.group(3)))
                continue
            m = ASSERT_SIZE.match(lines[j])
            if m:
                group.append((j, "size", ""))
        types: dict[str, list[tuple[int, str, str]]] = {}
        for j, kind, val in group:
            owner = ASSERT_OFFSET.match(lines[j])
            owner = owner.group(1) if owner else ASSERT_SIZE.match(lines[j]).group(1)
            types.setdefault(owner, []).append((j, kind, val))
        for owner, asserts in types.items():
            values = [
                numeric(val) if kind == "offset" else None for _, kind, val in asserts
            ]
            if any(
                v is None for k, v in enumerate(values) if asserts[k][1] == "offset"
            ):
                findings.append(
                    Finding(
                        path,
                        asserts[0][0] + 1,
                        "asserts",
                        f"{owner}: offset expression needs a person to order",
                    )
                )
                continue
            if len(types) > 1:
                findings.append(
                    Finding(
                        path,
                        asserts[0][0] + 1,
                        "asserts",
                        f"{owner}: mixed record asserts need a person to order",
                    )
                )
                continue
            order = sorted(
                range(len(asserts)),
                key=lambda k: (1 if asserts[k][1] == "size" else 0, values[k] or 0, k),
            )
            items = [(j, j + 1) for j, _, _ in asserts]
            finding = sort_finding(
                path,
                lines,
                items,
                order,
                "asserts",
                f"{owner}: ASSERT_OFFSET in offset order, then ASSERT_SIZE",
            )
            if finding:
                findings.append(finding)
        i = end
    return findings


def check_enums(path: str, lines: list[str]) -> list[Finding]:
    """ID and flag enums list explicit values in ascending order."""
    findings: list[Finding] = []
    i = 0
    while i < len(lines):
        if not ENUM_START.match(lines[i]):
            i += 1
            continue
        j = i + 1
        while j < len(lines) and not ENUM_CLOSE.match(lines[j]):
            j += 1
        members: list[tuple[int, str, int, str]] = []
        complete = True
        for k in range(i + 1, j):
            m = ENUM_MEMBER.match(lines[k])
            if not m:
                if lines[k].strip() and not lines[k].strip().startswith("/*"):
                    complete = False
                continue
            value = numeric(m.group(2))
            if value is None:
                complete = False
                break
            members.append((k, m.group(1), value, lines[k]))
        names = " ".join(name for _, name, _, _ in members)
        is_id_or_flag = (
            "_ID_" in names
            or "_FLAG" in names
            or re.search(r"\b(?:Id|Ids|Flags)\b", lines[i])
        )
        if members and complete and is_id_or_flag:
            values = [value for _, _, value, _ in members]
            if values != sorted(values):
                items = [
                    (comment_start(lines, k, i + 1), k + 1) for k, _, _, _ in members
                ]
                order = sorted(range(len(members)), key=lambda k: (members[k][2], k))
                finding = sort_finding(
                    path,
                    lines,
                    items,
                    order,
                    "enum values",
                    "ID/flag enum values out of order",
                )
                findings.append(
                    finding
                    if finding
                    else Finding(
                        path,
                        members[0][0] + 1,
                        "enum values",
                        "ID/flag enum values out of order",
                    )
                )
        i = j
    return findings


def table_regions(lines: list[str]) -> list[tuple[int, int]]:
    """Line ranges of each symbols.toml table, excluding the header line."""
    starts = [i for i, line in enumerate(lines) if re.match(r'^\["[^"]+"\]', line)]
    return [(s + 1, e) for s, e in zip(starts, starts[1:] + [len(lines)], strict=False)]


def check_symbols(path: str, lines: list[str]) -> list[Finding]:
    """Rows inside each symbols.toml table are in address order."""
    findings: list[Finding] = []
    for lo, hi in table_regions(lines):
        items: list[tuple[int, int]] = []
        for i in range(lo, hi):
            if ROW.match(lines[i]):
                items.append((comment_start(lines, i, lo, hash_comments=True), i + 1))
        if len(items) < 2:
            continue
        keys = [int(ROW.match(lines[b - 1]).group(2), 16) for _, b in items]
        order = sorted(range(len(items)), key=lambda k: (keys[k], k))
        finding = sort_finding(
            path, lines, items, order, "symbols.toml rows", "rows out of address order"
        )
        if finding:
            findings.append(finding)
    return findings


def check_data_file(path: str, lines: list[str]) -> list[Finding]:
    """Data definitions and MATCH functions in a file are in address order (report only)."""
    items: list[tuple[int, int | None, str]] = []
    for i, line in enumerate(lines):
        m = OBJECT_DEF.match(line)
        if not m:
            m = FUNC_DEF.match(line)
        if not m:
            continue
        name = m.group(1)
        mm = ADDR_NAME.search(name)
        if not mm:
            continue
        items.append((i, int(mm.group(1), 16), name))
    findings: list[Finding] = []
    for (_, a, name), (j, b, other) in zip(items, items[1:], strict=False):
        if a > b:
            findings.append(
                Finding(
                    path,
                    j + 1,
                    "data/functions",
                    f"{name} at 0x{a:08X} precedes {other} at 0x{b:08X}",
                )
            )
    return findings


def tracked() -> tuple[list[str], list[str]]:
    paths = ls_files("include", "src", root=ROOT)
    headers = [
        f for f in paths if f.endswith(".h") and not f.startswith("include/psyq/")
    ]
    data = [f for f in paths if f.endswith(".c")]
    return headers, data


def changed(ref: str) -> tuple[list[str], list[str]]:
    base = merge_base(ref, root=ROOT)
    paths = changed_files(
        "--diff-filter=ACMR",
        f"{base}...HEAD",
        "--",
        "include",
        "src",
        SPLIT,
        root=ROOT,
    )
    return (
        [f for f in paths if f.endswith(".h") and not f.startswith("include/psyq/")],
        [f for f in paths if f.endswith(".c")],
    )


def duplicate_prototype_names(headers: list[str]) -> set[str]:
    """Functions declared in more than one header; check-tree reads a moved one as a new duplicate."""
    owners: dict[str, set[str]] = {}
    for path in headers:
        target = ROOT / path
        if not target.is_file():
            continue
        for line in target.read_text(errors="replace").splitlines():
            if "(" not in line or not line.rstrip().endswith(";"):
                continue
            if not (PROTOTYPE.match(line) or EXTERN.match(line)):
                continue
            name = DECL_FUNC_NAME.search(line)
            if name:
                owners.setdefault(name.group(1), set()).add(path)
    return {name for name, files in owners.items() if len(files) > 1}


def inspect(headers: list[str], data: list[str]) -> list[Finding]:
    all_headers, _ = tracked()
    dupes = duplicate_prototype_names(all_headers)
    findings: list[Finding] = []
    for path in headers:
        target = ROOT / path
        if not target.is_file():
            continue
        lines = target.read_text(errors="replace").splitlines(keepends=True)
        # One rule at a time: a moved extern run can share lines with a prototype run, so each
        # rule must see the lines the previous one wrote.
        for check in (check_asserts, check_enums, check_prototypes, check_externs):
            hits = (
                check(path, lines, dupes)
                if check in (check_prototypes, check_externs)
                else check(path, lines)
            )
            findings.extend(hits)
    for target in sorted((ROOT / SPLIT).glob("*.toml")):
        if target.is_file():
            name = target.relative_to(ROOT).as_posix()
            lines = target.read_text(errors="replace").splitlines(keepends=True)
            hits = check_symbols(name, lines)
            findings.extend(hits)
    for path in data:
        target = ROOT / path
        if target.is_file():
            findings.extend(
                check_data_file(
                    path, target.read_text(errors="replace").splitlines(keepends=True)
                )
            )
    return findings


def main() -> int:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("--diff", metavar="REF", help="check files changed against REF")
    parser.add_argument(
        "paths", nargs="*", help="check these files instead of the whole tree"
    )
    args = parser.parse_args()
    if args.paths:
        headers = [p for p in args.paths if p.endswith(".h")]
        data = [p for p in args.paths if p.endswith(".c")]
    elif args.diff:
        headers, data = changed(args.diff)
    else:
        headers, data = tracked()
    findings = inspect(headers, data)
    for finding in findings:
        print(finding.render())
    fixable = [f for f in findings if f.fixable]
    if findings:
        print(
            f"order-check: {len(findings)} finding(s), {len(fixable)} need a mechanical reorder",
            file=sys.stderr,
        )
    return 1 if fixable else 0


if __name__ == "__main__":
    raise SystemExit(main())
