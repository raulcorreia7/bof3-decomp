#!/usr/bin/env python3
"""Add, rename and inspect symbols everywhere they live.

    tools/symbol.py add IMAGE NAME 0xADDR --source TEXT [--type T] [--size N] [--alias]
    tools/symbol.py rename OLD NEW [--image IMAGE...] [--local | --scope PATH...] [--source TEXT]
                           [--type T] [--size N] [--dry-run]
    tools/symbol.py params FUNC OLD=NEW...
    tools/symbol.py refs [DIR...]
    tools/symbol.py check
    tools/symbol.py at IMAGE 0xADDR... [--diff [BASE]]
    tools/symbol.py member TYPE 0xOFF
    tools/symbol.py uses NAME|IMAGE@0xADDR

`add` writes one row of config/symbols.toml in address order.

`rename` changes a function or global in every tracked file of the scope: the definition, each
prototype and use, `config/` references, and the unit file `OLD.c` (`git mv`). It writes the
row of config/symbols.toml: a new row for an address name (`--source` describes the symbol), or the
renamed key of an existing row. An address name (`func_<ADDR>`, `D_<ADDR>`) stays in a comment
above its definition and declaration. A named symbol is one name in every image: with no
`--image` its row is renamed in every table that has it. An address name is unique only per
image, so give `--image` once per image that holds the twin; `--local` limits the files to those
images' `src/` and `config/` folders (`--scope` to the given paths). The resident images
(`exe/slus_004_22`, `emi/etc/game/00`) are visible everywhere and rename with no scope.

`rename` checks the planned edits and moves before changing sources. A failure restores the
files, paths and index; success also requires no old named reference in src/include/config,
including untracked files. Address-name comments and unrelated images retain their provenance.

`params` renames parameters of one function in its unit file `FUNC.c` and on its prototype
lines in headers.

`refs` ranks the address-named units (`func_<ADDR>.c`) under the folders (default `src`) by how
often their name occurs in `src`, `include` and `asm`: the most used are the best to name first.

`check` reports the table's problems: a table out of address order, a name at two addresses, an
address with two non-alias names, a row repeated in several images, an alias no source mentions,
and a row with no `source`. The first three exit 1; the rest are a list. Fix ordering by hand or
with `tools/symbol.py add`; never renumber a row.
`at` prints the named owner of each address in one image: `NAME+0xOFF (type, size) [table]`, the
member path when the owner is a record (`g_Game.members[2].pos.x`), or `no named owner`. A hit comes
from the image's own table or a resident one (`exe/slus_004_22`, `emi/etc/game/00`). `--diff` reads
the `D_<ADDR>` names the branch adds instead of the addresses; with an image it reads only that
image's sources, and `BASE` defaults to `public/main`.

`member` prints the member path and type at a byte offset of a record, from the compiler's own
layout: `tools/symbol.py member Actor 0xB` prints `param.actor_slot` and its `u8` type, plus every
other name of that union cell. Layouts are cached in `build/symbol-layouts.json` by the headers clang
reads.

`uses` lists every reference to a symbol in one table: C uses (`src`, `include`), assembly uses in
the open functions (`asm`, the function and its instruction) and, when the image's Rizin project
exists, its cross-references. `IMAGE@0xADDR` resolves the owner first and also lists the retail
cross-references of that address. The first query in an image analyses its Rizin project and caches
every cross-reference in `build/symbol-xrefs` until the project changes.

Run `meson compile -C build/meson check-<image>` for every touched image afterwards.
"""

from __future__ import annotations

import argparse
import collections
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import tomllib
from dataclasses import dataclass
from pathlib import Path

from bof3.link import symbols
from bof3.resolve.ids import source_folder
from bof3.source import ctext, symtab

ROOT = Path(__file__).resolve().parent.parent
SYMBOLS = ROOT / "config/symbols.toml"
ADDRESS_NAME = re.compile(r"(func|D|jtbl)_([0-9A-F]{8})$")
RESIDENT = ("exe/slus_004_22", "emi/etc/game/00")
DEFAULT_SCOPE = ("src", "include", "config", "docs", "asm")


def git(*args: str, check: bool = True, env: dict[str, str] | None = None) -> str:
    """Run Git in the repository and return stdout."""
    return subprocess.run(
        ["git", *args], cwd=ROOT, capture_output=True, text=True, check=check, env=env
    ).stdout


def grep_files(word: str, scope: list[str]) -> list[str]:
    """Return the tracked files under ``scope`` that hold ``word`` as a whole word."""
    names = git("grep", "-l", "-z", "-w", "-e", word, "--", *scope, check=False)
    return [name for name in names.split("\0") if name]


def add(args: argparse.Namespace) -> int:
    """Insert one row."""
    addr = int(args.addr, 16)
    row = symtab.format_row(
        args.name, addr, type=args.type, size=int(args.size, 0) if args.size else None,
        source=args.source, alias=args.alias,
    )  # fmt: skip
    text = SYMBOLS.read_text(encoding="utf-8")
    SYMBOLS.write_text(
        symtab.add_row(text, args.image, args.name, row, addr), encoding="utf-8"
    )
    print(f"added {args.name} to [{args.image}]")
    return 0


def tables_with(text: str, name: str) -> list[str]:
    """Return the images whose table has a row ``name``."""
    images, image = [], ""
    for line in text.split("\n"):
        if line.startswith('["'):
            image = line[2:-2]
        elif line.startswith(name + " = "):
            images.append(image)
    return images


def local_scope(images: list[str]) -> list[str]:
    """Return the folders that belong to the images."""
    folders = [
        f
        for image in images
        for f in (f"src/{source_folder(image)}", f"config/{image}")
    ]
    missing = [f for f in folders if not (ROOT / f).is_dir()]
    if missing:
        raise SystemExit(f"symbol: no such folder {', '.join(missing)}")
    return folders


def with_address_comment(path: Path, old: str, new: str, text: str) -> str:
    """Keep the original address above a renamed definition or declaration."""
    lines = text.split("\n")
    out = []
    function = re.compile(r"(MATCH|NON_MATCHING)\b[^=;]*\b" + re.escape(new) + r"\(")
    prototype = re.compile(r"[A-Za-z_][^=;{}]*\b" + re.escape(new) + r"\(.*\);")
    variable = re.compile(
        r"(extern\s)?[A-Za-z_][^=;{}()]*\b" + re.escape(new) + r"(\[[^;]*\])?;"
    )
    for line in lines:
        if path.suffix == ".h":
            hit = variable if old.startswith("D_") else prototype
            wanted = bool(hit.match(line)) and not line.startswith(
                ("#", "return", "        ")
            )
        else:
            wanted = bool(function.match(line))
        if wanted and not (out and out[-1].strip() == f"/* {old} */"):
            if (
                path.suffix == ".c"
                and out
                and out[-1].startswith("#ifdef NON_MATCHING")
            ):
                out.insert(len(out) - 1, f"/* {old} */")
            else:
                out.append(f"/* {old} */")
        out.append(line)
    return "\n".join(out)


def check_rename(
    old: str, edits: dict[Path, str], scope: list[str], address: bool
) -> None:
    """Reject old references in the planned or current source tree."""
    pattern = re.compile(rb"\b" + re.escape(old.encode()) + rb"\b")
    names = git("ls-files", "-z", "--cached", "--others", "--", *scope)
    for name in names.rstrip("\0").split("\0"):
        path = ROOT / name
        if not name.startswith(("src/", "include/", "config/")) or not path.is_file():
            continue
        data = edits[path].encode("utf-8") if path in edits else path.read_bytes()
        if address:
            data = re.sub(
                rb"(?m)^\s*/\* " + re.escape(old.encode()) + rb" \*/\s*$", b"", data
            )
        if pattern.search(data):
            raise SystemExit(
                f"symbol: {old} remains in {name}; include every reference in the rename"
            )


def apply_rename(
    edits: dict[Path, str],
    moves: list[tuple[str, str]],
    old: str,
    scope: list[str],
    address: bool,
) -> None:
    """Publish the index only after every file edit, move and reference check succeeds."""
    index = Path(
        git("rev-parse", "--path-format=absolute", "--git-path", "index").strip()
    )
    lock = index.with_name(index.name + ".lock")
    # Hold Git's real index lock while git mv operates on a private copy.
    lock.open("xb").close()
    published = False
    try:
        with tempfile.TemporaryDirectory(prefix=".symbol-rename-", dir=ROOT) as folder:
            scratch = Path(folder)
            private_index = scratch / "index"
            shutil.copy2(index, private_index)
            env = dict(os.environ, GIT_INDEX_FILE=str(private_index))
            backups = {}
            for number, path in enumerate(edits):
                if (
                    path.is_symlink()
                    or not path.is_file()
                    or not os.access(path, os.W_OK)
                    or not os.access(path.parent, os.W_OK)
                ):
                    raise SystemExit(f"symbol: cannot rewrite {path.relative_to(ROOT)}")
                backup = scratch / str(number)
                shutil.copy2(path, backup)
                backups[path] = backup
            for source, target in moves:
                if not os.access((ROOT / source).parent, os.W_OK):
                    raise SystemExit(f"symbol: cannot move {source}")
                if os.path.lexists(ROOT / target):
                    raise SystemExit(f"symbol: destination already exists: {target}")
                git("mv", "-n", "--", source, target, env=env)
            try:
                for path, contents in edits.items():
                    path.write_text(contents, encoding="utf-8")
                for source, target in moves:
                    git("mv", "--", source, target, env=env)
                check_rename(old, {}, scope, address)
                shutil.copyfile(private_index, lock)
                os.chmod(lock, index.stat().st_mode)
                os.replace(lock, index)
                published = True
            except BaseException:
                for _, target in moves:
                    (ROOT / target).unlink(missing_ok=True)
                for path, backup in backups.items():
                    os.replace(backup, path)
                raise
    finally:
        if not published:
            lock.unlink(missing_ok=True)


def rename(args: argparse.Namespace) -> int:
    """Rename one symbol across the scope and in the symbol table."""
    old, new = args.old, args.new
    if not re.fullmatch(r"[A-Za-z_]\w*", new):
        raise SystemExit(f"symbol: {new} is not an identifier")
    address = ADDRESS_NAME.match(old)
    text = SYMBOLS.read_text(encoding="utf-8")
    images = args.image or ([] if address else tables_with(text, old))
    if not images:
        raise SystemExit(
            f"symbol: give --image for {old}; no table has a row of that name"
        )
    if args.local:
        scope = local_scope(images)
    elif args.scope:
        scope = args.scope
    elif address and any(i not in RESIDENT for i in images):
        raise SystemExit(
            f"symbol: {old} is unique only inside its image. Add --local, or --scope PATH..."
        )
    else:
        scope = list(DEFAULT_SCOPE)
    files = grep_files(old, scope)
    if not files:
        raise SystemExit(f"symbol: {old} does not occur under {' '.join(scope)}")
    clash = grep_files(new, scope)
    if clash:
        raise SystemExit(
            f"symbol: {new} already occurs in {clash[0]}; pick another name"
        )
    if args.dry_run:
        print("\n".join(files))
        return 0
    if address:
        if not args.source:
            raise SystemExit(
                f"symbol: naming {old} needs --source, a description of the symbol"
            )
        addr = int(address[2], 16)
        kind = args.type or ("func" if old.startswith("func_") else None)
        row = symtab.format_row(
            new,
            addr,
            type=kind,
            size=int(args.size, 0) if args.size else None,
            source=args.source,
        )
        for image in images:
            text = symtab.add_row(text, image, new, row, addr)
    else:
        for image in images:
            text = symtab.rename_row(text, image, old, new) or text
    pattern = re.compile(r"\b" + re.escape(old) + r"\b")
    edits = {SYMBOLS: text}
    moves = []
    for name in files:
        path = ROOT / name
        contents = edits.get(path)
        if contents is None:
            contents = path.read_text(encoding="utf-8")
        contents = pattern.sub(new, contents)
        if address and name.startswith(("src/", "include/")):
            contents = with_address_comment(path, old, new, contents)
        edits[path] = contents
        if path.name == f"{old}.c":
            moves.append(
                (name, path.with_name(f"{new}.c").relative_to(ROOT).as_posix())
            )
    check_scope = scope if address else ["src", "include", "config"]
    check_rename(old, edits, check_scope, bool(address))
    apply_rename(edits, moves, old, check_scope, bool(address))
    print(f"renamed {old} -> {new} in {len(files)} files")
    return 0


def params(args: argparse.Namespace) -> int:
    """Rename parameters in one function's unit file and its prototypes."""
    pairs = [p.split("=", 1) for p in args.pairs]
    if any(len(p) != 2 or not p[0] or not p[1] for p in pairs):
        raise SystemExit("symbol: write each rename as OLD=NEW")
    prototype = re.compile(r"\S[^=]*\b" + re.escape(args.func) + r"\s*\(.*\)\s*;")
    for name in grep_files(args.func, ["src", "include"]):
        path = ROOT / name
        lines = path.read_text(encoding="utf-8").split("\n")
        own = path.name == f"{args.func}.c"
        for i, line in enumerate(lines):
            if own or (name.endswith(".h") and prototype.match(line)):
                for a, b in pairs:
                    line = re.sub(r"\b" + re.escape(a) + r"\b", b, line)
                lines[i] = line
        path.write_text("\n".join(lines), encoding="utf-8")
    return 0


def ref_rows(dirs: list[str]) -> list[dict]:
    """Return the address-named units with their reference counts, most used first."""
    units = {}
    for folder in dirs:
        for path in sorted((ROOT / folder).rglob("func_????????.c")):
            units[path.stem] = path.relative_to(ROOT).as_posix()
    counts: collections.Counter[str] = collections.Counter()
    word = re.compile(r"func_[0-9A-F]{8}")
    for folder in ("asm", "src", "include"):
        for path in (ROOT / folder).rglob("*"):
            if path.suffix in (".s", ".c", ".h") and path.is_file():
                counts.update(
                    word.findall(path.read_text(encoding="utf-8", errors="replace"))
                )
    return [
        {"count": counts[name], "name": name, "unit": units[name]}
        for name in sorted(units, key=lambda n: (-counts[n], n))
    ]


def refs(args: argparse.Namespace) -> int:
    """Print the address-named units with their reference counts, most used first."""
    for row in ref_rows(args.dirs or ["src"]):
        if args.jsonl:
            print(json.dumps(row, ensure_ascii=False))
        else:
            print(row["count"], row["name"], row["unit"], sep="\t")
    return 0


def mentioned(names: set[str]) -> set[str]:
    """Return the names that a tracked file under ``src``, ``include``, ``asm`` or ``config`` uses."""
    if not names:
        return set()
    with tempfile.NamedTemporaryFile("w", suffix=".names", encoding="utf-8") as handle:
        handle.write("\n".join(sorted(names)) + "\n")
        handle.flush()
        result = subprocess.run(
            [
                "git",
                "grep",
                "-h",
                "-o",
                "-w",
                "-f",
                handle.name,
                "--",
                "src",
                "include",
                "asm",
                "config",
                ":(exclude)config/symbols.toml",
            ],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
    return set(result.stdout.split())


def check(args: argparse.Namespace) -> int:
    """Report the table's problems; a name at two addresses or an out-of-order table exits 1.

    The other findings are the owner's list: a row repeated in several images (a candidate for a
    group table), an alias no source mentions, and a row with no ``source``.
    """
    try:
        tables = symbols.load(ROOT)
    except symbols.LinkError as error:
        print(f"symbols: {error}")
        return 1
    findings: list[str] = []
    repeated: dict[tuple[str, int, str], list[str]] = collections.defaultdict(list)
    aliases: list[tuple[str, symbols.Entry]] = []
    status = 0
    rows = 0
    for target, entries in tables.items():
        rows += len(entries)
        for before, after in zip(entries, entries[1:], strict=False):
            if before.addr > after.addr:
                findings.append(
                    f"order\t{target}\t{after.name} 0x{after.addr:08X} after "
                    f"{before.name} 0x{before.addr:08X}"
                )
                status = 1
                break
        addresses: dict[str, set[int]] = collections.defaultdict(set)
        names_at: dict[int, list[str]] = collections.defaultdict(list)
        for entry in entries:
            addresses[entry.name].add(entry.addr)
            if entry.alias:
                aliases.append((target, entry))
            else:
                names_at[entry.addr].append(entry.name)
                repeated[(entry.name, entry.addr, entry.type)].append(target)
            if not entry.source:
                findings.append(f"no-source\t{target}\t{entry.name} 0x{entry.addr:08X}")
        for name, found in addresses.items():
            if len(found) > 1:
                status = 1
                findings.append(
                    f"name-two-addresses\t{target}\t{name}\t"
                    + " ".join(f"0x{a:08X}" for a in sorted(found))
                )
        for address, names in names_at.items():
            if len(names) > 1:
                status = 1
                findings.append(
                    f"address-two-names\t{target}\t0x{address:08X}\t" + " ".join(names)
                )
    for (name, address, type_), images in sorted(repeated.items()):
        if len(images) > 1:
            findings.append(
                f"repeat\t{len(images)}\t{name}\t0x{address:08X}\t{type_ or '-'}\t"
                + " ".join(images)
            )
    used = mentioned({entry.name for _, entry in aliases})
    for target, entry in aliases:
        if entry.name not in used:
            findings.append(f"alias-unused\t{target}\t{entry.name} 0x{entry.addr:08X}")
    print("\n".join(findings))
    sys.stderr.write(
        f"symbols: {len(tables)} tables, {rows} rows, {len(findings)} findings; "
        f"{'FAIL' if status else 'ok'}\n"
    )
    return status


# --- Lookup ---------------------------------------------------------------------------------

CLANG = os.environ.get("SYMBOL_CLANG", "clang")
CLANG_FLAGS = [
    CLANG,
    "--target=mipsel-unknown-elf",
    "-fsyntax-only",
    "-Wno-everything",
    "-DM2CTX",
    "-DLANGUAGE_C",
    "-Isrc",
    "-Iinclude",
    "-Iinclude/psyq",
]
LAYOUT_CACHE = ROOT / "build/symbol-layouts.json"
XREF_CACHE = ROOT / "build/symbol-xrefs"
LAYOUT_VERSION = 2
SCALAR_WIDTH = {
    "char": 1,
    "short": 2,
    "int": 4,
    "long": 4,
    "s8": 1,
    "s16": 2,
    "s32": 4,
    "u8": 1,
    "u16": 2,
    "u32": 4,
    "u_char": 1,
    "u_short": 2,
    "u_long": 4,
    "unsigned char": 1,
    "unsigned short": 2,
    "unsigned int": 4,
}
LAYOUT_MEMBER = re.compile(r"^\s*(\d+)(?::\d+-\d+)? \|( +)(.+) (\w+)$")
LAYOUT_SIZE = re.compile(r"\[sizeof=(\d+),")
PROBE_HEAD = re.compile(r"^\s*0 \| struct __probe$")
ARRAY = re.compile(r"^(?P<base>.+?)\s*\[(?P<count>[^\]]*)\](?P<rest>.*)$")
GLABEL = re.compile(r"^\s*glabel\s+(\w+)\s*$")


@dataclass(frozen=True)
class Member:
    """One member of a record, at its absolute offset from the record start."""

    offset: int
    path: str
    ctype: str
    size: int


@dataclass(frozen=True)
class Layout:
    """A C type's size and members; ``record`` is false for a scalar or pointer."""

    size: int
    members: tuple[Member, ...]
    record: bool


@dataclass(frozen=True)
class Row:
    """One non-alias row of config/symbols.toml."""

    name: str
    addr: int
    type: str
    size: int | None
    table: str


def parse_probe(text: str) -> Layout | None:
    """Read the layout from the ``struct __probe`` block of a clang record dump."""
    for block in text.split("*** Dumping AST Record Layout")[1:]:
        lines = block.strip("\n").split("\n")
        if not lines or not PROBE_HEAD.match(lines[0]):
            continue
        members: list[Member] = []
        stack: list[tuple[int, str]] = []
        size = None
        for line in lines[1:]:
            found = LAYOUT_SIZE.search(line)
            if found:
                size = int(found.group(1))
                break
            match = LAYOUT_MEMBER.match(line)
            if not match:
                continue
            offset, indent, ctype, name = match.groups()
            depth = len(indent) // 2
            stack = stack[: depth - 1]
            path = ".".join([part for _, part in stack] + [name])
            stack.append((depth, name))
            members.append(Member(int(offset), path, ctype.strip(), 0))
        if size is None:
            continue
        inner = []
        for member in members:
            if member.path == "x":
                continue
            if member.path.startswith("x."):
                member = Member(member.offset, member.path[2:], member.ctype, 0)
            inner.append(member)
        for index, member in enumerate(inner):
            depth = member.path.count(".")
            end = size
            for later in inner[index + 1 :]:
                if later.path.count(".") <= depth and later.offset > member.offset:
                    end = later.offset
                    break
            length = end - member.offset
            width = _known_width(member.ctype)
            if width is not None:
                length = min(length, width)
            inner[index] = Member(member.offset, member.path, member.ctype, length)
        return Layout(size, tuple(inner), bool(inner))
    return None


def _type_headers(name: str) -> list[str]:
    """Return the headers that define a C type, in path order."""
    base = name
    for prefix in ("struct ", "union ", "enum "):
        if base.startswith(prefix):
            base = base[len(prefix) :]
            break
    pattern = re.escape(base)
    end = re.compile(r"(?m)^\s*\}\s*" + pattern + r"\s*(?:\[[^\]]*\])?\s*;")
    simple = re.compile(r"(?m)^\s*typedef\b[^;{}]*\b" + pattern + r"\b[^;{}]*;")
    definition = re.compile(r"\b(?:struct|union|enum)\s+" + pattern + r"\s*\{")
    headers = []
    for path in grep_files(base, ["include", "src"]):
        if not path.endswith(".h"):
            continue
        try:
            text = (ROOT / path).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if end.search(text) or simple.search(text) or definition.search(text):
            headers.append(path)
    return headers


def _dependencies(dep: Path, source: Path) -> list[list[str | int]]:
    """Return the header stamp clang read: path, mtime and size of every dependency."""
    text = dep.read_text(encoding="utf-8", errors="replace").replace("\\\n", " ")
    _, _, rest = text.partition(":")
    deps: list[list[str | int]] = []
    for token in rest.split():
        path = Path(token)
        if path.resolve() == source.resolve():
            continue
        full = path if path.is_absolute() else ROOT / path
        try:
            info = full.stat()
        except OSError:
            continue
        deps.append([str(path), info.st_mtime_ns, info.st_size])
    return deps


def _probe(name: str) -> tuple[Layout, list[list[str | int]], str] | None:
    """Ask clang for ``name``'s layout through a probe record that holds one."""
    for header in _type_headers(name):
        root, _, relative = header.partition("/")
        include = relative if root in ("include", "src") else header
        with tempfile.TemporaryDirectory(prefix="symbol-probe-") as folder:
            source = Path(folder) / "probe.c"
            source.write_text(
                '#include "common.h"\n'
                f'#include "{include}"\n'
                f"struct __probe {{ {name} x; }};\n",
                encoding="utf-8",
            )
            dep = Path(folder) / "probe.d"
            result = subprocess.run(
                [
                    *CLANG_FLAGS,
                    "-x",
                    "c",
                    str(source),
                    "-MD",
                    "-MF",
                    str(dep),
                    "-Xclang",
                    "-fdump-record-layouts-complete",
                ],
                cwd=ROOT,
                capture_output=True,
                text=True,
                check=False,
            )
            if result.returncode:
                continue
            layout = parse_probe(result.stdout)
            if layout is None:
                continue
            return layout, _dependencies(dep, source), header
    return None


_LAYOUTS: dict[str, Layout | None] = {}
_LAYOUT_INDEX: dict[str, dict] | None = None


def _layout_index() -> dict[str, dict]:
    global _LAYOUT_INDEX
    if _LAYOUT_INDEX is None:
        try:
            _LAYOUT_INDEX = json.loads(LAYOUT_CACHE.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            _LAYOUT_INDEX = {}
    return _LAYOUT_INDEX


def _cache_current(entry: dict) -> bool:
    if entry.get("version") != LAYOUT_VERSION:
        return False
    for name, mtime, size in entry.get("deps", []):
        path = Path(name)
        full = path if path.is_absolute() else ROOT / path
        try:
            info = full.stat()
        except OSError:
            return False
        if info.st_mtime_ns != mtime or info.st_size != size:
            return False
    return True


def _store_layout(
    name: str, layout: Layout, deps: list[list[str | int]], header: str
) -> None:
    index = _layout_index()
    index[name] = {
        "version": LAYOUT_VERSION,
        "header": header,
        "deps": deps,
        "size": layout.size,
        "members": [[m.offset, m.path, m.ctype, m.size] for m in layout.members],
    }
    try:
        LAYOUT_CACHE.parent.mkdir(parents=True, exist_ok=True)
        handle, tmp = tempfile.mkstemp(
            dir=LAYOUT_CACHE.parent, prefix="symbol-layouts-"
        )
        with os.fdopen(handle, "w", encoding="utf-8") as stream:
            json.dump(index, stream, sort_keys=True)
        os.replace(tmp, LAYOUT_CACHE)
    except OSError:
        pass


def type_layout(name: str) -> Layout | None:
    """Return a C type's record layout from clang, cached by the headers it reads."""
    key = " ".join(name.split())
    if key in _LAYOUTS:
        return _LAYOUTS[key]
    if "*" in key or key in ("func", "void"):
        _LAYOUTS[key] = None
        return None
    entry = _layout_index().get(key)
    layout = None
    if entry and _cache_current(entry):
        layout = Layout(
            entry["size"],
            tuple(Member(*member) for member in entry["members"]),
            bool(entry["members"]),
        )
    else:
        try:
            probed = _probe(key)
        except OSError:
            probed = None
        if probed:
            layout, deps, header = probed
            _store_layout(key, layout, deps, header)
    _LAYOUTS[key] = layout
    return layout


def type_size(name: str) -> int | None:
    """Return the size of a C type in bytes, from a scalar table or the record layout."""
    key = " ".join(name.split())
    if "*" in key:
        return 4
    if key in SCALAR_WIDTH:
        return SCALAR_WIDTH[key]
    layout = type_layout(key)
    return layout.size if layout else None


def split_array(ctype: str) -> tuple[str, list[int | None]] | None:
    """Return the element type and dimensions of an array type, else None."""
    match = ARRAY.match(ctype.strip())
    if not match:
        return None
    dims: list[int | None] = [
        int(match.group("count"), 0) if match.group("count") else None
    ]
    rest = match.group("rest")
    while True:
        found = re.match(r"\s*\[([^\]]*)\]", rest)
        if not found:
            break
        dims.append(int(found.group(1), 0) if found.group(1) else None)
        rest = rest[found.end() :]
    return match.group("base").strip(), dims


def _known_width(ctype: str) -> int | None:
    """Return a scalar, pointer or array-of-scalars width, else None for a record."""
    text = ctype.strip()
    if "*" in text:
        return 4
    array = split_array(text)
    if array is not None:
        base, dims = array
        width = _known_width(base)
        if width is None or any(dim is None for dim in dims):
            return None
        for dim in dims:
            width *= dim
        return width
    return SCALAR_WIDTH.get(text)


def locate(layout: Layout, offset: int, prefix: str = "") -> list[tuple[str, int, str]]:
    """Return the deepest named members at ``offset``: path, start and type."""
    hits = [
        member
        for member in layout.members
        if member.offset <= offset < member.offset + member.size
    ]
    if not hits:
        return []
    depth = max(member.path.count(".") for member in hits)
    found: list[tuple[str, int, str]] = []
    for member in hits:
        if member.path.count(".") < depth:
            continue
        array = split_array(member.ctype)
        if array is None:
            found.append((prefix + member.path, member.offset, member.ctype))
            continue
        base, dims = array
        element = type_size(base)
        if not element:
            found.append((prefix + member.path, member.offset, member.ctype))
            continue
        strides = [0] * len(dims)
        stride = element
        for index in range(len(dims) - 1, -1, -1):
            strides[index] = stride
            if dims[index]:
                stride *= dims[index]
        remaining = offset - member.offset
        indexes = ""
        for index in range(len(dims)):
            indexes += f"[{remaining // strides[index]}]"
            remaining %= strides[index]
        start = member.offset + (offset - member.offset - remaining)
        inner = type_layout(base)
        if inner is not None and inner.members:
            deeper = locate(inner, remaining)
            if deeper:
                found.extend(
                    (prefix + member.path + indexes + "." + path, start + at, ctype)
                    for path, at, ctype in deeper
                )
                continue
        found.append((prefix + member.path + indexes, start, base))
    return found


def symbol_tables() -> dict[str, dict[str, dict]]:
    """Load config/symbols.toml as image table -> name -> row."""
    return tomllib.loads(SYMBOLS.read_text(encoding="utf-8"))


def table_rows(data: dict[str, dict[str, dict]], table: str) -> list[Row]:
    """Return one table's non-alias rows."""
    rows = []
    for name, row in data.get(table, {}).items():
        if not isinstance(row, dict) or "addr" not in row or row.get("alias"):
            continue
        size = row.get("size")
        rows.append(
            Row(
                name,
                int(row["addr"]),
                str(row.get("type", "")),
                int(size) if size is not None else None,
                table,
            )
        )
    return rows


def next_addresses(rows: list[Row]) -> dict[int, int]:
    """Return each row address's next distinct address in the same table."""
    ordered = sorted({row.addr for row in rows})
    return {addr: ordered[index + 1] for index, addr in enumerate(ordered[:-1])}


_SPLAT_SPANS: dict[str, dict[int, int]] = {}


def splat_spans(table: str) -> dict[int, int]:
    """Return the size of each subsegment the target's layout starts."""
    if table in _SPLAT_SPANS:
        return _SPLAT_SPANS[table]
    spans: dict[int, int] = {}
    path = ROOT / "config" / table / "splat.yaml"
    if path.is_file():
        try:
            from bof3.resolve.layout import parse_splat_layout, splat_facts

            facts = splat_facts(path)
            layout = parse_splat_layout(path, facts.load_address)
            for boundary in layout.boundaries:
                if boundary.virtual_end is not None:
                    spans[boundary.virtual_start] = (
                        boundary.virtual_end - boundary.virtual_start
                    )
        except (OSError, ValueError, ImportError):
            pass
    _SPLAT_SPANS[table] = spans
    return spans


_RANGES: dict[str, tuple[int, int] | None] = {}


def table_range(table: str) -> tuple[int, int] | None:
    """Return the address range a target's payload occupies, when its layout is known."""
    if table in _RANGES:
        return _RANGES[table]
    result = None
    path = ROOT / "config" / table / "splat.yaml"
    if path.is_file():
        try:
            from bof3.resolve.layout import parse_splat_layout, splat_facts

            layout = parse_splat_layout(path, splat_facts(path).load_address)
            ends = [
                boundary.virtual_end
                for boundary in layout.boundaries
                if boundary.virtual_end is not None
            ]
            if layout.boundaries and ends:
                result = (layout.boundaries[0].virtual_start, max(ends))
        except (OSError, ValueError, ImportError):
            pass
    _RANGES[table] = result
    return result


def foreign_visible(table: str, image: str | None, addr: int) -> bool:
    """Whether a table other than the image's own may own ``addr``."""
    if image is None or table == image:
        return True
    span = table_range(table)
    return span is None or span[0] <= addr < span[1]


def row_span(row: Row, following: dict[int, int]) -> int:
    """Return a row's extent: its size, its layout subsegment, its type, or a guess.

    A row outside its table's payload (a resident symbol copied into an overlay table) has no
    meaningful next row there, so it keeps the 0x100-byte guess the former lookup used.
    """
    if row.size is not None:
        return row.size
    span = splat_spans(row.table).get(row.addr)
    if span is not None:
        return span
    inside = True
    bounds = table_range(row.table)
    if bounds is not None:
        inside = bounds[0] <= row.addr < bounds[1]
    later = following.get(row.addr)
    gap = (
        later - row.addr if inside and later is not None and later > row.addr else None
    )
    if row.type == "func":
        return gap if gap is not None else 0x100
    layout = type_layout(row.type) if row.type else None
    if layout is not None and layout.size:
        return max(layout.size, min(gap or 0x100, 0x100))
    return min(gap, 0x100) if gap is not None else 0x100


def owner(row: Row, addr: int) -> tuple[str, int, str]:
    """Return the deepest member path at ``addr``, its start and type."""
    offset = addr - row.addr
    if offset == 0:
        return row.name, 0, row.type or "untyped"
    layout = type_layout(row.type) if row.type and row.type != "func" else None
    if layout is None or not layout.members:
        return row.name, 0, row.type or "untyped"
    prefix = ""
    element = 0
    if (
        row.size
        and layout.size
        and row.size >= layout.size
        and row.size % layout.size == 0
    ):
        count = row.size // layout.size
        if count > 1:
            index = offset // layout.size
            element = index * layout.size
            offset -= element
            prefix = f"[{index}]"
    if offset == 0 or offset >= layout.size:
        return row.name + prefix, element, row.type or "untyped"
    found = locate(layout, offset)
    if not found:
        return row.name + prefix, element, row.type or "untyped"
    path, start, ctype = found[0]
    return f"{row.name}{prefix}.{path}", element + start, ctype


def _address(text: str) -> int:
    """Parse a symbol address, accepting ``D_`` and ``func_`` names."""
    token = text.strip()
    if token.startswith("D_"):
        token = token[2:]
    elif token.startswith("func_"):
        token = token[5:]
    if token.lower().startswith("0x"):
        token = token[2:]
    try:
        return int(token, 16)
    except ValueError:
        raise SystemExit(f"symbol: {text} is not an address") from None


def _diff_addresses(base: str, image: str | None) -> list[int]:
    """Return the D_ addresses the branch adds, under the image's sources when given."""
    scope = ["src", "include"]
    if image:
        try:
            folder = source_folder(image)
        except (IndexError, ValueError):
            raise SystemExit(f"symbol: {image} is not a target") from None
        scope = [f"src/{folder}", "include"]
    diff = git("diff", f"{base}...HEAD", "--", *scope)
    found = set()
    for line in diff.splitlines():
        if line.startswith("+"):
            found.update(
                int(match, 16) for match in re.findall(r"\bD_([0-9A-F]{8})\b", line)
            )
    return sorted(found)


def _visible_tables(data: dict[str, dict[str, dict]], image: str | None) -> list[str]:
    """Return the image's own table and the resident ones, or every table."""
    if image is None:
        return list(data)
    tables = [image, *RESIDENT]
    seen = []
    for table in tables:
        if table in data and table not in seen:
            seen.append(table)
    return seen


def find_hits(
    rows: dict[str, list[Row]],
    following: dict[str, dict[int, int]],
    image: str | None,
    addr: int,
) -> list[tuple[Row, int]]:
    """Return the rows that own an address, nearest first."""
    hits = []
    for table, table_rows_ in rows.items():
        if not foreign_visible(table, image, addr):
            continue
        for row in table_rows_:
            span = row_span(row, following[table])
            if addr == row.addr or row.addr < addr < row.addr + span:
                hits.append((row, span))
    hits.sort(key=lambda item: (item[0].addr, item[0].name), reverse=True)
    return hits


def at(args: argparse.Namespace) -> int:
    """Print the owner of each address, or the D_ addresses the branch adds."""
    if args.diff is not None:
        if args.addresses:
            raise SystemExit("symbol: at takes addresses or --diff, not both")
        addresses = _diff_addresses(args.diff, args.image)
        if not addresses:
            print(f"no added D_ address in {args.diff}...HEAD")
            return 0
    elif not args.image or not args.addresses:
        raise SystemExit("symbol: at needs IMAGE 0xADDR..., or --diff [BASE]")
    else:
        addresses = [_address(text) for text in args.addresses]
    data = symbol_tables()
    tables = _visible_tables(data, args.image)
    rows = {table: table_rows(data, table) for table in tables}
    following = {table: next_addresses(rows[table]) for table in tables}
    for addr in addresses:
        hits = find_hits(rows, following, args.image, addr)
        if not hits:
            print(f"{addr:#010x}  no named owner")
            continue
        printed = 0
        for row, span in hits:
            path, start, _ = owner(row, addr)
            delta = addr - (row.addr + start)
            size = (
                "(size unknown: check the record's members)"
                if row.size is None and not row.type
                else f"({row.type or 'untyped'}, {span:#x})"
            )
            print(f"{addr:#010x}  {path}+{delta:#x}  {size}  [{row.table}]")
            printed += 1
            if printed == 3:
                break
    return 0


def member(args: argparse.Namespace) -> int:
    """Print the member path and type at one byte offset of a record."""
    name = " ".join(args.type.split())
    layout = type_layout(name)
    if layout is None or not layout.members:
        raise SystemExit(f"symbol: {name} has no named members")
    offset = _address(args.offset)
    if offset < 0 or offset >= layout.size:
        raise SystemExit(
            f"symbol: {name} is {layout.size:#x} bytes; {args.offset} is outside"
        )
    found = locate(layout, offset)
    if not found:
        raise SystemExit(f"symbol: no named member at {name}+{offset:#x}")
    for path, _, ctype in found:
        print(f"{path}\t{ctype}")
    return 0


def _c_references(name: str) -> list[tuple[str, int]]:
    """Return the file and line of each C use outside comments and strings."""
    out = []
    word = re.compile(r"\b" + re.escape(name) + r"\b")
    for path in grep_files(name, ["src", "include"]):
        text = (ROOT / path).read_text(encoding="utf-8", errors="replace")
        masked = ctext.mask(text)
        for number, (_, code) in enumerate(
            zip(text.split("\n"), masked.split("\n"), strict=True), 1
        ):
            if word.search(code):
                out.append((path, number))
    return out


def _asm_references(name: str) -> list[tuple[str, int, str, str]]:
    """Return the file, line, open function and instruction of each assembly use."""
    out = []
    word = re.compile(r"\b" + re.escape(name) + r"\b")
    for path in grep_files(name, ["asm"]):
        if not path.endswith(".s"):
            continue
        function = Path(path).stem
        lines = (ROOT / path).read_text(encoding="utf-8", errors="replace").split("\n")
        for number, line in enumerate(lines, 1):
            label = GLABEL.match(line)
            if label:
                function = label.group(1)
                continue
            stripped = line.lstrip()
            if stripped.startswith(("nonmatching ", "endlabel ", ".")):
                continue
            code = line.split("*/", 1)[1] if "*/" in line else line
            if word.search(code):
                out.append((path, number, function, " ".join(code.split())))
    return out


def _xref_path(image: str) -> Path:
    return XREF_CACHE / (image.replace("/", "+") + ".json")


def _read_xrefs(image: str) -> dict | None:
    """Return one image's cached cross-references, when its project stamp still matches."""
    try:
        return json.loads(_xref_path(image).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None


def _write_xrefs(image: str, data: dict) -> None:
    try:
        XREF_CACHE.mkdir(parents=True, exist_ok=True)
        handle, tmp = tempfile.mkstemp(dir=XREF_CACHE, prefix="xrefs-")
        with os.fdopen(handle, "w", encoding="utf-8") as stream:
            json.dump(data, stream, sort_keys=True)
        os.replace(tmp, _xref_path(image))
    except OSError:
        pass


def _rizin_xrefs(queries: list[tuple[str, int]]) -> list[tuple[str, int, str]]:
    """Return each image's Rizin cross-references to the queried addresses.

    The first query in an image analyses it, saves the analysis in the project and caches
    every cross-reference in build/symbol-xrefs; a later address only reads that cache.
    """
    by_image: dict[str, set[int]] = collections.defaultdict(set)
    for image, addr in queries:
        by_image[image].add(addr)
    maps: dict[str, dict] = {}
    for image in sorted(by_image):
        project = ROOT / f"build/meson/rz+{image.replace('/', '+')}.rzdb"
        if not project.is_file():
            print(
                f"symbol: no Rizin project for {image}; run meson compile "
                f"-C build/meson rz+{image.replace('/', '+')}.rzdb",
                file=sys.stderr,
            )
            continue
        info = project.stat()
        stamp = [info.st_mtime_ns, info.st_size]
        stale = any(
            path.is_file() and path.stat().st_mtime_ns > info.st_mtime_ns
            for path in (project.with_suffix(".image"), project.with_suffix(".rz"))
        )
        data = _read_xrefs(image)
        if data is None or data.get("stamp") != stamp or stale:
            result = subprocess.run(
                [str(ROOT / "bin/rz"), image, "aaa", "axlj", f"Ps {project}"],
                cwd=ROOT,
                capture_output=True,
                text=True,
                check=False,
            )
            xrefs = None
            for line in result.stdout.splitlines():
                if line.startswith("[") and line.endswith("]"):
                    try:
                        xrefs = json.loads(line)
                    except ValueError:
                        xrefs = None
            if not isinstance(xrefs, list):
                print(
                    f"symbol: the Rizin xref query failed for {image}",
                    file=sys.stderr,
                )
                continue
            saved = project.stat()
            data = {
                "stamp": [saved.st_mtime_ns, saved.st_size],
                "xrefs": [
                    [
                        int(xref.get("from", 0)),
                        int(xref.get("to", 0)),
                        str(xref.get("type", "")),
                    ]
                    for xref in xrefs
                    if isinstance(xref, dict)
                ],
            }
            _write_xrefs(image, data)
        maps[image] = data
    out = []
    for image, addresses in sorted(by_image.items()):
        data = maps.get(image)
        if data is None:
            continue
        for addr in sorted(addresses):
            out.extend(
                (image, source, kind)
                for source, target, kind in data["xrefs"]
                if target == addr
            )
    return out


def uses(args: argparse.Namespace) -> int:
    """Print every C, assembly and Rizin reference to a symbol or address."""
    data = symbol_tables()
    name = None
    queries: list[tuple[str, int]] = []
    spec = args.symbol
    if "@" in spec:
        image, _, address = spec.rpartition("@")
        if not image or "/" not in image:
            raise SystemExit("symbol: uses takes NAME or IMAGE@0xADDR")
        addr = _address(address)
        rows = {
            table: table_rows(data, table) for table in _visible_tables(data, image)
        }
        following = {table: next_addresses(rows[table]) for table in rows}
        hits = find_hits(rows, following, image, addr)
        if hits:
            row, span = hits[0]
            name = row.name
            path, start, _ = owner(row, addr)
            delta = addr - (row.addr + start)
            size = (
                "(size unknown: check the record's members)"
                if row.size is None and not row.type
                else f"({row.type or 'untyped'}, {span:#x})"
            )
            print(f"{image}@0x{addr:08X}  {path}+{delta:#x}  {size}  [{row.table}]")
        else:
            print(f"{image}@0x{addr:08X}  no named owner")
        queries.append((image, addr))
    else:
        name = spec
        for table, rows in data.items():
            row = rows.get(name)
            if isinstance(row, dict) and "addr" in row and not row.get("alias"):
                queries.append((table, int(row["addr"])))
    if name is not None:
        for path, number in _c_references(name):
            print(f"c\t{path}:{number}")
        for path, number, function, instruction in _asm_references(name):
            print(f"asm\t{path}:{number}\t{function}\t{instruction}")
    for image, source, kind in _rizin_xrefs(queries):
        print(f"rizin\t{image}\t0x{source:08X}\t{kind}")
    return 0


def main(argv: list[str] | None = None) -> int:
    """Run one verb."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    verbs = parser.add_subparsers(dest="verb", required=True)
    one = verbs.add_parser("add", help="add a symbols.toml row")
    one.add_argument("image")
    one.add_argument("name")
    one.add_argument("addr")
    one.add_argument("--source", help="a description of the symbol")
    one.add_argument("--type")
    one.add_argument("--size")
    one.add_argument("--alias", action="store_true")
    one.set_defaults(run=add)
    two = verbs.add_parser("rename", help="rename a function or global")
    two.add_argument("old")
    two.add_argument("new")
    two.add_argument(
        "--image",
        action="append",
        help="a symbols.toml table, such as emi/battle/battle/03; repeat it per image "
        "(default for a named symbol: every table that has it)",
    )
    two.add_argument(
        "--local",
        action="store_true",
        help="only this image's src/ and config/ folders",
    )
    two.add_argument("--scope", nargs="+", help="only these paths")
    two.add_argument("--source", help="a description (required for an address name)")
    two.add_argument("--type")
    two.add_argument("--size")
    two.add_argument(
        "--dry-run", action="store_true", help="list the files; change nothing"
    )
    two.set_defaults(run=rename)
    three = verbs.add_parser("params", help="rename parameters of one function")
    three.add_argument("func")
    three.add_argument("pairs", nargs="+", metavar="OLD=NEW")
    three.set_defaults(run=params)
    four = verbs.add_parser("refs", help="rank address-named units by references")
    four.add_argument("dirs", nargs="*")
    four.add_argument("--jsonl", action="store_true", help="one JSON object per line")
    four.set_defaults(run=refs)
    check_parser = verbs.add_parser("check", help="report symbol-table problems")
    check_parser.set_defaults(run=check)
    five = verbs.add_parser(
        "at",
        help="show the symbol and member at an address",
        epilog="Example: tools/symbol.py at exe/slus_004_22 0x8014630C",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    five.add_argument("image", nargs="?", help="a symbols.toml table")
    five.add_argument("addresses", nargs="*", metavar="0xADDR")
    five.add_argument(
        "--diff",
        nargs="?",
        const="public/main",
        metavar="BASE",
        help="read the D_ addresses the branch adds (default base: public/main)",
    )
    five.set_defaults(run=at)
    six = verbs.add_parser(
        "member",
        help="show the member at a byte offset of a record",
        epilog="Example: tools/symbol.py member Actor 0xB",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    six.add_argument("type", help="a C record type")
    six.add_argument("offset", help="a byte offset, such as 0x44")
    six.set_defaults(run=member)
    seven = verbs.add_parser(
        "uses",
        help="list every reference to a symbol",
        epilog=(
            "Examples: tools/symbol.py uses g_Battle\n"
            "          tools/symbol.py uses exe/slus_004_22@0x8014630C"
        ),
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    seven.add_argument("symbol", help="a name, or IMAGE@0xADDR")
    seven.set_defaults(run=uses)
    args = parser.parse_args(argv)
    if args.verb == "add" and not args.source and not args.alias:
        parser.error("add needs --source (a description) or --alias")
    try:
        return args.run(args)
    except (symtab.SymtabError, OSError) as error:
        raise SystemExit(f"symbol: {error}") from None
    except subprocess.CalledProcessError as error:
        raise SystemExit(
            f"symbol: {error.stderr.strip() if error.stderr else error}"
        ) from None


if __name__ == "__main__":
    raise SystemExit(main())
