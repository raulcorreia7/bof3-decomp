#!/usr/bin/env python3
"""Fail when a change loses or degrades a named thing that the merge base has.

The check reads every C source and header under `src/` and `include/` (not `include/psyq`)
that changed between `git merge-base REF HEAD` and HEAD, at both revisions, and compares:

- `static inline` helpers, function names and globals (`g_`, `s_` and every other non-default name);
- `#define` constants and macros;
- typedefs, enums and their values;
- struct and union definitions, nested records included, and their named members.

A thing is lost when its name is gone from HEAD and no successor holds it. A successor is a new
name at the same `config/symbols.toml` address (functions and globals), a new member at the same
offset of the same record, a new define with the same value, a new enumerator with the same value
in the same enum, or a new record with the same layout. A thing degrades when its successor is a
default or unknown name (`func_`, `D_`, `unk_`, `pad`), when a typed member's successor is raw
bytes or an integer, or when a record global is split back into loose integer globals.

Clang parses the sources (`-fsyntax-only` with the AST as JSON and the record layouts), so struct
members, nested records and offsets come from a real C parse. `#define` lines are read as text.

A deliberate removal passes with a commit message line between the merge base and HEAD:

    Kept-Removed: <name> <reason>

Usage: python3 tools/check_kept.py REF [HEAD]
"""

from __future__ import annotations

import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import tomllib
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, field
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SYMBOLS = "config/symbols.toml"
CLANG = os.environ.get("CHECK_KEPT_CLANG", "clang")
CLANG_FLAGS = [
    "--target=mipsel-unknown-elf",
    "-fsyntax-only",
    "-ferror-limit=0",
    "-Wno-everything",
    # The context m2c reads: INCLUDE_ASM expands to nothing, and asm.h hides the register names.
    "-DM2CTX",
    "-DLANGUAGE_C",
    "-Isrc",
    "-Iinclude",
    "-Iinclude/psyq",
]
DEFAULT_NAME = re.compile(
    r"^(?:(?:func|D|jtbl|jpt|s_gap|L)_[0-9A-Fa-f]{8}\w*|unk\w*|pad\w*|field_\w*|_+\w*)$"
)
WEAK_WORDS = frozenset(
    "u8 s8 u16 s16 u32 s32 u64 s64 int char short long unsigned signed void const volatile".split()
)
KEPT_REMOVED = re.compile(r"^Kept-Removed:\s*(\S+)", re.M)
DEFINE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+(\w+)(\([^)]*\))?(.*)$")
INCLUDE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)
IDENT = re.compile(r"[A-Za-z_]\w*")
NUMBER = re.compile(r"\b(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\b")
COMMENT_OR_STRING = re.compile(
    r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S
)
LAYOUT_RECORD = re.compile(r"^\s*0 \| (struct|union) (.+)$")
LAYOUT_MEMBER = re.compile(r"^\s*(\d+)(?::\d+-\d+)? \|( +)(.+) (\w+)$")
LAYOUT_SIZE = re.compile(r"\[sizeof=(\d+),")


def is_default(name: str) -> bool:
    return bool(DEFAULT_NAME.match(name))


def is_weak(ctype: str) -> bool:
    """Whether a C type is a plain integer, void or an array of them: no record, enum or pointer."""
    if "*" in ctype or "(" in ctype:
        return False
    words = IDENT.findall(re.sub(r"\[[^\]]*\]", " ", ctype))
    return all(word in WEAK_WORDS for word in words)


def normalize_value(text: str) -> str:
    """One spelling for a define body: comments and spaces dropped, numbers in decimal."""
    text = COMMENT_OR_STRING.sub(
        lambda m: m.group(0) if m.group(0)[0] in "\"'" else " ", text
    )
    text = NUMBER.sub(lambda m: str(int(m.group(1), 0)), text)
    return re.sub(r"\s+", "", text)


@dataclass
class Member:
    offset: int
    path: str
    ctype: str
    size: int


@dataclass
class Entities:
    functions: dict[str, str] = field(default_factory=dict)  # name -> file
    inlines: dict[str, str] = field(default_factory=dict)
    globals: dict[str, str] = field(default_factory=dict)  # name -> type
    typedefs: dict[str, str] = field(default_factory=dict)
    enums: dict[str, tuple[str, int]] = field(
        default_factory=dict
    )  # name -> (enum, value)
    defines: dict[str, str] = field(default_factory=dict)  # name -> normalized value
    records: dict[str, list[list[Member]]] = field(
        default_factory=lambda: defaultdict(list)
    )
    record_sizes: dict[str, int] = field(default_factory=dict)


# --- Text -----------------------------------------------------------------------------------


def strip_comments(text: str) -> str:
    return COMMENT_OR_STRING.sub(" ", text)


def defines_in(text: str) -> dict[str, str]:
    """Every `#define` in one file, guards excepted: name -> normalized value."""
    found = {}
    lines = text.replace("\\\r\n", "\\\n").split("\n")
    i = 0
    while i < len(lines):
        line = lines[i]
        while line.endswith("\\") and i + 1 < len(lines):
            i += 1
            line = line[:-1] + " " + lines[i]
        i += 1
        match = DEFINE.match(line)
        if not match:
            continue
        name, params, body = match.groups()
        value = normalize_value((params or "") + body)
        if not value and name.endswith("_H"):
            continue  # an include guard
        found[name] = value
    return found


# --- Clang ----------------------------------------------------------------------------------


def walk_decls(tree: dict, wanted: set[str]):
    """Yield (file, node) for each top-level declaration; the JSON writes a file only when it changes."""
    state = {"file": None, "line": None}

    def visit(node):
        if isinstance(node, dict):
            if "offset" in node and ("line" in node or "col" in node):
                if "file" in node:
                    state["file"] = os.path.normpath(node["file"])
                if "line" in node:
                    state["line"] = node["line"]
            for key, value in node.items():
                if key != "includedFrom":
                    visit(value)
        elif isinstance(node, list):
            for item in node:
                visit(item)

    def owner(node):
        loc = node.get("loc", {})
        visit(loc)
        return state["file"], state["line"], (loc.get("expansionLoc") or loc).get("col")

    for node in tree.get("inner", []):
        file, line, col = owner(node)
        for key, value in node.items():
            if key != "loc":
                visit(value)
        if file in wanted:
            yield file, line, col, node


def enum_value(node: dict) -> int | None:
    for child in node.get("inner", []):
        if child.get("kind") == "ConstantExpr" and "value" in child:
            return int(child["value"])
    return None


def owned_tag(typedef: dict) -> str | None:
    """The id of the record a typedef defines in place: clang 18 wraps it in an ElaboratedType."""
    for child in typedef.get("inner", []):
        if "ownedTagDecl" in child:
            return child["ownedTagDecl"].get("id")
        if child.get("isTagOwned"):
            return child.get("decl", {}).get("id")
    return None


def parse_layouts(text: str) -> tuple[dict[str, list[Member]], dict[str, int]]:
    """Record name -> its members at every depth, with absolute offsets, from -fdump-record-layouts."""
    layouts: dict[str, list[Member]] = {}
    sizes: dict[str, int] = {}
    for block in text.split("*** Dumping AST Record Layout")[1:]:
        lines = block.strip("\n").split("\n")
        head = LAYOUT_RECORD.match(lines[0])
        if not head:
            continue
        # Clang 18 and older write "(anonymous at", later ones "(unnamed at".
        name = f"{head.group(1)} {head.group(2).strip()}".replace(
            "(anonymous at ", "(unnamed at "
        )
        members: list[Member] = []
        stack: list[tuple[int, str]] = []
        for line in lines[1:]:
            size = LAYOUT_SIZE.search(line)
            if size:
                sizes[name] = int(size.group(1))
                break
            match = LAYOUT_MEMBER.match(line)
            if not match:
                continue
            offset, indent, ctype, member = match.groups()
            depth = len(indent) // 2
            stack = stack[: depth - 1]
            path = ".".join([part for _, part in stack] + [member])
            stack.append((depth, member))
            members.append(Member(int(offset), path, ctype.strip(), 0))
        # A member's size is the distance to the next member at its depth or above.
        record_size = sizes.get(name, 0)
        for i, member in enumerate(members):
            depth = member.path.count(".")
            end = record_size
            for later in members[i + 1 :]:
                if later.path.count(".") <= depth:
                    end = later.offset
                    break
            member.size = max(end - member.offset, 0)
        layouts[name] = members
    return layouts, sizes


def run_clang(tree: Path, unit: str, wanted: set[str]) -> Entities:
    """Parse one translation unit and keep what the wanted files declare."""
    flags = [CLANG, *CLANG_FLAGS, f"-I{Path(unit).parent}", "-x", "c", unit]
    ast = subprocess.run(
        [*flags, "-Xclang", "-ast-dump=json"],
        cwd=tree,
        capture_output=True,
        check=False,
    )
    layout = None
    # -fdump-record-layouts-complete (clang 15+) dumps every complete record, not only the used ones.
    for dump in ("-fdump-record-layouts-complete", "-fdump-record-layouts"):
        layout = subprocess.run(
            [*flags, "-Xclang", dump],
            cwd=tree,
            capture_output=True,
            text=True,
            check=False,
        )
        if "Dumping AST Record Layout" in layout.stdout:
            break
    found = Entities()
    record_keys: dict[str, str] = {}  # layout name -> record name
    anonymous: dict[str, str] = {}  # RecordDecl id -> layout name of an unnamed record
    try:
        decls = list(walk_decls(json.loads(ast.stdout or b"{}"), wanted))
    except json.JSONDecodeError:
        decls = []
    for file, line, col, node in decls:
        kind, name = node.get("kind"), node.get("name", "")
        if node.get("isImplicit"):
            continue
        if kind == "FunctionDecl" and name:
            if node.get("inline") and node.get("storageClass") == "static":
                found.inlines[name] = file
            else:
                found.functions[name] = file
        elif kind == "VarDecl" and name:
            found.globals[name] = node.get("type", {}).get("qualType", "")
        elif kind == "RecordDecl" and node.get("completeDefinition"):
            tag = node.get("tagUsed", "struct")
            if name:
                record_keys[f"{tag} {name}"] = name
            else:
                anonymous[node["id"]] = f"{tag} (unnamed at {file}:{line}:{col})"
        elif kind == "TypedefDecl" and name:
            found.typedefs[name] = node.get("type", {}).get("qualType", "")
            owned = owned_tag(node)
            if owned in anonymous:
                record_keys[anonymous[owned]] = name
        elif kind == "EnumDecl":
            value = -1
            for child in node.get("inner", []):
                if child.get("kind") != "EnumConstantDecl":
                    continue
                explicit = enum_value(child)
                value = explicit if explicit is not None else value + 1
                found.enums[child["name"]] = (name, value)
    layouts, sizes = parse_layouts(layout.stdout)
    for key, record in record_keys.items():
        if key in layouts:
            found.records[record].append(layouts[key])
            found.record_sizes[record] = sizes.get(key, 0)
    return found


# --- Revisions ------------------------------------------------------------------------------


def git(*args: str) -> str:
    return subprocess.check_output(["git", *args], cwd=ROOT, text=True)


def extract(rev: str, into: Path) -> None:
    archive = subprocess.run(
        ["git", "archive", rev, "src", "include"],
        cwd=ROOT,
        capture_output=True,
        check=True,
    )
    subprocess.run(["tar", "-x", "-C", str(into)], input=archive.stdout, check=True)


def tracked(path: str) -> bool:
    return (
        path.startswith(("src/", "include/"))
        and not path.startswith("include/psyq/")
        and path.endswith((".c", ".h"))
    )


def includers(tree: Path) -> dict[str, list[str]]:
    """Header path -> the files that include it by a quoted include."""
    found: dict[str, list[str]] = defaultdict(list)
    for path in sorted(tree.glob("src/**/*.[ch]")):
        rel = path.relative_to(tree).as_posix()
        for name in INCLUDE.findall(path.read_text(encoding="utf-8", errors="replace")):
            for base in (path.parent, tree / "src", tree / "include"):
                target = base / name
                if target.is_file():
                    found[target.relative_to(tree).as_posix()].append(rel)
                    break
    return found


def unit_for(path: str, users: dict[str, list[str]]) -> str | None:
    """The translation unit that gives a file its context: itself, or the first C file above it."""
    if path.endswith(".c") or path.startswith("include/"):
        return path
    queue, seen = [path], {path}
    while queue:
        current = queue.pop(0)
        for user in users.get(current, []):
            if user.endswith(".c"):
                return user
            if user not in seen:
                seen.add(user)
                queue.append(user)
    return None


def merge(into: Entities, part: Entities) -> None:
    into.functions.update(part.functions)
    into.inlines.update(part.inlines)
    into.globals.update(part.globals)
    into.typedefs.update(part.typedefs)
    into.enums.update(part.enums)
    into.defines.update(part.defines)
    for name, layouts in part.records.items():
        into.records[name].extend(layouts)
    into.record_sizes.update(part.record_sizes)


def scan(tree: Path, paths: list[str]) -> Entities:
    """Every entity the given files declare at one revision."""
    found = Entities()
    paths = [p for p in paths if (tree / p).is_file()]
    for path in paths:
        found.defines.update(
            defines_in((tree / path).read_text(encoding="utf-8", errors="replace"))
        )
    users = (
        includers(tree)
        if any(p.startswith("src/") and p.endswith(".h") for p in paths)
        else {}
    )
    units: dict[str, set[str]] = defaultdict(set)
    for path in paths:
        unit = unit_for(path, users)
        if unit:
            units[unit].add(path)
    with ThreadPoolExecutor(max_workers=min(8, os.cpu_count() or 1)) as pool:
        for part in pool.map(
            lambda item: run_clang(tree, item[0], item[1]), units.items()
        ):
            merge(found, part)
    return found


def read_tree(tree: Path) -> tuple[dict[str, set[str]], dict[str, str]]:
    """Per file, the identifiers it uses outside comments and strings; and every define."""
    uses: dict[str, set[str]] = {}
    defines: dict[str, str] = {}
    for path in tree.glob("**/*.[ch]"):
        rel = path.relative_to(tree).as_posix()
        if tracked(rel):
            text = path.read_text(encoding="utf-8", errors="replace")
            uses[rel] = set(IDENT.findall(strip_comments(text)))
            defines.update(defines_in(text))
    return uses, defines


def addresses(
    rev: str,
) -> tuple[dict[str, set[tuple[str, int]]], dict[tuple[str, int], str]]:
    text = subprocess.check_output(["git", "show", f"{rev}:{SYMBOLS}"], cwd=ROOT)
    by_name: dict[str, set[tuple[str, int]]] = defaultdict(set)
    by_addr: dict[tuple[str, int], str] = {}
    for target, rows in tomllib.loads(text.decode()).items():
        for name, row in rows.items():
            if isinstance(row, dict) and "addr" in row:
                by_name[name].add((target, row["addr"]))
                if not row.get("alias"):
                    by_addr[(target, row["addr"])] = name
    return by_name, by_addr


# --- Comparison -----------------------------------------------------------------------------


@dataclass
class Snapshot:
    entities: Entities
    uses: dict[str, set[str]]
    defines: dict[str, str]
    names: dict[str, set[tuple[str, int]]]
    rows: dict[tuple[str, int], str]
    tokens: set[str] = field(init=False)

    def __post_init__(self) -> None:
        self.tokens = set().union(*self.uses.values())


def address_successor(
    name: str, before: Snapshot, after: Snapshot
) -> tuple[str, str | None]:
    """('kept', new) when a non-default name holds the address now, else ('degraded'|'lost', None)."""
    places = before.names.get(name, set())
    if not places:
        return "lost", None
    if places & after.names.get(name, set()):
        return "kept", name  # an alias row: the global is a member of a record now
    news = {after.rows.get(place) for place in places}
    named = sorted(n for n in news if n and not is_default(n))
    if named:
        return "kept", named[0]
    return "degraded", None


def member_problems(
    record: str, old: list[Member], new_layouts: list[list[Member]]
) -> list[str]:
    problems = []
    new = [member for layout in new_layouts for member in layout]
    for member in old:
        leaf = member.path.rsplit(".", 1)[-1]
        if is_default(leaf):
            continue
        same = [m for m in new if m.path == member.path]
        if same:
            if not is_weak(member.ctype) and all(is_weak(m.ctype) for m in same):
                problems.append(
                    f"{record}.{member.path} at +0x{member.offset:X}: {member.ctype} became {same[0].ctype}"
                )
            continue
        here = [m for m in new if m.offset == member.offset]
        named = [m for m in here if not is_default(m.path.rsplit(".", 1)[-1])]
        if named:
            if not is_weak(member.ctype) and all(is_weak(m.ctype) for m in named):
                problems.append(
                    f"{record}.{member.path} at +0x{member.offset:X}: {member.ctype} became {named[0].ctype} {named[0].path}"
                )
            continue
        if here:
            problems.append(
                f"{record}.{member.path} at +0x{member.offset:X}: became {here[0].path}"
            )
            continue
        inside = [
            m
            for m in new
            if m.offset < member.offset < m.offset + m.size and "[" in m.ctype
        ]
        if inside and not is_default(inside[0].path.rsplit(".", 1)[-1]):
            if not is_weak(member.ctype) and is_weak(inside[0].ctype):
                problems.append(
                    f"{record}.{member.path} at +0x{member.offset:X}: {member.ctype} became bytes of {inside[0].path}"
                )
            continue
        problems.append(
            f"{record}.{member.path} at +0x{member.offset:X}: no member holds it"
        )
    return problems


def layout_signature(layouts: list[list[Member]]) -> set[tuple]:
    return {tuple((m.offset, m.path.count(".")) for m in layout) for layout in layouts}


def compare(before: Snapshot, after: Snapshot, removed: set[str]) -> list[str]:
    """Every loss or degradation from BEFORE to AFTER, one line each."""
    problems: list[str] = []
    old, new = before.entities, after.entities

    def gone(name: str) -> bool:
        # A name built by token pasting (a static assertion) never appears in the text.
        return (
            not is_default(name)
            and name in before.tokens
            and name not in after.tokens
            and name not in removed
        )

    def added(name: str) -> bool:
        return name not in before.tokens

    for kind, table in (("function", old.functions), ("global", old.globals)):
        for name in sorted(n for n in table if gone(n)):
            verdict, successor = address_successor(name, before, after)
            if verdict == "kept":
                if kind == "global" and successor:
                    old_type, new_type = old.globals[name], new.globals.get(successor)
                    if new_type and not is_weak(old_type) and is_weak(new_type):
                        problems.append(
                            f"global {name} ({old_type}) became {new_type} {successor}"
                        )
                continue
            what = "has only a default name now" if verdict == "degraded" else "is gone"
            problems.append(f"{kind} {name} {what}")
    for name in sorted(n for n in old.inlines if gone(n)):
        problems.append(f"static inline {name} is gone")
    for name in sorted(n for n in old.defines if gone(n)):
        # Kept when the files that used it now use a define of the same value.
        value = old.defines[name]
        sites = [
            f for f, used in before.uses.items() if name in used and f in after.uses
        ]
        same = {n for n, v in after.defines.items() if v == value and n != name}
        if value and any(same & after.uses[f] for f in sites):
            continue
        problems.append(f"#define {name} is gone")
    for name in sorted(n for n in old.enums if gone(n)):
        enum, value = old.enums[name]
        if any(e == (enum, value) and added(n) for n, e in new.enums.items() if enum):
            continue
        if any(v == str(value) and added(n) for n, v in new.defines.items()):
            continue
        problems.append(f"enumerator {name} = {value} is gone")
    for name in sorted(n for n in old.enums if n in new.enums):
        if old.enums[name][1] != new.enums[name][1]:
            problems.append(
                f"enumerator {name} changed value {old.enums[name][1]} -> {new.enums[name][1]}"
            )
    old_records = set(old.records)
    for name in sorted(n for n in set(old.typedefs) - old_records if gone(n)):
        if any(t == old.typedefs[name] and added(n) for n, t in new.typedefs.items()):
            continue
        problems.append(f"typedef {name} is gone")
    for name in sorted(old_records):
        if is_default(name) or name in removed:
            continue
        layouts = new.records.get(name)
        if layouts is None and gone(name):
            signature = layout_signature(old.records[name])
            twins = [
                n
                for n, other in new.records.items()
                if added(n) and layout_signature(other) & signature
            ]
            if twins:
                layouts = new.records[twins[0]]
            else:
                problems.append(f"record {name} is gone")
                continue
        if layouts is None:
            continue  # defined in a file this change does not touch
        for layout in old.records[name]:
            problems.extend(
                f"member {p}" for p in member_problems(name, layout, layouts)
            )
    return sorted(set(problems))


def removals(base: str, head: str) -> set[str]:
    return set(KEPT_REMOVED.findall(git("log", "--format=%B", f"{base}..{head}")))


def record_files(tree: Path, names: set[str]) -> set[str]:
    """Files at one revision that define one of the named records."""
    if not names:
        return set()
    pattern = re.compile(
        r"\b(?:struct|union)\s+("
        + "|".join(map(re.escape, names))
        + r")\s*\{|\}\s*("
        + "|".join(map(re.escape, names))
        + r")\s*;"
    )
    found = set()
    for path in tree.glob("**/*.h"):
        rel = path.relative_to(tree).as_posix()
        if tracked(rel) and pattern.search(
            path.read_text(encoding="utf-8", errors="replace")
        ):
            found.add(rel)
    return found


def main(argv: list[str]) -> int:
    if len(argv) == 2 and argv[1] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    if len(argv) not in (2, 3):
        print(__doc__.strip(), file=sys.stderr)
        return 2
    if not shutil.which(CLANG):
        print(f"check-kept: skipped, no {CLANG} on PATH")
        return 0
    ref, head = argv[1], argv[2] if len(argv) == 3 else "HEAD"
    base = git("merge-base", ref, head).strip()
    changed = [
        p
        for p in git("diff", "--no-renames", "--name-only", base, head).split()
        if tracked(p)
    ]
    if not changed:
        print(f"check-kept: no source changed against {ref}")
        return 0
    with tempfile.TemporaryDirectory(prefix="check-kept-") as tmp:
        trees = {rev: Path(tmp) / rev for rev in ("before", "after")}
        for rev, commit in (("before", base), ("after", head)):
            trees[rev].mkdir()
            extract(commit, trees[rev])
        before_entities = scan(trees["before"], changed)
        after_uses, after_defines = read_tree(trees["after"])
        after_tokens = set().union(*after_uses.values())
        after_entities = scan(trees["after"], changed)
        # A record kept by name but defined in an untouched file still needs its members.
        missing = {
            n
            for n in before_entities.records
            if n in after_tokens and n not in after_entities.records
        }
        extra = sorted(record_files(trees["after"], missing) - set(changed))
        if extra:
            merge(after_entities, scan(trees["after"], extra))
        before = Snapshot(
            before_entities, *read_tree(trees["before"]), *addresses(base)
        )
        after = Snapshot(after_entities, after_uses, after_defines, *addresses(head))
    problems = compare(before, after, removals(base, head))
    for problem in problems:
        print(problem)
    if problems:
        print(
            f"check-kept: {len(problems)} name(s) lost or degraded against {ref}; keep them, or add "
            "a 'Kept-Removed: <name> <reason>' line to a commit message"
        )
        return 1
    print(
        f"check-kept: every named thing in {len(changed)} changed file(s) kept against {ref}"
    )
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
