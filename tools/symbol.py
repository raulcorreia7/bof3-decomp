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
    tools/symbol.py value 0xNN [--image IMAGE] [--type ENUM_OR_PREFIX]
    tools/symbol.py layers [--jsonl]
    tools/symbol.py accesses NAME [--jsonl]
    tools/symbol.py records [--jsonl]
    tools/symbol.py values --scan [--jsonl]
    tools/symbol.py signatures [FUNC|--all] [--jsonl]
    tools/symbol.py extents [IMAGE] [--jsonl]
    tools/symbol.py homes [--jsonl]

`add` writes one row of config/symbols.toml in address order. The image is a folder under
`config/` that holds a `splat.yaml`; any other id is refused.

`rename` changes a function or global in every tracked file of the scope: the definition, each
prototype and use, `config/` references, and the unit file `OLD.c` (`git mv`). It writes the
row of config/symbols.toml: a new row for an address name (`--source` describes the symbol), or the
renamed key of an existing row. Naming an address replaces the row already keyed with its address
name, so no key repeats. An address name (`func_<ADDR>`, `D_<ADDR>`) stays in a comment
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

`value` lists every enum member and numeric `#define` with one value among the headers the image
sees, nearest scope first: its own headers, the group's, then `include/`. Each row is the name, the
header and line, and the enum or prefix family; `--type` keeps one enum or one name prefix. Without
`--image` it reads every tracked header. The value is written in hexadecimal, like the other verbs.

`layers` builds the game call graph over every image: split assembly `jal` targets, matched C calls,
and the entries of every function table an indirect call or `jalr` uses. A function's layer is 0 when
it calls nothing in the game (SDK and libc calls do not count), else 1 + the deepest callee; a cycle
shares one layer. Each row carries the image, name, address, layer, caller count, callees, status
(`MATCH`, `INCLUDE_ASM`, `NON_MATCHING`), whether the name is real, how many images hold a byte-equal
body, and whether the body is already one shared header. `--jsonl` writes one object per line.

`accesses` lists every load and store that reaches a record type or a global, decoded from the
built function index: direct globals, globals that point at the type, and the image's `g_Task` view
are followed. Each row gives the byte offset, the widths seen, reads and writes, the member the
current definition has there, up to five examples, the constants it is compared with or assigned,
the callee argument slots it is passed to, and a problem (`unknown member`, `width differs`,
`signedness differs`, `straddles members`, `past the end`, `never accessed`). A coverage line on
stderr says how many base-register memory operations the trace followed.

`records` summarises every struct, union and typedef in `include/` and `src/**/*.h`: the compiler
size, member count, `unk_`/`pad_` count, how many times the name is defined, how many other names
share its layout, the globals and parameters of the type, and its direct access count. Rows are
ordered by accesses times unknown members, so the records that need work first come first.

`values --scan` reads every `MATCH` body in `src/` and decides what each numeric literal means from
the declaration around it: the member, global, parameter or call slot the literal is assigned to or
compared with, its comment and its type. A literal whose declaration names a family (an enum tag in
a member comment, an enum-typed parameter, a `<thing>_id` name) gets that family and the one member
of it with the value; a member name that states the role (`timer`, `index`, `x`, `color`) gets the
form the conventions prescribe. `--jsonl` writes one object per site with the file, line, literal,
role, family, existing constant, rewritten form and confidence (`typed` when the declaration proves
the role). A form rewrite keeps the value and its suffix, so it never changes the bytes.

`signatures` reads every split function under `asm/` and interprets its register dataflow as a
GCC 2.7.2 MIPS o32 signature: the argument registers read before written (the highest plus one),
the stack arguments, the kind of each argument and the value or void the function returns. An
argument is a pointer when the callee uses it as a base, when the callee forwards it to a declared
pointer parameter, or when every caller passes an address or a pointer returned by a call; a stack
argument read from the frame and used as a base is a pointer too. The returned value is the nearest
write of `v0` that no later instruction consumes: a write whose value a store, a branch or an
argument move reads is scratch, and a delay-slot write counts when its branch targets the epilogue
or the write only moves or loads a value. A value written in a loop's delay slot can be scratch on
the fall-through path; that row is `likely` at most. Every call site is cross-checked: the argument
registers a caller sets and how it uses the returned v0. Each row gives the declared prototype,
the found signature, `callee_args`, the callers' minimum and maximum, `disagree`, the evidence and a
confidence. `proven` needs every direct caller to set the callee's argument count, no stack argument,
and every pointer or narrowing claim proved on both sides: a pointer only the callers pass, a
pointer the declaration types as a word, and a narrowing one side does not perform are `likely` at
most. A function reached through a table counts the table's row as a caller. `--jsonl` writes one
object per line.

`extents` gives every data and bss symbol of a target: the gap to the next symbol, the size its
declaration states, the access offsets beyond that size, the index stride the code uses on it, and
the neighbours only reached as `base + constant` from it (members of one record, not globals). It
also names the section the symbol sits in. `--jsonl` writes one object per line.

`homes` reads the call and data graph. A function's found home differs from its declared one only
by rule a (80% of at least three callers are in that system), rule b (it is the only writer of a
global whose other readers are all in that system) or rule c (it sits in address order between two
functions of that system and no caller is from its declared system); two rules are `proven`, one is
`likely`. A function of an `emi` image whose declared system lives in that image moves only by rule
c. A global's owner is the one system all its writers are in, and a global written from two systems
gets no row. File rows cover `src/**/*.c` units only, with the address runs that continue another
file of the same system or that another system's units interrupt. `--jsonl` writes one object per
line.

Run `meson compile -C build/meson check-<image>` for every touched image afterwards.
"""

from __future__ import annotations

import argparse
import ast
import bisect
import collections
import hashlib
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
from bof3.source import asmtext, ctext, symtab

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
    if not (ROOT / "config" / args.image / "splat.yaml").is_file():
        print(
            f"symbol: no image {args.image}; "
            "use a folder id under config/ that holds a splat.yaml",
            file=sys.stderr,
        )
        return 2
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
            # A row already keyed with the address name would be rewritten by the source
            # substitution below and repeat the new key.
            text = symtab.remove_row(text, image, old) or text
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


# --- Value lookup ---------------------------------------------------------------------------

VALUE_INCLUDE = re.compile(r'^\s*#\s*include\s*([<"])([^>"]+)[>"]', re.M)
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
VALUE_DEFINE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+(\w+)(\([^)]*\))?(.*)$")
ENUM_HEAD = re.compile(r"\benum\s*(\w+)?\s*\{")
C_SUFFIX = re.compile(r"\b(0[xX][0-9A-Fa-f]+|\d+)[uUlL]+\b")
C_OCTAL = re.compile(r"\b0([0-7]+)\b")
C_TOKEN = re.compile(r"(0[xX][0-9A-Fa-f]+|\d+)|([A-Za-z_]\w*)")
C_CAST = re.compile(r"\((?:u|s)(?:8|16|32)\)")
C_CHAR = re.compile(r"'(?:\\.|[^\\'])'")
IDENT = re.compile(r"[A-Za-z_]\w*")


@dataclass(frozen=True)
class NamedValue:
    """One enum member or macro with a numeric value."""

    name: str
    value: int
    header: str
    line: int
    family: str


def _without_comments(text: str) -> str:
    """Blank comments but keep strings, so an include path and a char literal survive."""
    return COMMENT.sub(lambda match: re.sub(r"[^\n]", " ", match.group()), text)


def _resolve_include(
    source: str, name: str, angle: bool, tracked: set[str]
) -> str | None:
    """Return the tracked header an include names, or None when it is a system header."""
    parent = str(Path(source).parent)
    bases = (
        (ROOT / "include", ROOT / "include/psyq")
        if angle
        else (ROOT / parent, ROOT / "src", ROOT / "include")
    )
    for base in bases:
        try:
            relative = (base / name).resolve().relative_to(ROOT).as_posix()
        except (OSError, ValueError):
            continue
        if relative in tracked:
            return relative
    return None


def _value_headers(image: str | None) -> list[str]:
    """Return the headers the image's sources include, or every tracked header."""
    names = ctext.tracked(ROOT, "src", "include")
    tracked = set(names)
    if image is None:
        return sorted(name for name in names if name.endswith(".h"))
    try:
        folder = f"src/{source_folder(image)}"
    except (IndexError, ValueError):
        raise SystemExit(f"symbol: {image} is not a target") from None
    queue = [
        name
        for name in names
        if name.startswith(folder + "/") and name.endswith((".c", ".h"))
    ]
    seen: set[str] = set()
    while queue:
        source = queue.pop()
        if source in seen:
            continue
        seen.add(source)
        try:
            text = (ROOT / source).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for delimiter, name in VALUE_INCLUDE.findall(_without_comments(text)):
            resolved = _resolve_include(source, name, delimiter == "<", tracked)
            if resolved is not None and resolved not in seen:
                queue.append(resolved)
    return sorted(name for name in seen if name.endswith(".h"))


def _match_brace(text: str, opening: int) -> int:
    """Return the index of the brace that closes the one at ``opening``."""
    depth = 0
    for index in range(opening, len(text)):
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return index
    return -1


def _split_commas(body: str):
    """Yield ``(start, part)`` for each top-level comma-separated part of an enum body."""
    start = 0
    depth = 0
    for index, char in enumerate(body):
        if char in "([{":
            depth += 1
        elif char in ")]}":
            depth -= 1
        elif char == "," and depth == 0:
            yield start, body[start:index]
            start = index + 1
    yield start, body[start:]


def _enum_values(
    text: str,
) -> list[tuple[str, list[tuple[str, str | None, int]]]]:
    """Return each enum's family and its members with their raw expressions and lines."""
    masked = _without_comments(text)
    found = []
    for match in ENUM_HEAD.finditer(masked):
        opening = masked.find("{", match.start())
        closing = _match_brace(masked, opening)
        if closing < 0:
            continue
        tag = match.group(1) or ""
        tail = re.match(r"\s*(\w+)\s*;", masked[closing + 1 :])
        family = tag or (tail.group(1) if tail else "")
        body = masked[opening + 1 : closing]
        members = []
        for start, part in _split_commas(body):
            piece = part.strip()
            if not piece:
                continue
            member = re.match(r"(\w+)\s*(?:=\s*(.*))?$", piece, re.S)
            if member is None:
                continue
            name = member.group(1)
            expression = member.group(2)
            offset = opening + 1 + start + part.find(name)
            line = masked.count("\n", 0, offset) + 1
            members.append((name, expression.strip() if expression else None, line))
        found.append((family, members))
    return found


def _define_values(text: str) -> list[tuple[str, str, int]]:
    """Return each object-like macro's name, raw body and line."""
    masked = _without_comments(text)
    lines = masked.split("\n")
    found = []
    index = 0
    while index < len(lines):
        start = index
        line = lines[index]
        while line.rstrip().endswith("\\") and index + 1 < len(lines):
            index += 1
            line = line.rstrip()[:-1] + " " + lines[index]
        index += 1
        match = VALUE_DEFINE.match(line)
        if match is None:
            continue
        name, params, body = match.groups()
        body = body.strip()
        if params or not body:
            continue
        found.append((name, body, start + 1))
    return found


def _char_code(literal: str) -> int:
    """Return the value of a one-character C literal."""
    escapes = {"n": 10, "t": 9, "r": 13, "0": 0, "\\": 92, "'": 39, '"': 34}
    char = literal[1:-1]
    if char.startswith("\\") and len(char) >= 2:
        return escapes.get(char[1], ord(char[1]))
    return ord(char[0]) if char else 0


def _eval_node(node: ast.AST) -> int | None:
    if isinstance(node, ast.Constant):
        return node.value if type(node.value) is int else None
    if isinstance(node, ast.UnaryOp):
        value = _eval_node(node.operand)
        if value is None:
            return None
        if isinstance(node.op, ast.UAdd):
            return value
        if isinstance(node.op, ast.USub):
            return -value
        if isinstance(node.op, ast.Invert):
            return ~value
        return None
    if isinstance(node, ast.BinOp):
        left = _eval_node(node.left)
        right = _eval_node(node.right)
        if left is None or right is None:
            return None
        if isinstance(node.op, ast.Add):
            return left + right
        if isinstance(node.op, ast.Sub):
            return left - right
        if isinstance(node.op, ast.Mult):
            return left * right
        if isinstance(node.op, (ast.Div, ast.FloorDiv)) and right:
            return left // right
        if isinstance(node.op, ast.Mod) and right:
            return left % right
        if isinstance(node.op, ast.LShift):
            return left << right
        if isinstance(node.op, ast.RShift):
            return left >> right
        if isinstance(node.op, ast.BitOr):
            return left | right
        if isinstance(node.op, ast.BitAnd):
            return left & right
        if isinstance(node.op, ast.BitXor):
            return left ^ right
        return None
    return None


def _c_expression(expression: str, values: dict[str, int]) -> int | None:
    """Evaluate a C integer constant expression, resolving known names."""
    text = C_SUFFIX.sub(r"\1", expression)
    text = C_CAST.sub("", text)
    text = C_CHAR.sub(lambda match: str(_char_code(match.group(0))), text)
    text = C_OCTAL.sub(lambda match: str(int(match.group(1), 8)), text)

    def replace(match: re.Match[str]) -> str:
        if match.group(1) is not None:
            return match.group(0)
        name = match.group(0)
        if name not in values:
            raise KeyError(name)
        return str(values[name])

    try:
        text = C_TOKEN.sub(replace, text)
        tree = ast.parse(text, mode="eval")
    except (KeyError, SyntaxError):
        return None
    return _eval_node(tree.body)


def _value_family(name: str) -> str:
    """Return a macro's prefix family, such as ``ENEMY_ID_``."""
    head, separator, _ = name.rpartition("_")
    return head + separator if separator else name


def _matches_type(name: str, family: str, wanted: str | None) -> bool:
    if not wanted:
        return True
    if name.startswith(wanted):
        return True
    if family == wanted or family == f"enum {wanted}":
        return True
    return family.endswith("_") and family[:-1] == wanted


def _named_values(
    headers: list[str], wanted: int, kind: str | None
) -> list[NamedValue]:
    """Return every enum member and numeric macro with ``wanted`` among the headers."""
    enums = []
    defines = []
    for header in headers:
        try:
            text = (ROOT / header).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        enums.extend(
            (header, family, members) for family, members in _enum_values(text)
        )
        defines.extend(
            (header, name, body, line) for name, body, line in _define_values(text)
        )
    values: dict[str, int] = {}
    for _ in range(5):
        changed = False
        for _, name, body, _ in defines:
            if name in values:
                continue
            value = _c_expression(body, values)
            if value is not None:
                values[name] = value
                changed = True
        for _, _, members in enums:
            previous: int | None = -1
            for name, body, _ in members:
                if name in values:
                    previous = values[name]
                    continue
                value = (
                    _c_expression(body, values)
                    if body is not None
                    else (previous + 1 if previous is not None else None)
                )
                if value is not None:
                    values[name] = value
                    previous = value
                    changed = True
                else:
                    previous = None
        if not changed:
            break
    found: list[NamedValue] = []
    for header, family, members in enums:
        for name, _, line in members:
            if name in values and values[name] == wanted:
                label = f"enum {family}" if family else "enum"
                if _matches_type(name, label, kind):
                    found.append(NamedValue(name, values[name], header, line, label))
    for header, name, _, line in defines:
        if name in values and values[name] == wanted:
            family = _value_family(name)
            if _matches_type(name, family, kind):
                found.append(NamedValue(name, values[name], header, line, family))
    return found


def _value_rank(header: str, image: str | None, folder: str | None) -> int:
    """Rank a header's scope: the image's own, the group's, then the include tree."""
    if image is None:
        if header.startswith("include/psyq/"):
            return 2
        return 0 if header.startswith("include/") else 1
    if folder is not None and header.startswith(folder + "/"):
        return 0
    if header.startswith("src/"):
        return 1
    if header.startswith("include/psyq/"):
        return 3
    return 2


def value(args: argparse.Namespace) -> int:
    """List the enum members and numeric macros with one value."""
    wanted = _address(args.number)
    folder = None
    if args.image is not None:
        try:
            folder = f"src/{source_folder(args.image)}"
        except (IndexError, ValueError):
            raise SystemExit(f"symbol: {args.image} is not a target") from None
    found = _named_values(_value_headers(args.image), wanted, args.type)
    found.sort(
        key=lambda item: (
            _value_rank(item.header, args.image, folder),
            item.header,
            item.line,
            item.name,
        )
    )
    for item in found:
        print(f"{item.name}\t{item.header}:{item.line}\t{item.family}")
    return 0


# --- Values: what each numeric literal means ------------------------------------------------

VALUE_LITERAL = re.compile(r"(?<![\w.])(0[xX][0-9A-Fa-f]+|\d+)([uUlL]*)(?![\w.])")
VALUE_BODY = re.compile(
    r"\b(MATCH|NON_MATCHING|HAND_ASM)\b([^;{}]*?)\b(\w+)\s*\(([^;{}]*)\)\s*\{"
)
VALUE_MEMBER_LINE = re.compile(
    r"^\s*(?:const\s+|volatile\s+)*(?:(struct|union)\s+)?"
    r"([A-Za-z_]\w*(?:\s*\*+)?)\s+(\w+)\s*((?:\[[^\]]*\]\s*)*)"
    r"\s*(?::\s*\d+)?\s*;\s*(?:/\*\s*(.*?)\s*\*/)?\s*$"
)
VALUE_ANON_LINE = re.compile(r"\b(?:struct|union)\s*\{([^{}]*)\}\s*(\w+)\s*;")
VALUE_GLOBAL_LINE = re.compile(
    r"^\s*extern\s+(?:const\s+|volatile\s+)*"
    r"((?:struct\s+|union\s+)?\w+(?:\s*\*+)?(?:\s+(?:const|volatile))*)"
    r"\s+(\w+)\s*((?:\[[^\]]*\]\s*)*)\s*;",
    re.M,
)
VALUE_TYPEDEF_LINE = re.compile(r"^\s*typedef\s+([^;{}()]+?)\s+(\w+)\s*;", re.M)
VALUE_VIEW_ANY = re.compile(
    r"#\s*define\s+(\w+)\s+\(\(\s*(?:volatile\s+)?(\w+)\s*\*\s*\)\s*\1\s*\)"
)
VALUE_PROTO = re.compile(
    r"^[ \t]*(?:const\s+|volatile\s+)*"
    r"((?:struct\s+|union\s+)?[A-Za-z_]\w*(?:\s*\*+)?)"
    r"\s+(\w+)\s*\(([^;{}()]*)\)\s*;",
    re.M,
)
VALUE_LOCAL_LINE = re.compile(
    r"^\s*(?:const\s+|volatile\s+)*((?:struct\s+|union\s+)?[A-Za-z_]\w*)"
    r"\s*(\*?)\s*(\w+)\s*((?:\[[^\]]*\]\s*)*)\s*(?:=[^;]*)?;",
    re.M,
)
VALUE_CAST = re.compile(
    r"^\(\s*(?:volatile\s+|const\s+)*(?:struct\s+|union\s+)?(\w+)\s*(\*+)\s*\)"
)
VALUE_LEFTOVER = re.compile(
    r"(\([^()]*\)|[A-Za-z_][\w.\[\]\->]*?)\s*"
    r"(==|!=|<=|>=|<|>|=|\+=|-=|\*=|/=|&=|\|=|\^=|<<|>>)\s*$"
)
VALUE_RIGHT_OPERATOR = re.compile(
    r"^\s*(==|!=|<=|>=|<|>|\+|-|\*|/|&|\||\^|<<|>>)\s*([A-Za-z_][\w.\[\]\->]*)"
)
VALUE_SWITCH = re.compile(r"\bswitch\s*\(")
VALUE_CASE = re.compile(r"\bcase\s+(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*:")
VALUE_COUNT_NAME = re.compile(
    r"(?:^count$|_count$|^counter$|_counter$|^timer$|_timer$|^limit$|^total$|"
    r"^wait$|^amount$|^radius$|^distance$|^frames$|^steps$|^hp$|^mp$|"
    r"^damage$|^price$|^exp$|^gold$|^percent$|^percentage$)"
)
VALUE_INDEX_NAME = re.compile(
    r"(?:^index$|_index$|^slot$|_slot$|^row$|_row$|^column$|_column$|^position$)"
)
VALUE_COORD_NAME = re.compile(r"(?:^x$|^y$|^z$|^vx$|^vy$|^vz$|^width$|^height$)")
VALUE_COLOUR_NAME = re.compile(r"(?:^colou?r$|_colou?r$|^red$|^green$|^blue$)")
VALUE_FLAGS_NAME = re.compile(r"(?:^flags$|_flags$)")
VALUE_STATE_NAME = re.compile(r"(?:^state$|_state$|^mode$|_mode$|^step$|_step$)")
VALUE_ANGLE_NAME = re.compile(r"(?:^angle$|_angle$)", re.I)
VALUE_FIXED_COMMENT = re.compile(r"\b16\.16\b")
VALUE_ANGLE_CONSTANTS = (
    (512, "ANGLE_45"),
    (1024, "ANGLE_90"),
    (2048, "ANGLE_180"),
    (3072, "ANGLE_270"),
)
VALUE_ALL_ONES = {1: "BYTE_MASK", 2: "HALF_MASK"}


@dataclass(frozen=True)
class ValueFamily:
    """One enum: its tag, the name prefix its members share, and their values."""

    tag: str
    prefix: str
    members: tuple[tuple[str, int], ...]
    header: str


@dataclass(frozen=True)
class ValueSignal:
    """What the declaration around one literal says about its role."""

    role: str
    family: str
    confidence: str
    comment: str
    ctype: str


@dataclass(frozen=True)
class ValueSite:
    """One numeric literal of a matched body and what its role is."""

    file: str
    line: int
    literal: str
    role: str
    family: str
    constant: str
    form: str
    confidence: str


def _value_prefix(names: list[str]) -> str:
    """Return the common ``TAG_`` prefix of the names."""
    if not names:
        return ""
    prefix = names[0]
    for name in names[1:]:
        while prefix and not name.startswith(prefix):
            prefix = prefix[:-1]
    return prefix[: prefix.rfind("_") + 1] if "_" in prefix else ""


def _header_values(
    headers: list[str],
) -> tuple[list, list, dict[str, int]]:
    """Return each header's enums, macros and the resolved value of every name."""
    enums = []
    defines = []
    for header in headers:
        try:
            text = (ROOT / header).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        enums.extend(
            (header, family, members) for family, members in _enum_values(text)
        )
        defines.extend(
            (header, name, body, line) for name, body, line in _define_values(text)
        )
    values: dict[str, int] = {}
    for _ in range(5):
        changed = False
        for _, name, body, _ in defines:
            if name in values:
                continue
            value = _c_expression(body, values)
            if value is not None:
                values[name] = value
                changed = True
        for _, _, members in enums:
            previous: int | None = -1
            for name, body, _ in members:
                if name in values:
                    previous = values[name]
                    continue
                value = (
                    _c_expression(body, values)
                    if body is not None
                    else (previous + 1 if previous is not None else None)
                )
                if value is not None:
                    values[name] = value
                    previous = value
                    changed = True
                else:
                    previous = None
        if not changed:
            break
    return enums, defines, values


def _value_families(headers: list[str]) -> tuple[dict[str, ValueFamily], set[str]]:
    """Return each visible enum by its tag, and every visible constant's name."""
    enums, _, values = _header_values(headers)
    families: dict[str, ValueFamily] = {}
    for header, tag, members in enums:
        if not tag:
            continue
        resolved = tuple(
            (name, values[name]) for name, _, _ in members if name in values
        )
        if not resolved:
            continue
        family = ValueFamily(
            tag, _value_prefix([name for name, _ in resolved]), resolved, header
        )
        existing = families.get(tag)
        if existing is None or len(resolved) > len(existing.members):
            families[tag] = family
    return families, set(values)


def _value_members(
    body: str, records: dict[str, dict[str, tuple[str, str]]]
) -> dict[str, tuple[str, str]]:
    """Return the members of one aggregate body, registering its anonymous ones."""
    members: dict[str, tuple[str, str]] = {}
    stack = [members]
    pending: list[str] = []
    count = 0
    for line in body.split("\n"):
        for match in VALUE_ANON_LINE.finditer(line):
            count += 1
            name = f"value_anon_{count}"
            inner = _value_members(match.group(1), records)
            records[name] = inner
            stack[-1][match.group(2)] = (name, "")
        if VALUE_ANON_LINE.search(line):
            continue
        match = VALUE_MEMBER_LINE.match(line)
        if match is not None and "{" not in line and not line.strip().startswith("}"):
            ctype = (match.group(2) + match.group(4)).strip()
            stack[-1][match.group(3)] = (ctype, (match.group(5) or "").strip())
            continue
        if re.search(r"\b(?:struct|union)\s*\{", line):
            count += 1
            name = f"value_anon_{count}"
            inner: dict[str, tuple[str, str]] = {}
            records[name] = inner
            stack.append(inner)
            pending.append(name)
            continue
        closing = re.match(r"\}\s*(\w+)?\s*(?:\[[^\]]*\])?\s*;", line.strip())
        if closing is not None and len(stack) > 1:
            stack.pop()
            name = pending.pop()
            if closing.group(1):
                stack[-1][closing.group(1)] = (name, "")
    return members


def _value_records() -> tuple[dict[str, dict[str, tuple[str, str]]], dict[str, str]]:
    """Return each record's members and each typedef alias's type, from every header."""
    records: dict[str, dict[str, tuple[str, str]]] = {}
    typedefs: dict[str, str] = {}
    for path in ctext.tracked_c(ROOT):
        if not path.endswith(".h") or path.startswith("include/psyq/"):
            continue
        text = ctext.read(ROOT, path)
        masked = ctext.mask(text)
        for match in RECORD_HEAD.finditer(masked):
            opening = match.end() - 1
            closing = _match_brace(masked, opening)
            if closing < 0:
                continue
            tag = match.group(1) or ""
            tail = re.match(r"\s*(\w+)\s*;", masked[closing + 1 :])
            alias = tail.group(1) if tail else ""
            members = _value_members(text[opening + 1 : closing], records)
            for name in {part for part in (tag, alias) if part}:
                if name not in records or len(members) > len(records[name]):
                    records[name] = members
        for match in VALUE_TYPEDEF_LINE.finditer(masked):
            base = match.group(1).strip()
            if base.split()[0] in ("struct", "union", "enum"):
                continue
            typedefs.setdefault(match.group(2), base)
    return records, typedefs


def _value_globals() -> dict[str, str]:
    """Return each ``extern`` global's declared type."""
    found: dict[str, str] = {}
    for path in ctext.tracked_c(ROOT):
        if not path.endswith(".h") or path.startswith("include/psyq/"):
            continue
        text = ctext.read(ROOT, path)
        for match in VALUE_GLOBAL_LINE.finditer(ctext.mask(text)):
            found.setdefault(match.group(2), (match.group(1) + match.group(3)).strip())
    return found


def _value_prototypes() -> tuple[dict[str, list[tuple[str, str]]], dict[str, str]]:
    """Return each function's parameters and return type from its prototypes."""
    from bof3.source import decls

    params: dict[str, list[tuple[str, str]]] = {}
    returns: dict[str, str] = {}
    for path in ctext.tracked_c(ROOT):
        if not path.endswith(".h") or path.startswith("include/psyq/"):
            continue
        text = ctext.read(ROOT, path)
        for match in VALUE_PROTO.finditer(ctext.mask(text)):
            name = match.group(2)
            if name in ("if", "while", "for", "switch", "sizeof", "return"):
                continue
            found = [
                decls.split_param(part) for part in decls.split_args(match.group(3))
            ]
            params.setdefault(name, found)
            returns.setdefault(name, match.group(1).strip())
    return params, returns


def _value_views() -> list[tuple[str, str, str]]:
    """Return ``(folder, macro, type)`` for each macro that views a global as a record."""
    found = []
    for path in ctext.tracked_c(ROOT):
        if not path.endswith(".h") or path.startswith("include/psyq/"):
            continue
        text = ctext.read(ROOT, path)
        for match in VALUE_VIEW_ANY.finditer(text):
            found.append((str(Path(path).parent), match.group(1), match.group(2)))
    return found


def _value_dereference(ctype: str) -> str | None:
    """Return what one ``*`` or one array subscript of the type gives."""
    text = " ".join(ctype.split())
    index = text.find("[")
    if index >= 0:
        return text[:index].strip()
    if text.endswith("*"):
        return text[:-1].strip() or None
    return None


def _value_element(ctype: str) -> str | None:
    """Return the element type of an array or pointer type."""
    return _value_dereference(ctype)


def _value_member(
    index: dict,
    ctype: str,
    name: str,
) -> tuple[str, str] | None:
    """Return the ``(type, comment)`` of one member of ``ctype``."""
    text = " ".join(ctype.split())
    text = re.sub(r"\b(?:const|volatile)\b", " ", text)
    for _ in range(4):
        text = " ".join(text.split())
        stripped = _value_dereference(text)
        if stripped is not None:
            text = stripped
            continue
        base = re.sub(r"^(?:struct|union)\s+", "", text)
        base = index["typedefs"].get(base, base)
        base = re.sub(r"^(?:struct|union)\s+", "", base)
        record = index["records"].get(base)
        if record is None:
            return None
        found = record.get(name)
        if found is not None:
            return found
        # A member of an anonymous union shares its enclosing record's scope.
        for member_type, _ in record.values():
            inner = index["records"].get(member_type)
            if inner is not None and name in inner:
                return inner[name]
        return None
    return None


def _value_type(
    expression: str,
    index: dict,
    scope: dict[str, str],
    depth: int = 0,
) -> str | None:
    """Return the declared type of an expression, or None when it cannot be resolved."""
    if depth > 8:
        return None
    text = expression.strip()
    while text.startswith("(") and text.endswith(")"):
        inner = text[1:-1]
        if not _value_balanced(inner):
            break
        text = inner.strip()
    if not text:
        return None
    cast = VALUE_CAST.match(text)
    if cast is not None:
        return cast.group(1) + cast.group(2)
    if text.startswith("*"):
        base = _value_type(text[1:], index, scope, depth + 1)
        return _value_dereference(base) if base else None
    if text.startswith("&"):
        base = _value_type(text[1:], index, scope, depth + 1)
        return base + "*" if base else None
    identifier = re.fullmatch(r"[A-Za-z_]\w*", text)
    if identifier is not None:
        name = identifier.group(0)
        if name in scope:
            return scope[name]
        view = index["views"].get(name)
        if view is not None:
            return view + "*"
        if name in index["globals"]:
            return index["globals"][name]
        return None
    call = re.match(r"^([A-Za-z_]\w*)\s*\(", text)
    if call is not None:
        return index["returns"].get(call.group(1))
    # The last top-level member access decides the type.
    split = _value_last_access(text)
    if split is not None:
        base, operator, name = split
        ctype = _value_type(base, index, scope, depth + 1)
        if ctype is None:
            return None
        if operator == "->":
            ctype = _value_dereference(ctype)
            if ctype is None:
                return None
        found = _value_member(index, ctype, name)
        return found[0] if found is not None else None
    # A trailing subscript takes the element type of what it indexes.
    subscript = re.match(r"^(.*)\[[^\]]*\]\s*$", text, re.S)
    if subscript is not None:
        base = _value_type(subscript.group(1), index, scope, depth + 1)
        return _value_element(base) if base else None
    return None


def _value_balanced(text: str) -> bool:
    """True when every bracket of the text is closed inside it."""
    depth = 0
    for char in text:
        depth += char in "([{"
        depth -= char in ")]}"
        if depth < 0:
            return False
    return depth == 0


def _value_last_access(text: str) -> tuple[str, str, str] | None:
    """Split an expression at its last top-level ``.`` or ``->``."""
    depth = 0
    found = None
    index = 0
    while index < len(text):
        char = text[index]
        if char in "([{":
            depth += 1
        elif char in ")]}":
            depth -= 1
        elif depth == 0 and char == ".":
            found = (index, ".")
        elif depth == 0 and char == "-" and text[index + 1 : index + 2] == ">":
            found = (index, "->")
            index += 1
        index += 1
    if found is None:
        return None
    position, operator = found
    name = re.match(r"\s*(\w+)", text[position + len(operator) :])
    if name is None:
        return None
    return text[:position], operator, name.group(1)


def _value_member_map(
    index: dict,
) -> dict[str, list[tuple[str, str]]]:
    """Return each member name's ``(type, comment)`` in every record that declares it."""
    found: dict[str, list[tuple[str, str]]] = collections.defaultdict(list)
    for record in index["records"].values():
        for name, info in record.items():
            found[name].append(info)
    return found


def _value_signal(
    index: dict,
    target: str,
    scope: dict[str, str],
) -> ValueSignal | None:
    """Return what the declaration of ``target`` says about a literal beside it."""
    text = target.strip()
    while text.startswith("(") and text.endswith(")") and _value_balanced(text[1:-1]):
        text = text[1:-1].strip()
    if not text or text.count("[") != text.count("]"):
        return None
    if not re.fullmatch(r"[A-Za-z_][\w.\[\]\->]*", text):
        return None
    split = _value_last_access(text)
    name = split[2] if split is not None else text
    ctype = _value_type(text, index, scope)
    member = None
    if split is not None:
        base = _value_type(split[0], index, scope)
        if base is not None:
            if split[1] == "->":
                base = _value_dereference(base) or base
            member = _value_member(index, base, name)
    if member is None and ctype is None:
        candidates = set(index["member_map"].get(name, []))
        if len(candidates) == 1:
            member = candidates.pop()
    comment = member[1] if member is not None else ""
    if not ctype and member is not None:
        ctype = member[0]
    comments = _value_chain_comments(index, text, scope)
    return _value_name_signal(
        name,
        comment,
        ctype or "",
        index["families"],
        any(VALUE_FIXED_COMMENT.search(item) for item in comments),
    )


def _value_chain_comments(index: dict, text: str, scope: dict[str, str]) -> list[str]:
    """Return the comments of each record member on an access chain."""
    comments = []
    current = text
    for _ in range(8):
        split = _value_last_access(current)
        if split is None:
            break
        base, operator, name = split
        ctype = _value_type(base, index, scope)
        if ctype is not None:
            if operator == "->":
                ctype = _value_dereference(ctype) or ctype
            member = _value_member(index, ctype, name)
            if member is not None:
                comments.append(member[1])
        current = base
    return comments


def _value_family_role(tag: str) -> str:
    """Return the role an enum tag's name declares."""
    if tag.endswith("Flags"):
        return "flags"
    if tag.endswith("Id"):
        return "id"
    if tag.endswith("Index"):
        return "index"
    if tag.endswith(("Type", "Category", "Kind")):
        return "type"
    return "state"


def _value_camel(stem: str) -> str:
    """Return ``item`` as ``Item``, for the enum tag an id family takes."""
    return "".join(part.capitalize() for part in stem.split("_"))


def _value_name_signal(
    name: str,
    comment: str,
    ctype: str,
    families: dict[str, ValueFamily],
    fixed: bool = False,
) -> ValueSignal | None:
    """Return the role a member's name, comment or type declares."""
    for word in re.findall(r"[A-Za-z_]\w*", comment):
        if word not in families:
            continue
        return ValueSignal(_value_family_role(word), word, "typed", comment, ctype)
    enum_type = re.sub(r"^(?:struct|union)\s+", "", " ".join(ctype.split()))
    if enum_type in families:
        return ValueSignal(
            _value_family_role(enum_type), enum_type, "typed", comment, ctype
        )
    if name.endswith("_id"):
        tag = _value_camel(name[: -len("_id")]) + "Id"
        if tag in families:
            return ValueSignal("id", tag, "typed", comment, ctype)
        return ValueSignal("id", "", "family", comment, ctype)
    if name.endswith("_index") or VALUE_INDEX_NAME.search(name):
        stem = name[: -len("_index")] if name.endswith("_index") else ""
        tag = _value_camel(stem) + "Index" if stem else ""
        if tag in families:
            return ValueSignal("index", tag, "typed", comment, ctype)
        return ValueSignal("index", "", "typed", comment, ctype)
    if fixed or name == "fixed" or VALUE_FIXED_COMMENT.search(comment):
        return ValueSignal("fixed", "", "typed", comment, ctype)
    if "*" in ctype or "[" in ctype:
        return None
    if VALUE_COUNT_NAME.search(name) and not VALUE_FLAGS_NAME.search(name):
        return ValueSignal("count", "", "typed", comment, ctype)
    if VALUE_COORD_NAME.search(name):
        return ValueSignal("coordinate", "", "typed", comment, ctype)
    if VALUE_COLOUR_NAME.search(name):
        return ValueSignal("colour", "", "typed", comment, ctype)
    if VALUE_ANGLE_NAME.search(name):
        return ValueSignal("angle", "", "typed", comment, ctype)
    if ctype.strip() == "bool":
        return ValueSignal("bool", "", "typed", comment, ctype)
    if VALUE_FLAGS_NAME.search(name):
        return ValueSignal("flags", "", "family", comment, ctype)
    if VALUE_STATE_NAME.search(name):
        return ValueSignal("state", "", "family", comment, ctype)
    return None


def _value_family_member(family: ValueFamily, value: int) -> str:
    """Return the one member of the family with ``value``, else empty."""
    names = {name for name, member_value in family.members if member_value == value}
    return names.pop() if len(names) == 1 else ""


def _value_operator(masked: str, start: int, end: int) -> str:
    """Return the operator the literal is an operand of: ``mask``, ``shift`` or empty."""
    before = masked[max(0, start - 40) : start]
    after = masked[end : end + 40]
    if re.search(r"<<\s*$", before) or re.match(r"\s*>>", after):
        return "shift"
    left = re.search(r"([&|^])=?\s*$", before)
    if left is not None:
        operator = left.group(1)
        if operator == "&" and before[max(0, left.start() - 1) : left.start()] == "&":
            return ""
        if operator == "|" and before[max(0, left.start() - 1) : left.start()] == "|":
            return ""
        if before[left.start() + 1 : left.start() + 2] == "=":
            return ""
        return "mask"
    right = re.match(r"\s*([&|^])(?![&=|])", after)
    if right is not None:
        return "mask"
    return ""


def _value_target(masked: str, start: int, end: int) -> str:
    """Return the expression the literal is an operand of or is compared with."""
    before = masked[max(0, start - 90) : start]
    after = masked[end : end + 70]
    left = VALUE_LEFTOVER.search(before)
    if left is not None:
        return left.group(1).strip()
    right = VALUE_RIGHT_OPERATOR.match(after)
    if right is not None:
        return right.group(2).strip()
    return ""


def _value_call_argument(masked: str, start: int, end: int) -> tuple[str, int] | None:
    """Return the callee and argument index when the literal is a whole call argument."""
    depth = 0
    opening = -1
    for index in range(start - 1, -1, -1):
        char = masked[index]
        if char in ")]}":
            depth += 1
        elif char in "([{":
            if depth == 0:
                if char != "(":
                    return None
                opening = index
                break
            depth -= 1
    if opening < 0:
        return None
    callee = re.search(r"([A-Za-z_]\w*)\s*$", masked[:opening])
    if callee is None:
        return None
    keyword = callee.group(1)
    if keyword in ("if", "while", "for", "switch", "sizeof", "return", "do"):
        return None
    inner = masked[opening + 1 : start]
    commas = 0
    brackets = 0
    last = 0
    for offset, char in enumerate(inner):
        if char in "([{":
            brackets += 1
        elif char in ")]}":
            brackets -= 1
        elif char == "," and brackets == 0:
            commas += 1
            last = offset + 1
    before_argument = inner[last:]
    if before_argument.strip() and not re.fullmatch(
        r"\s*(?:\(?\s*(?:u|s)(?:8|16|32)\s*\)?)?\s*", before_argument
    ):
        return None
    after = re.match(r"\s*([,)])", masked[end:])
    if after is None:
        return None
    return keyword, commas


def _value_form(literal: str, value: int, signal: ValueSignal) -> str:
    """Return the rewrite when only the form is wrong, else empty."""
    suffix = re.search(r"[uUlL]+$", literal)
    tail = suffix.group(0) if suffix else ""
    if signal.role == "index" and value == 0xFF:
        return ""
    if signal.role in ("count", "index", "coordinate", "colour"):
        return str(value) + tail if not _is_decimal(literal) else ""
    if signal.role == "mask":
        width = _value_width(signal.ctype)
        if width is not None and value == (1 << (8 * width)) - 1:
            return ""
        return f"0x{value:X}{tail}"
    if signal.role == "offset":
        if _is_decimal(literal):
            return f"0x{value:X}{tail}"
        return ""
    return ""


def _is_decimal(literal: str) -> bool:
    return not literal.lower().startswith("0x")


def _value_width(ctype: str) -> int | None:
    """Return the byte width a declared type names, when it is a plain integer."""
    text = " ".join(ctype.split())
    return {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4}.get(text)


def _value_role_constant(
    index: dict, signal: ValueSignal, value: int
) -> tuple[str, str]:
    """Return the ``(constant, form)`` a signal gives one value."""
    families = index["families"]
    if signal.family:
        family = families.get(signal.family)
        if family is not None:
            constant = _value_family_member(family, value)
            if constant:
                return constant, ""
    if signal.role == "mask":
        width = _value_width(signal.ctype)
        name = VALUE_ALL_ONES.get(width) if width is not None else None
        if name is None:
            name = {0xFF: "BYTE_MASK", 0xFFFF: "HALF_MASK"}.get(value)
        if name and name in index["names"]:
            return name, ""
    if signal.role == "angle":
        for angle, name in VALUE_ANGLE_CONSTANTS:
            if angle == value and name in index["names"]:
                return name, ""
    if signal.role == "index" and value == 0xFF and "GAME_NONE" in index["names"]:
        return "GAME_NONE", ""
    if signal.role == "bool":
        if value == 1:
            return "true", ""
        if value == 0:
            return "false", ""
    return "", ""


def _value_scan_file(path: str, image: str | None, index: dict) -> list[ValueSite]:
    """Return every classified literal of one source file."""
    text = ctext.read(ROOT, path)
    masked = ctext.mask(text)
    found: list[ValueSite] = []
    for match in VALUE_BODY.finditer(masked):
        if match.group(1) != "MATCH":
            continue
        body_start = match.end()
        depth = 1
        position = body_start
        while position < len(masked) and depth:
            depth += (masked[position] == "{") - (masked[position] == "}")
            position += 1
        body = masked[body_start:position]
        scope: dict[str, str] = {}
        for local in VALUE_LOCAL_LINE.finditer(body):
            ctype = (local.group(1) + local.group(2) + local.group(4)).strip()
            scope.setdefault(local.group(3), ctype)
        from bof3.source import decls

        for part in decls.split_args(match.group(4)):
            ctype, name = decls.split_param(part)
            if name:
                scope.setdefault(name, ctype)
        _value_scan_body(path, text, body_start, body, scope, index, found)
        _value_switch_sites(path, text, body_start, body, scope, index, found)
    return found


def _value_number(literal: str) -> int:
    """Return the value of a C numeric literal, without its suffix."""
    text = re.sub(r"[uUlL]+$", "", literal)
    return int(text, 0)


def _value_scan_body(
    path: str,
    text: str,
    body_start: int,
    body: str,
    scope: dict[str, str],
    index: dict,
    found: list[ValueSite],
) -> None:
    """Classify the literals of one matched body into ``found``."""
    for literal_match in VALUE_LITERAL.finditer(body):
        literal = literal_match.group(0)
        value = _value_number(literal)
        start, end = literal_match.start(), literal_match.end()
        signal = None
        target = _value_target(body, start, end)
        if target:
            signal = _value_signal(index, target, scope)
        operator = _value_operator(body, start, end)
        if signal is None and operator == "mask":
            signal = ValueSignal("mask", "", "typed", "", "")
        argument = None
        if signal is None:
            argument = _value_call_argument(body, start, end)
            if argument is not None:
                callee, slot = argument
                if callee == "FIELD" and slot == 2:
                    signal = ValueSignal("offset", "", "typed", "", "u32")
                else:
                    params = index["prototypes"].get(callee)
                    if params is not None and slot < len(params):
                        ctype, name = params[slot]
                        if name:
                            signal = _value_signal(index, name, {name: ctype})
                            if signal is not None:
                                signal = ValueSignal(
                                    signal.role,
                                    signal.family,
                                    signal.confidence,
                                    signal.comment,
                                    ctype,
                                )
        if signal is not None and signal.role == "mask" and operator != "mask":
            continue
        if signal is None:
            continue
        constant, role_form = _value_role_constant(index, signal, value)
        if not constant and operator == "mask" and signal.role != "mask":
            signal = ValueSignal(
                "mask", signal.family, "typed", signal.comment, signal.ctype
            )
        form = role_form or _value_form(literal, value, signal)
        if form.lower() == literal.lower():
            form = ""
        if not constant and not form and not signal.family:
            continue
        line = text.count("\n", 0, body_start + start) + 1
        found.append(
            ValueSite(
                path,
                line,
                literal,
                signal.role,
                signal.family,
                constant,
                form,
                signal.confidence,
            )
        )


def _value_switch_sites(
    path: str,
    text: str,
    body_start: int,
    body: str,
    scope: dict[str, str],
    index: dict,
    found: list[ValueSite],
) -> None:
    """Classify the ``case`` labels of each switch by what the switch tests."""
    for switch in VALUE_SWITCH.finditer(body):
        close = body.find(")", switch.end())
        if close < 0:
            continue
        target = body[switch.end() : close]
        signal = _value_signal(index, target, scope)
        if signal is None:
            continue
        opening = body.find("{", close)
        if opening < 0:
            continue
        depth, position = 1, opening + 1
        while position < len(body) and depth:
            depth += (body[position] == "{") - (body[position] == "}")
            position += 1
        region = body[opening:position]
        for case in VALUE_CASE.finditer(region):
            literal = case.group(1)
            value = _value_number(literal)
            constant, form = _value_role_constant(index, signal, value)
            if not constant and not form and not signal.family:
                continue
            offset = opening + case.start(1)
            found.append(
                ValueSite(
                    path,
                    text.count("\n", 0, body_start + offset) + 1,
                    literal,
                    signal.role,
                    signal.family,
                    constant,
                    form,
                    signal.confidence,
                )
            )


def _value_index(image: str | None) -> dict:
    """Return the declarations and constants one source file sees."""
    key = image or ""
    cached = _VALUE_INDEX.get(key)
    if cached is not None:
        return cached
    shared = _VALUE_SHARED
    if image is None:
        headers = [
            name
            for name in ctext.tracked(ROOT, "include")
            if name.endswith(".h") and not name.startswith("include/psyq/")
        ]
    else:
        headers = _value_headers(image)
    families, names = _value_families(headers)
    index = {
        "records": shared["records"],
        "typedefs": shared["typedefs"],
        "globals": shared["globals"],
        "prototypes": shared["prototypes"],
        "returns": shared["returns"],
        "member_map": shared["member_map"],
        "families": families,
        "names": names,
        "views": _value_views_for(image),
    }
    _VALUE_INDEX[key] = index
    return index


def _value_views_for(image: str | None) -> dict[str, str]:
    """Return the globals a source of ``image`` reads through a record-view macro."""
    if image is None:
        return {}
    found: dict[str, str] = {}
    from bof3.resolve.ids import source_folder

    folder = f"src/{source_folder(image)}"
    for parent, macro, ctype in _VALUE_VIEWS:
        if parent == "" or folder == parent or folder.startswith(parent + "/"):
            found[macro] = ctype
    task = _task_types().get(image)
    if task is not None:
        found["g_Task"] = task
    return found


def _value_images() -> dict[str, str]:
    """Return source folder -> the image whose sources it holds."""
    found: dict[str, str] = {}
    for image, manifest in _layer_manifests().items():
        found.setdefault(manifest.source_dir, image)
    return found


def _value_image_of(path: str, images: dict[str, str]) -> str | None:
    """Return the image whose source folder holds ``path``, longest folder first."""
    parts = path.split("/")
    for length in range(len(parts) - 1, 0, -1):
        folder = "/".join(parts[:length])
        if folder in images:
            return images[folder]
    return None


def _value_sites() -> list[ValueSite]:
    """Return every classified literal of every matched body."""
    images = _value_images()
    sites: list[ValueSite] = []
    for path in ctext.tracked(ROOT, "src"):
        if not path.endswith((".c", ".h")):
            continue
        image = _value_image_of(path, images)
        index = _value_index(image)
        sites.extend(_value_scan_file(path, image, index))
    return sites


_VALUE_SHARED: dict = {}
_VALUE_INDEX: dict[str, dict] = {}
_VALUE_VIEWS: list[tuple[str, str, str]] = []


def values(args: argparse.Namespace) -> int:
    """Scan the matched bodies for numeric literals whose role is declared."""
    global _VALUE_SHARED, _VALUE_VIEWS
    if not _VALUE_SHARED:
        records, typedefs = _value_records()
        prototypes, returns = _value_prototypes()
        _VALUE_SHARED = {
            "records": records,
            "typedefs": typedefs,
            "globals": _value_globals(),
            "prototypes": prototypes,
            "returns": returns,
            "member_map": _value_member_map({"records": records, "typedefs": typedefs}),
        }
        _VALUE_VIEWS = _value_views()
    sites = _value_sites()
    sites.sort(key=lambda site: (site.file, site.line, site.literal))
    if args.jsonl:
        for site in sites:
            print(
                json.dumps(
                    {
                        "file": site.file,
                        "line": site.line,
                        "literal": site.literal,
                        "role": site.role,
                        "family": site.family,
                        "constant": site.constant,
                        "form": site.form,
                        "confidence": site.confidence,
                    },
                    ensure_ascii=False,
                )
            )
        return 0
    by_role = collections.Counter(site.role for site in sites)
    by_family = collections.Counter(site.family for site in sites if site.family)
    by_confidence = collections.Counter(site.confidence for site in sites)
    by_subsystem = collections.Counter(_value_subsystem(site.file) for site in sites)
    print(f"{len(sites)} sites")
    for title, counter in (
        ("role", by_role),
        ("family", by_family),
        ("confidence", by_confidence),
        ("subsystem", by_subsystem),
    ):
        print(f"\n{title}")
        for key, count in counter.most_common():
            print(f"{count}\t{key}")
    return 0


def _value_subsystem(path: str) -> str:
    """Return the overlay or engine group a source belongs to."""
    parts = path.split("/")
    if len(parts) > 3 and parts[1] == "overlays":
        return parts[2]
    if len(parts) > 3 and parts[1] == "engine":
        return parts[2]
    return parts[0]


# --- Call-graph layers ----------------------------------------------------------------------

LAYER_RESIDENT = RESIDENT
FUNC_ADDRESS_NAME = re.compile(r"func_[0-9A-F]{8}$")
NON_MATCHING_DEF = re.compile(r"\bNON_MATCHING\b")
HAND_ASM_DEF = re.compile(r"\bHAND_ASM\s*\(\s*(\w+)\s*\)")
JAL = re.compile(r"\bjal\s+([A-Za-z_]\w*)")
JALR = re.compile(r"\bjalr\b")
DISPATCH_CALL = re.compile(r"SYS_DISPATCH_(?:BYTE|TASK)\(\s*\(*\s*([A-Za-z_]\w*)")
ARRAY_CALL = re.compile(r"\b([A-Za-z_]\w*)\s*\[[^\]]*\]\s*\(")
TABLE_INIT = re.compile(r"\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*=\s*\{")


@dataclass
class LayerNode:
    """One function of one image, with its source and call-graph fields."""

    image: str
    name: str
    addr: int
    size: int
    sha1: str
    kind: str
    src: str | None
    status: str = "INCLUDE_ASM"
    shared: bool = False
    definition: object | None = None


def _layer_manifests() -> dict:
    from bof3.resolve import load_target_manifests

    manifests = load_target_manifests(ROOT)
    if not manifests:
        raise SystemExit("layers: no targets under config/")
    return manifests


def _index_nodes(manifests: dict) -> list[LayerNode] | None:
    """Return the built function index when every image is present, else None."""
    from bof3.source.index import load_index

    elfs = list((ROOT / "build/meson").glob("*.elf"))
    if len(elfs) < len(manifests):
        return None
    try:
        funcs = load_index(ROOT)
    except SystemExit:
        return None
    return [
        LayerNode(
            func.image,
            func.name,
            func.addr,
            func.size,
            func.sha1,
            "C" if func.status == "C" else "ASM",
            func.src,
        )
        for func in funcs
        if func.status != "LIB"
    ]


def _splat_nodes(manifests: dict) -> list[LayerNode]:
    """Return every split function without a build, with its bytes hashed for copies."""
    from bof3.resolve.layout import parse_splat_layout

    nodes = []
    seen = set()
    for image, manifest in manifests.items():
        layout = parse_splat_layout(ROOT / manifest.splat, manifest.load_address)
        payload_path = ROOT / manifest.binary
        try:
            payload = payload_path.read_bytes()
        except OSError:
            payload = b""
        for boundary in layout.boundaries:
            if not boundary.is_function or not boundary.name:
                continue
            key = (image, boundary.name, boundary.virtual_start)
            if key in seen:
                continue
            seen.add(key)
            start = boundary.file_start
            end = boundary.file_end if boundary.file_end is not None else len(payload)
            body = payload[start:end] if payload and end > start else b""
            size = (
                boundary.virtual_end - boundary.virtual_start
                if boundary.virtual_end is not None
                else len(body)
            )
            nodes.append(
                LayerNode(
                    image,
                    boundary.name,
                    boundary.virtual_start,
                    size,
                    hashlib.sha1(body).hexdigest()[:16] if body else "",
                    "C" if boundary.kind == "c" else "ASM",
                    None,
                )
            )
    return nodes


def _layer_tree():
    """Read every tracked C file once for definitions, calls and data initializers."""
    from bof3.source import decls

    texts = {name: ctext.read(ROOT, name) for name in ctext.tracked_c(ROOT)}
    return decls.Tree(texts=texts)


def _visible_files(tree, manifest) -> set[str]:
    folder = manifest.source_dir
    visible: set[str] = set()
    for name in tree.texts:
        if name.startswith(folder + "/") and name.endswith(".c"):
            visible.update(tree.closure(name))
    return visible


def _defs_by_file(tree) -> dict[str, list]:
    by_file: dict[str, list] = collections.defaultdict(list)
    for decls in tree.decls.values():
        for decl in decls:
            if decl.kind == "def":
                by_file[decl.file].append(decl)
    for decls in by_file.values():
        decls.sort(key=lambda decl: decl.line)
    return by_file


def _body_range(tree, by_file: dict[str, list], definition) -> tuple[int, int]:
    lines = tree.stripped.get(definition.file, "").split("\n")
    end = len(lines)
    for later in by_file.get(definition.file, ()):
        if later.line > definition.line:
            end = later.line - 1
            break
    return definition.line, end


def _asm_path(image: str, name: str) -> Path | None:
    for folder in (ROOT / "asm" / image, ROOT / "asm" / image / "hand"):
        path = folder / f"{name}.s"
        if path.is_file():
            return path
    return None


def _prepare_nodes(nodes: list[LayerNode], manifests: dict, tree) -> None:
    """Fill each node's status, shared flag and defining declaration."""
    visible_by_image: dict[str, set[str]] = {}
    for node in nodes:
        manifest = manifests.get(node.image)
        if manifest is None:
            continue
        if node.image not in visible_by_image:
            visible_by_image[node.image] = _visible_files(tree, manifest)
        visible = visible_by_image[node.image]
        definitions = [
            decl
            for decl in tree.decls.get(node.name, ())
            if decl.kind == "def" and decl.file in visible
        ]
        chosen = next(
            (decl for decl in definitions if decl.file.endswith(".h")),
            definitions[0] if definitions else None,
        )
        node.definition = chosen
        if chosen is not None:
            raw = tree.texts[chosen.file].splitlines()
            window = "\n".join(raw[max(0, chosen.line - 3) : chosen.line])
            node.status = "NON_MATCHING" if NON_MATCHING_DEF.search(window) else "MATCH"
            node.shared = chosen.file.endswith(".h")
        else:
            node.status = "INCLUDE_ASM"
        if node.status != "MATCH" and node.src is None:
            node.src = next(
                (
                    name
                    for name in tree.texts
                    if name.startswith(manifest.source_dir + "/")
                    and name.endswith(".c")
                    and re.search(
                        r"INCLUDE_ASM\s*\(\s*" + re.escape(node.name) + r"\s*\)",
                        tree.texts[name],
                    )
                ),
                None,
            )


def _table_initializers(text: str, known: set[str]):
    """Yield ``(table name, entries)`` for each top-level initializer of function names."""
    depth_at = [0] * len(text)
    depth = 0
    for index, char in enumerate(text):
        depth_at[index] = depth
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
    for match in TABLE_INIT.finditer(text):
        if depth_at[match.start()] != 0:
            continue
        opening = match.end() - 1
        closing = _match_brace(text, opening)
        if closing < 0:
            continue
        entries: list[str] = []
        for ident in IDENT.findall(text[opening + 1 : closing]):
            if ident in known and ident not in entries:
                entries.append(ident)
        if entries:
            yield match.group(1), entries


def _layer_tables(tree, known: set[str], manifests: dict) -> tuple[dict, set[str]]:
    """Return ``(image, table name) -> function names`` and every table name."""
    folders = sorted(
        ((manifest.source_dir, image) for image, manifest in manifests.items()),
        key=lambda pair: -len(pair[0]),
    )

    def image_of(name: str) -> str | None:
        for folder, image in folders:
            if name.startswith(folder + "/"):
                return image
        return None

    tables: dict[tuple[str, str], list[str]] = {}
    names: set[str] = set()
    for name, text in tree.stripped.items():
        if not name.startswith("src/") or not name.endswith(".c"):
            continue
        image = image_of(name)
        if image is None:
            continue
        for table, entries in _table_initializers(text, known):
            tables[(image, table)] = entries
            names.add(table)
    return tables, names


def _table_entries(tables: dict, image: str, name: str) -> list[str]:
    for candidate in (image, *LAYER_RESIDENT):
        if (candidate, name) in tables:
            return tables[(candidate, name)]
    found = [entries for (_, table), entries in tables.items() if table == name]
    return found[0] if len(found) == 1 else []


def _indirect_bases(text: str) -> set[str]:
    bases = set(DISPATCH_CALL.findall(text))
    bases.update(ARRAY_CALL.findall(text))
    return bases


def _local_tables(text: str, known: set[str]) -> dict[str, list[str]]:
    """Return the function tables a body builds on its stack or in a local."""
    tables: dict[str, list[str]] = {}
    for match in TABLE_INIT.finditer(text):
        opening = match.end() - 1
        closing = _match_brace(text, opening)
        if closing < 0:
            continue
        entries: list[str] = []
        for ident in IDENT.findall(text[opening + 1 : closing]):
            if ident in known and ident not in entries:
                entries.append(ident)
        if entries:
            tables[match.group(1)] = entries
    return tables


def _table_targets(
    text: str,
    image: str,
    table_names: set[str],
    local: dict[str, list[str]],
    resolve_table,
) -> list[str]:
    bases = _indirect_bases(text)
    if not bases:
        return []
    referenced = set(IDENT.findall(text)) & table_names
    targets: list[str] = []
    for base in sorted(bases):
        if base in local:
            targets.extend(local[base])
            continue
        entries = resolve_table(image, base)
        if entries:
            targets.extend(entries)
            continue
        for table in sorted(referenced):
            targets.extend(resolve_table(image, table))
    return targets


def _asm_table_targets(
    text: str, image: str, table_names: set[str], resolve_table
) -> list[str]:
    if not JALR.search(text):
        return []
    targets: list[str] = []
    for table in sorted(set(IDENT.findall(text)) & table_names):
        targets.extend(resolve_table(image, table))
    return targets


def _call_names(
    node: LayerNode,
    tree,
    by_file: dict[str, list],
    calls_by_file: dict[str, list],
    table_names: set[str],
    known: set[str],
    resolve_table,
) -> list[str]:
    """Return the game names a function calls, directly and through function tables."""
    names: list[str] = []
    if node.status == "MATCH" and node.definition is not None:
        start, end = _body_range(tree, by_file, node.definition)
        names.extend(
            call.name
            for call in calls_by_file.get(node.definition.file, ())
            if start <= call.line <= end
        )
        body = "\n".join(
            tree.stripped[node.definition.file].split("\n")[start - 1 : end]
        )
        names.extend(
            _table_targets(
                body,
                node.image,
                table_names,
                _local_tables(body, known),
                resolve_table,
            )
        )
        return names
    path = _asm_path(node.image, node.name)
    if path is None:
        if node.definition is not None:
            start, end = _body_range(tree, by_file, node.definition)
            names.extend(
                call.name
                for call in calls_by_file.get(node.definition.file, ())
                if start <= call.line <= end
            )
        return names
    text = path.read_text(encoding="utf-8", errors="replace")
    names.extend(JAL.findall(text))
    names.extend(_asm_table_targets(text, node.image, table_names, resolve_table))
    return names


def _layer_layouts(manifests: dict) -> tuple[dict, dict]:
    """Return each target's reviewed layout and retail payload."""
    from bof3.resolve.layout import parse_splat_layout

    layouts = {}
    payloads = {}
    for image, manifest in manifests.items():
        layouts[image] = parse_splat_layout(
            ROOT / manifest.splat, manifest.load_address
        )
        try:
            payloads[image] = (ROOT / manifest.binary).read_bytes()
        except OSError:
            payloads[image] = b""
    return layouts, payloads


def _looks_like_table(row: dict) -> bool:
    if row.get("alias"):
        return False
    ctype = str(row.get("type", ""))
    source = str(row.get("source", "")).lower()
    return (
        "Callback" in ctype
        or "Func" in ctype
        or "Steps" in ctype
        or any(
            word in source
            for word in ("handler", "step", "table", "callback", "dispatch", "function")
        )
    )


def _retail_table_entries(
    image: str,
    name: str,
    symbols: dict,
    layouts: dict,
    payloads: dict,
    by_address: dict[int, list[LayerNode]],
) -> list[str]:
    """Read a function table from the retail bytes of the image that defines it."""
    table_image = image
    row = symbols.get(image, {}).get(name)
    if row is None:
        for resident in LAYER_RESIDENT:
            row = symbols.get(resident, {}).get(name)
            if row is not None:
                table_image = resident
                break
    if not isinstance(row, dict) or "addr" not in row:
        return []
    layout = layouts.get(table_image)
    payload = payloads.get(table_image, b"")
    if layout is None or not payload:
        return []
    address = int(row["addr"])
    span = row.get("size")
    if span is None:
        for boundary in layout.boundaries:
            if boundary.virtual_start <= address < (boundary.virtual_end or 0):
                span = (boundary.virtual_end or address + 0x400) - address
                break
    if span is None:
        span = 0x400
    offset = address - layout.image_base
    data = payload[offset : offset + span]
    names: list[str] = []
    for index in range(0, len(data) - 3, 4):
        word = int.from_bytes(data[index : index + 4], "little")
        if word == 0:
            continue
        candidates = by_address.get(word, ())
        same = [node for node in candidates if node.image == table_image]
        resident = [node for node in candidates if node.image in LAYER_RESIDENT]
        for node in same or resident or candidates:
            if node.name not in names:
                names.append(node.name)
    return names


def assign_layers(count: int, edges: list[set[int]]) -> list[int]:
    """Return each node's layer: 0 when it calls no game function, else 1 + its deepest callee.

    A cycle is one strongly connected component and shares one layer.
    """
    adjacency = [list(targets) for targets in edges]
    reverse: list[set[int]] = [set() for _ in range(count)]
    for source, targets in enumerate(edges):
        for target in targets:
            reverse[target].add(source)
    seen = [False] * count
    finished: list[int] = []
    for start in range(count):
        if seen[start]:
            continue
        seen[start] = True
        stack = [(start, 0)]
        while stack:
            node, index = stack[-1]
            if index < len(adjacency[node]):
                target = adjacency[node][index]
                stack[-1] = (node, index + 1)
                if not seen[target]:
                    seen[target] = True
                    stack.append((target, 0))
            else:
                finished.append(node)
                stack.pop()
    component = [-1] * count
    components = 0
    for start in reversed(finished):
        if component[start] != -1:
            continue
        component[start] = components
        stack = [start]
        while stack:
            node = stack.pop()
            for target in reverse[node]:
                if component[target] == -1:
                    component[target] = components
                    stack.append(target)
        components += 1
    component_edges: list[set[int]] = [set() for _ in range(components)]
    for source, targets in enumerate(edges):
        for target in targets:
            if component[source] != component[target]:
                component_edges[component[source]].add(component[target])
    incoming = [0] * components
    for targets in component_edges:
        for target in targets:
            incoming[target] += 1
    order = [index for index in range(components) if incoming[index] == 0]
    topological: list[int] = []
    while order:
        node = order.pop()
        topological.append(node)
        for target in component_edges[node]:
            incoming[target] -= 1
            if incoming[target] == 0:
                order.append(target)
    layers = [0] * components
    for node in reversed(topological):
        layers[node] = (
            0
            if not component_edges[node]
            else 1 + max(layers[target] for target in component_edges[node])
        )
    return [layers[component[node]] for node in range(count)]


def layers(args: argparse.Namespace) -> int:
    """Print the call-graph layer of every function of every image."""
    manifests = _layer_manifests()
    index_nodes = _index_nodes(manifests)
    if index_nodes is None:
        print(
            "symbol: no complete built image index; reading the split layouts by unit",
            file=sys.stderr,
        )
        nodes = _splat_nodes(manifests)
    else:
        nodes = index_nodes
    if not nodes:
        raise SystemExit("layers: no functions found")
    nodes.sort(key=lambda node: (node.image, node.addr, node.name))
    tree = _layer_tree()
    _prepare_nodes(nodes, manifests, tree)
    by_file = _defs_by_file(tree)
    calls_by_file: dict[str, list] = collections.defaultdict(list)
    for call in tree.calls:
        calls_by_file[call.file].append(call)
    known = {node.name for node in nodes}
    tables, table_names = _layer_tables(tree, known, manifests)
    symbols = symbol_tables()
    for rows in symbols.values():
        for name, row in rows.items():
            if isinstance(row, dict) and _looks_like_table(row):
                table_names.add(name)
    layouts, payloads = _layer_layouts(manifests)
    by_image: dict[str, dict[str, int]] = collections.defaultdict(dict)
    by_name: dict[str, list[int]] = collections.defaultdict(list)
    by_address: dict[int, list[LayerNode]] = collections.defaultdict(list)
    for index, node in enumerate(nodes):
        by_image[node.image][node.name] = index
        by_name[node.name].append(index)
        by_address[node.addr].append(node)
    table_cache: dict[tuple[str, str], list[str]] = {}

    def resolve_table(image: str, name: str) -> list[str]:
        key = (image, name)
        if key in table_cache:
            return table_cache[key]
        found = _table_entries(tables, image, name)
        if not found:
            found = _retail_table_entries(
                image, name, symbols, layouts, payloads, by_address
            )
        table_cache[key] = found
        return found

    edges = [set() for _ in nodes]
    for index, node in enumerate(nodes):
        for name in set(
            _call_names(
                node,
                tree,
                by_file,
                calls_by_file,
                table_names,
                known,
                resolve_table,
            )
        ):
            for resident in (node.image, *LAYER_RESIDENT):
                target = by_image.get(resident, {}).get(name)
                if target is not None:
                    edges[index].add(target)
                    break
            else:
                for target in by_name.get(name, ()):
                    edges[index].add(target)
    callers = [0] * len(nodes)
    for targets in edges:
        for target in targets:
            callers[target] += 1
    levels = assign_layers(len(nodes), edges)
    groups: dict[str, set[str]] = collections.defaultdict(set)
    for node in nodes:
        if node.sha1:
            groups[node.sha1].add(node.image)
    rows = []
    for index, node in enumerate(nodes):
        rows.append(
            {
                "image": node.image,
                "name": node.name,
                "address": f"0x{node.addr:08X}",
                "layer": levels[index],
                "callers": callers[index],
                "callees": sorted({nodes[target].name for target in edges[index]}),
                "status": node.status,
                "named": not FUNC_ADDRESS_NAME.match(node.name),
                "copies": len(groups[node.sha1]) if node.sha1 else 1,
                "shared": node.shared,
            }
        )
    rows.sort(key=lambda row: (row["layer"], row["image"], row["name"]))
    keys = [
        "image",
        "name",
        "address",
        "layer",
        "callers",
        "callees",
        "status",
        "named",
        "copies",
        "shared",
    ]
    if args.jsonl:
        for row in rows:
            print(json.dumps({key: row[key] for key in keys}, ensure_ascii=False))
        return 0
    print("\t".join(keys))
    for row in rows:
        print(
            "\t".join(
                str(row[key]) if key != "callees" else ",".join(row[key])
                for key in keys
            )
        )
    return 0


# --- Record accesses ------------------------------------------------------------------------

MIPS_READ = {
    "lb": (1, True),
    "lbu": (1, False),
    "lh": (2, True),
    "lhu": (2, False),
    "lw": (4, None),
}
MIPS_WRITE = {"sb": 1, "sh": 2, "sw": 4}
MIPS_READ_OPS = {0x20, 0x21, 0x23, 0x24, 0x25}
MIPS_WRITE_OPS = {0x28, 0x29, 0x2B}
MIPS_OPCODES = {
    0x08: "addi",
    0x09: "addiu",
    0x0A: "slti",
    0x0B: "sltiu",
    0x0C: "andi",
    0x0D: "ori",
    0x0F: "lui",
    0x20: "lb",
    0x21: "lh",
    0x23: "lw",
    0x24: "lbu",
    0x25: "lhu",
    0x28: "sb",
    0x29: "sh",
    0x2B: "sw",
    0x04: "beq",
    0x05: "bne",
    0x03: "jal",
}
REG_NAMES = [
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
]  # fmt: skip
CALLER_SAVED = set(range(1, 16)) | {24, 25}


@dataclass(frozen=True)
class AccessRange:
    """A global object an instruction can address: its extent, name and record type."""

    start: int
    end: int
    name: str
    type_name: str | None


@dataclass
class MipsAccess:
    """One load or store that lands in a target object or a traced pointer."""

    image: str
    function: str
    offset: int
    width: int
    mnemonic: str
    write: bool
    signed: bool | None
    instruction: str
    global_name: str | None = None
    type_name: str | None = None
    constant: int | None = None
    slot: str | None = None


def _signed16(value: int) -> int:
    return value - 0x10000 if value & 0x8000 else value


def _signed32(value: int) -> int:
    return value - 0x100000000 if value & 0x80000000 else value


def _reg_name(number: int) -> str:
    return REG_NAMES[number] if 0 <= number < len(REG_NAMES) else f"r{number}"


def _offset_text(offset: int) -> str:
    return f"-0x{-offset:x}" if offset < 0 else f"0x{offset:x}"


def _instruction(word: int, call_name: str | None = None) -> str:
    op = word >> 26
    rs = (word >> 21) & 31
    rt = (word >> 16) & 31
    rd = (word >> 11) & 31
    imm = word & 0xFFFF
    funct = word & 63
    name = MIPS_OPCODES.get(op)
    if op == 0:
        if funct in (0x20, 0x21):
            return f"{'add' if funct == 0x20 else 'addu'} {_reg_name(rd)}, {_reg_name(rs)}, {_reg_name(rt)}"
        if funct == 0x08:
            return f"jr {_reg_name(rs)}"
        if funct == 0x09:
            return f"jalr {_reg_name(rs)}"
        return f"0x{word:08x}"
    if name == "lui":
        return f"lui {_reg_name(rt)}, 0x{imm:x}"
    if name in MIPS_READ or name in MIPS_WRITE:
        return (
            f"{name} {_reg_name(rt)}, {_offset_text(_signed16(imm))}({_reg_name(rs)})"
        )
    if name == "jal":
        return f"jal {call_name or f'0x{word & 0x03FFFFFF:08x}'}"
    if name in ("addi", "addiu", "slti", "sltiu"):
        return (
            f"{name} {_reg_name(rt)}, {_reg_name(rs)}, {_offset_text(_signed16(imm))}"
        )
    if name in ("andi", "ori"):
        return f"{name} {_reg_name(rt)}, {_reg_name(rs)}, 0x{imm:x}"
    if name in ("beq", "bne"):
        return (
            f"{name} {_reg_name(rs)}, {_reg_name(rt)}, {_offset_text(_signed16(imm))}"
        )
    return f"0x{word:08x}"


def _range_at(
    ranges: list[AccessRange], starts: list[int], address: int
) -> AccessRange | None:
    index = bisect.bisect_right(starts, address) - 1
    if index >= 0:
        found = ranges[index]
        if address < found.end:
            return found
    return None


def decode_accesses(
    image: str,
    function: str,
    address: int,
    words: tuple[int, ...],
    ranges: list[AccessRange],
    pointer_cells: dict[int, str],
    function_names: dict[int, str],
) -> tuple[list[MipsAccess], int, int]:
    """Decode one function: the accesses it makes into ranges or traced pointer types.

    Returns the accesses, the number of traced memory operations, and the number of
    base-register operations whose base could not be followed.
    """
    starts = [item.start for item in ranges]
    registers: dict[int, object] = {}
    loaded: dict[int, int] = {}
    moves: dict[int, tuple[int, int]] = {}
    accesses: list[MipsAccess] = []
    traced = 0
    untraced = 0
    for index, word in enumerate(words):
        op = word >> 26
        rs = (word >> 21) & 31
        rt = (word >> 16) & 31
        rd = (word >> 11) & 31
        imm = word & 0xFFFF
        simm = _signed16(imm)
        funct = word & 63
        pc = address + index * 4
        if op == 0x0F:
            registers[rt] = imm << 16
            loaded.pop(rt, None)
            moves.pop(rt, None)
            continue
        if op == 0x09:
            base = registers.get(rs)
            if isinstance(base, int):
                registers[rt] = base + simm
            elif isinstance(base, tuple):
                registers[rt] = (base[0], base[1] + simm)
            elif rs == 0:
                registers[rt] = simm
            else:
                registers.pop(rt, None)
            loaded.pop(rt, None)
            moves.pop(rt, None)
            continue
        if op == 0x0D:
            base = registers.get(rs)
            if isinstance(base, int):
                registers[rt] = base | imm
            elif rs == 0:
                registers[rt] = imm
            else:
                registers.pop(rt, None)
            loaded.pop(rt, None)
            moves.pop(rt, None)
            continue
        if op in (0x0A, 0x0B, 0x0C):
            if rs in loaded:
                access = accesses[loaded[rs]]
                if access.constant is None:
                    access.constant = simm if op in (0x0A, 0x0B) else imm
            registers.pop(rt, None)
            loaded.pop(rt, None)
            continue
        if op == 0:
            if funct in (0x20, 0x21):
                first = registers.get(rs)
                second = registers.get(rt)
                if rs == 0:
                    value = second
                elif rt == 0:
                    value = first
                else:
                    value = None
                if value is None:
                    registers.pop(rd, None)
                else:
                    registers[rd] = value
                loaded.pop(rd, None)
                if rd in (4, 5, 6, 7) and (rs == 0 or rt == 0):
                    moves[rd] = (rt if rs == 0 else rs, index)
                continue
            if funct == 0x08 and rs == 31:
                break
            if funct == 0x09:
                _attach_slots(accesses, moves, loaded, index, "jalr")
                _after_call(registers, loaded, moves)
                continue
            continue
        if op in (0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B):
            mnemonic = MIPS_OPCODES[op]
            base = registers.get(rs)
            found: AccessRange | None = None
            access: MipsAccess | None = None
            address_value = 0
            if isinstance(base, int):
                address_value = base + simm
                found = _range_at(ranges, starts, address_value)
                if found is not None:
                    traced += 1
                    access = MipsAccess(
                        image,
                        function,
                        address_value - found.start,
                        4,
                        mnemonic,
                        op in MIPS_WRITE_OPS,
                        None,
                        _instruction(word),
                        found.name,
                        found.type_name,
                    )
            elif isinstance(base, tuple):
                type_name, base_offset = base
                traced += 1
                access = MipsAccess(
                    image,
                    function,
                    base_offset + simm,
                    4,
                    mnemonic,
                    op in MIPS_WRITE_OPS,
                    None,
                    _instruction(word),
                    None,
                    type_name,
                )
            elif rs not in (29, 30):
                untraced += 1
            if access is not None:
                if mnemonic in MIPS_READ:
                    access.width, access.signed = MIPS_READ[mnemonic]
                else:
                    access.width = MIPS_WRITE[mnemonic]
                if access.write and isinstance(registers.get(rt), int):
                    access.constant = registers[rt]
                accesses.append(access)
                if not access.write:
                    loaded[rt] = len(accesses) - 1
                elif rt in loaded:
                    loaded.pop(rt, None)
            else:
                loaded.pop(rt, None)
            if isinstance(base, int) and address_value in pointer_cells:
                registers[rt] = (pointer_cells[address_value], 0)
            else:
                registers.pop(rt, None)
            continue
        if op == 0x03:
            target = ((word & 0x03FFFFFF) << 2) | (pc & 0xF0000000)
            name = function_names.get(target)
            _attach_slots(accesses, moves, loaded, index, name or f"0x{target:08X}")
            registers[31] = None
            _after_call(registers, loaded, moves)
            continue
        if op in (0x04, 0x05):
            if rs == 0 or rt == 0:
                other = rt if rs == 0 else rs
                if other in loaded:
                    access = accesses[loaded[other]]
                    if access.constant is None:
                        access.constant = 0
            else:
                first, second = registers.get(rs), registers.get(rt)
                if isinstance(first, int) and rt in loaded:
                    accesses[loaded[rt]].constant = first
                elif isinstance(second, int) and rs in loaded:
                    accesses[loaded[rs]].constant = second
            continue
    return accesses, traced, untraced


def _attach_slots(
    accesses: list[MipsAccess],
    moves: dict[int, tuple[int, int]],
    loaded: dict[int, int],
    index: int,
    callee: str,
) -> None:
    for slot, (source, position) in moves.items():
        if index - position > 4 or source not in loaded:
            continue
        access = accesses[loaded[source]]
        label = f"{callee}[{_reg_name(slot)}]"
        if access.slot is None:
            access.slot = label
        elif label not in access.slot.split(","):
            access.slot += "," + label


def _after_call(
    registers: dict[int, object],
    loaded: dict[int, int],
    moves: dict[int, tuple[int, int]],
) -> None:
    for reg in list(registers):
        if reg in CALLER_SAVED or isinstance(registers[reg], tuple):
            registers.pop(reg, None)
    for reg in list(loaded):
        if reg in CALLER_SAVED:
            loaded.pop(reg, None)
    moves.clear()


def _normalized_type(value: str) -> str:
    return " ".join(value.replace("*", " * ").split())


def _pointer_target(value: str) -> str | None:
    text = _normalized_type(value)
    return text[:-2].strip() if text.endswith(" *") else None


def _task_types() -> dict[str, str]:
    """Return image -> the record type its g_Task macro reads the scratchpad cell as.

    A family header (``src/overlays/battle/battle.h``) casts the cell for every image under
    its folder; an image header is more specific and wins.
    """
    pattern = re.compile(
        r"#\s*define\s+g_Task\s+\(\(\s*(?:volatile\s+)?(\w+)\s*\*\s*\)\s*g_Task\s*\)"
    )
    headers = []
    for path in (ROOT / "src").rglob("*.h"):
        text = path.read_text(encoding="utf-8", errors="replace")
        match = pattern.search(text)
        if match is not None:
            headers.append((path.parent.relative_to(ROOT).as_posix(), match.group(1)))
    found: dict[str, str] = {}
    for image, manifest in _layer_manifests().items():
        folder = manifest.source_dir
        best: tuple[int, str] | None = None
        for parent, type_name in headers:
            if folder == parent or folder.startswith(parent + "/"):
                if best is None or len(parent) > best[0]:
                    best = (len(parent), type_name)
        if best is not None:
            found[image] = best[1]
    return found


def _c_member_uses(names: set[str]) -> dict[str, list[tuple[str, int, str]]]:
    """Return one entry per ``.member``/``->member`` use of the names, comments masked."""
    pattern = re.compile(r"(?:->|\.)\s*(\w+)")
    found: dict[str, list[tuple[str, int, str]]] = collections.defaultdict(list)
    if not names:
        return found
    for path in ctext.tracked_c(ROOT):
        if path.startswith("include/psyq/"):
            continue
        text = ctext.read(ROOT, path)
        masked = ctext.mask(text)
        for number, line in enumerate(masked.split("\n"), 1):
            for match in pattern.finditer(line):
                if match.group(1) in names:
                    raw = text.split("\n")[number - 1]
                    found[match.group(1)].append((path, number, raw))
    return found


def _member_constants(line: str, member: str) -> list[int]:
    """Return the numeric constants a C line compares with or assigns to a member."""
    token = r"(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\b"
    escaped = re.escape(member)
    patterns = (
        rf"\b{escaped}\b\s*(?:==|!=|<=|>=|<|>|&|\||\^|=)\s*{token}",
        rf"{token}\s*(?:==|!=|<=|>=|<|>|&|\||\^|=)\s*\b{escaped}\b",
    )
    out = []
    for pattern in patterns:
        for match in re.finditer(pattern, line):
            token = match.group(1)
            try:
                if token.lower().startswith("0x"):
                    value = int(token, 16)
                elif len(token) > 1 and token.startswith("0"):
                    value = int(token, 8)
                else:
                    value = int(token, 10)
            except ValueError:
                continue
            if value not in out:
                out.append(value)
    return out


def _aggregate_accesses(
    layout,
    accesses: list[MipsAccess],
    c_uses: dict[str, list[tuple[str, int, str]]],
) -> list[dict]:
    """Aggregate accesses by byte offset and attach the current member and problems."""
    rows: dict[int, dict] = {}

    def row(offset: int) -> dict:
        return rows.setdefault(
            offset,
            {
                "offset": offset,
                "widths": collections.Counter(),
                "reads": 0,
                "writes": 0,
                "examples": [],
                "constants": [],
                "slots": [],
            },
        )

    for access in accesses:
        item = row(access.offset)
        item["widths"][access.mnemonic] += 1
        item["reads"] += not access.write
        item["writes"] += access.write
        example = f"{access.image}@{access.function} {access.instruction}"
        if example not in item["examples"] and len(item["examples"]) < 5:
            item["examples"].append(example)
        if access.constant is not None and access.constant not in item["constants"]:
            item["constants"].append(access.constant)
        if access.slot and access.slot not in item["slots"]:
            item["slots"].append(access.slot)
    member_offsets = set()
    if layout is not None:
        for member in layout.members:
            member_offsets.add(member.offset)
            leaf = member.path.rsplit(".", 1)[-1]
            for path, number, line in c_uses.get(leaf, ()):
                item = row(member.offset)
                example = f"{path}:{number}"
                if example not in item["examples"] and len(item["examples"]) < 5:
                    item["examples"].append(example)
                for value in _member_constants(line, leaf):
                    if value not in item["constants"]:
                        item["constants"].append(value)
    for offset in member_offsets:
        row(offset)
    out = []
    for offset in sorted(rows):
        item = rows[offset]
        problems = []
        member = None
        member_type = None
        if layout is not None:
            found = locate(layout, offset)
            if found:
                path, _, ctype = found[0]
                member, member_type = path, ctype
            else:
                containing = [
                    entry
                    for entry in layout.members
                    if entry.offset <= offset < entry.offset + entry.size
                ]
                containing.sort(key=lambda entry: -entry.path.count("."))
                if containing:
                    member, member_type = containing[0].path, containing[0].ctype
            if member is None:
                problems.append("unknown member")
            elif member.rsplit(".", 1)[-1].startswith(("unk_", "pad_", "field_")):
                problems.append("unknown member")
        if not item["reads"] and not item["writes"]:
            problems.append("never accessed")
        for mnemonic in item["widths"]:
            width = MIPS_READ.get(mnemonic, (MIPS_WRITE.get(mnemonic, 4), None))[0]
            if offset + width > layout.size if layout is not None else False:
                problems.append("past the end")
            if layout is not None and member_type is not None:
                leaf_width = _known_width(member_type)
                if leaf_width is None:
                    found = [entry for entry in layout.members if entry.path == member]
                    leaf_width = found[0].size if found else None
                if leaf_width is not None and leaf_width != width:
                    problems.append("width differs")
                signed = MIPS_READ.get(mnemonic, (0, None))[1]
                if signed is not None and member_type:
                    base = _normalized_type(member_type)
                    if base in ("u8", "u16", "u32") and signed:
                        problems.append("signedness differs")
                    elif base in ("s8", "s16", "s32") and not signed:
                        problems.append("signedness differs")
            if layout is not None and offset + width <= layout.size:
                last = locate(layout, offset + width - 1)
                first = locate(layout, offset)
                if first and last and first[0][0] != last[0][0]:
                    problems.append("straddles members")
        item["member"] = member
        item["member_type"] = member_type
        item["problem"] = ", ".join(dict.fromkeys(problems))
        out.append(item)
    return out


def _index_by_image() -> dict[str, list]:
    """Return every indexed function grouped by image; accesses need the built images."""
    from bof3.source.index import load_index

    try:
        funcs = load_index(ROOT)
    except SystemExit:
        raise SystemExit(
            "accesses: no built images. Run: meson compile -C build/meson -j 4"
        ) from None
    groups: dict[str, list] = collections.defaultdict(list)
    for func in funcs:
        groups[func.image].append(func)
    return groups


def _row_extent(row: dict, layout) -> int:
    size = row.get("size")
    if size is not None:
        return int(size)
    if layout is not None:
        return layout.size
    text = _normalized_type(str(row.get("type", "")))
    if text.endswith(" *"):
        return 4
    width = SCALAR_WIDTH.get(text)
    if width is not None:
        return width
    return 0x100


def _visible_images(table: str, images: list[str]) -> list[str]:
    return images if table in LAYER_RESIDENT else [table]


def _scan_image(
    image: str,
    functions: dict[str, list],
    ranges: list[AccessRange],
    pointer_cells: dict[int, str],
    names: dict[int, str],
) -> tuple[list[MipsAccess], int, int]:
    found: list[MipsAccess] = []
    traced = 0
    untraced = 0
    for func in functions.get(image, ()):
        accesses, part_traced, part_untraced = decode_accesses(
            image,
            func.name,
            func.addr,
            func.words,
            ranges,
            pointer_cells,
            names,
        )
        found.extend(accesses)
        traced += part_traced
        untraced += part_untraced
    return found, traced, untraced


def _access_rows(
    name: str,
    layout,
    accesses: list[MipsAccess],
    c_uses: dict[str, list[tuple[str, int, str]]],
    kind: str,
) -> list[dict]:
    rows = _aggregate_accesses(layout, accesses, c_uses)
    for row in rows:
        row["name"] = name
        row["kind"] = kind
    return rows


def accesses(args: argparse.Namespace) -> int:
    """List the reads and writes of a record type or a global, per offset."""
    name = args.name
    data = symbol_tables()
    globals_found: list[tuple[str, dict]] = []
    for table, rows in data.items():
        row = rows.get(name)
        if isinstance(row, dict) and "addr" in row and not row.get("alias"):
            globals_found.append((table, row))
    functions = _index_by_image()
    images = sorted(functions)
    task_types = _task_types()
    all_accesses: list[MipsAccess] = []
    traced = 0
    untraced = 0
    layout = None
    c_uses: dict[str, list[tuple[str, int, str]]] = {}
    if globals_found:
        kind = "global"
        seen = set()
        for table, row in globals_found:
            if (table, int(row["addr"])) in seen:
                continue
            seen.add((table, int(row["addr"])))
            type_name = str(row.get("type", "")) or None
            row_layout = type_layout(type_name) if type_name else None
            if row_layout is not None and row_layout.record:
                layout = row_layout
            extent = _row_extent(row, row_layout)
            start = int(row["addr"])
            item_range = AccessRange(start, start + extent, name, type_name)
            for image in _visible_images(table, images):
                found, part_traced, part_untraced = _scan_image(
                    image,
                    functions,
                    [item_range],
                    {},
                    {func.addr: func.name for func in functions.get(image, ())},
                )
                all_accesses.extend(found)
                traced += part_traced
                untraced += part_untraced
        member_names = (
            {member.path.rsplit(".", 1)[-1] for member in layout.members}
            if layout is not None
            else set()
        )
        if member_names:
            all_uses = _c_member_uses(member_names)
            for member, uses in all_uses.items():
                kept = [
                    use
                    for use in uses
                    if re.search(
                        r"\b"
                        + re.escape(name)
                        + r"\s*(?:->|\.)\s*"
                        + re.escape(member)
                        + r"\b",
                        use[2],
                    )
                ]
                if kept:
                    c_uses[member] = kept
    else:
        kind = "type"
        layout = type_layout(name)
        if layout is None or not layout.record:
            raise SystemExit(f"symbol: {name} is neither a global nor a record type")
        direct_rows = [
            (table, row_name, row)
            for table, rows in data.items()
            for row_name, row in rows.items()
            if isinstance(row, dict)
            and "addr" in row
            and not row.get("alias")
            and _normalized_type(str(row.get("type", ""))) == _normalized_type(name)
        ]
        pointer_rows = [
            (table, row)
            for table, rows in data.items()
            for row_name, row in rows.items()
            if isinstance(row, dict)
            and "addr" in row
            and not row.get("alias")
            and _pointer_target(str(row.get("type", ""))) == _normalized_type(name)
        ]
        for table, row_name, row in direct_rows:
            start = int(row["addr"])
            item_range = AccessRange(
                start, start + _row_extent(row, layout), row_name, name
            )
            for image in _visible_images(table, images):
                found, part_traced, part_untraced = _scan_image(
                    image,
                    functions,
                    [item_range],
                    {},
                    {func.addr: func.name for func in functions.get(image, ())},
                )
                all_accesses.extend(found)
                traced += part_traced
                untraced += part_untraced
        for table, row in pointer_rows:
            cell = int(row["addr"])
            for image in _visible_images(table, images):
                found, part_traced, part_untraced = _scan_image(
                    image,
                    functions,
                    [],
                    {cell: name},
                    {func.addr: func.name for func in functions.get(image, ())},
                )
                all_accesses.extend(found)
                traced += part_traced
                untraced += part_untraced
        for image, task_type in task_types.items():
            if task_type == _normalized_type(name):
                found, part_traced, part_untraced = _scan_image(
                    image,
                    functions,
                    [],
                    {0x1F800044: name},
                    {func.addr: func.name for func in functions.get(image, ())},
                )
                all_accesses.extend(found)
                traced += part_traced
                untraced += part_untraced
        member_names = {member.path.rsplit(".", 1)[-1] for member in layout.members}
        c_uses = _c_member_uses(member_names)
        all_accesses = [access for access in all_accesses if access.type_name == name]
    rows = _access_rows(name, layout, all_accesses, c_uses, kind)
    if traced + untraced:
        share = 100.0 * traced / (traced + untraced)
        print(
            f"accesses: traced {traced} of {traced + untraced} memory operations "
            f"({share:.1f}%)",
            file=sys.stderr,
        )
    keys = [
        "name",
        "kind",
        "offset",
        "widths",
        "reads",
        "writes",
        "member",
        "member_type",
        "examples",
        "constants",
        "slots",
        "problem",
    ]
    if args.jsonl:
        for row in rows:
            item = {key: row[key] for key in keys}
            item["widths"] = dict(row["widths"])
            print(json.dumps(item, ensure_ascii=False))
        return 0
    print("\t".join(keys))
    for row in rows:
        widths = ",".join(
            f"{key}:{value}" for key, value in sorted(row["widths"].items())
        )
        print(
            "\t".join(
                [
                    row["name"],
                    row["kind"],
                    f"0x{row['offset']:X}",
                    widths,
                    str(row["reads"]),
                    str(row["writes"]),
                    row["member"] or "",
                    row["member_type"] or "",
                    "; ".join(row["examples"]),
                    ",".join(f"0x{value:X}" for value in row["constants"]),
                    ",".join(row["slots"]),
                    row["problem"],
                ]
            )
        )
    return 0


RECORD_HEAD = re.compile(r"(?m)\b(?:typedef\s+)?(?:struct|union)\s*(?:(\w+)\s*)?\{")
TYPEDEF_RECORD = re.compile(r"(?m)^\s*typedef\s+(?:struct|union)\s+(\w+)\s+(\w+)\s*;")


def _record_definitions() -> tuple[dict[str, int], dict[str, str], set[str]]:
    """Return each record name's definition count, its first header, and the record names."""
    counts: dict[str, int] = collections.Counter()
    header: dict[str, str] = {}
    names: set[str] = set()
    for path in ctext.tracked_c(ROOT):
        if not path.endswith(".h"):
            continue
        text = ctext.read(ROOT, path)
        masked = ctext.mask(text)
        for match in RECORD_HEAD.finditer(masked):
            opening = match.end() - 1
            closing = _match_brace(masked, opening)
            if closing < 0:
                continue
            tag = match.group(1) or ""
            tail = re.match(r"\s*(\w+)\s*;", masked[closing + 1 :])
            alias = tail.group(1) if tail else ""
            for name in {part for part in (tag, alias) if part}:
                counts[name] += 1
                header.setdefault(name, path)
                names.add(name)
        for match in TYPEDEF_RECORD.finditer(masked):
            name = match.group(2)
            counts[name] += 1
            header.setdefault(name, path)
            names.add(name)
    return dict(counts), header, names


def _record_members(layout) -> list:
    return list(layout.members)


def _record_globals(symbols: dict, names: set[str]) -> dict[str, int]:
    found: dict[str, int] = collections.Counter()
    for rows in symbols.values():
        for row in rows.values():
            if not isinstance(row, dict):
                continue
            text = _normalized_type(str(row.get("type", "")))
            if text in names:
                found[text] += 1
            else:
                target = _pointer_target(text)
                if target in names:
                    found[target] += 1
    return dict(found)


def _record_params(tree, names: set[str]) -> dict[str, int]:
    found: dict[str, int] = collections.Counter()
    for decls_list in tree.decls.values():
        for decl in decls_list:
            for ctype, _ in decl.params:
                for name in names:
                    if re.search(r"\b" + re.escape(name) + r"\b", ctype):
                        found[name] += 1
    return dict(found)


def _record_direct_accesses(
    names: set[str],
    layouts: dict,
    symbols: dict,
    functions: dict[str, list],
    images: list[str],
) -> dict[str, int]:
    """Decode every image once and count the direct accesses to each record's globals."""
    own: dict[str, list[AccessRange]] = collections.defaultdict(list)
    resident: list[AccessRange] = []
    for table, rows in symbols.items():
        for row_name, row in rows.items():
            if not isinstance(row, dict) or "addr" not in row or row.get("alias"):
                continue
            text = _normalized_type(str(row.get("type", "")))
            if text not in names:
                continue
            layout = layouts.get(text)
            start = int(row["addr"])
            item = AccessRange(start, start + _row_extent(row, layout), row_name, text)
            if table in LAYER_RESIDENT:
                resident.append(item)
            else:
                own[table].append(item)
    counts: dict[str, int] = collections.Counter()
    for image in images:
        ranges = own.get(image, []) + resident
        if not ranges:
            continue
        for func in functions.get(image, ()):
            found, _, _ = decode_accesses(
                image,
                func.name,
                func.addr,
                func.words,
                ranges,
                {},
                {},
            )
            for access in found:
                if access.type_name in names:
                    counts[access.type_name] += 1
    return dict(counts)


def records(args: argparse.Namespace) -> int:
    """Summarise every record: size, members, duplicates, globals, parameters and accesses."""
    counts, header, names = _record_definitions()
    layouts = {}
    for name in sorted(names):
        layout = type_layout(name)
        if layout is not None and layout.record:
            layouts[name] = layout
    symbols = symbol_tables()
    global_counts = _record_globals(symbols, set(layouts))
    tree = _layer_tree()
    param_counts = _record_params(tree, set(layouts))
    member_names = {
        member.path.rsplit(".", 1)[-1]
        for layout in layouts.values()
        for member in layout.members
    }
    c_uses = _c_member_uses(member_names)
    functions = _index_by_image()
    direct = _record_direct_accesses(
        set(layouts), layouts, symbols, functions, sorted(functions)
    )
    signatures: dict[tuple, list[str]] = collections.defaultdict(list)
    owners: dict[str, set[str]] = collections.defaultdict(set)
    for name, layout in layouts.items():
        signature = (layout.size, tuple((m.offset, m.ctype) for m in layout.members))
        signatures[signature].append(name)
        for member in layout.members:
            owners[member.path.rsplit(".", 1)[-1]].add(name)
    rows = []
    for name, layout in layouts.items():
        members = _record_members(layout)
        unknown = sum(
            1
            for member in members
            if member.path.rsplit(".", 1)[-1].startswith(("unk_", "pad_", "field_"))
        )
        c_count = sum(
            len(c_uses.get(member.path.rsplit(".", 1)[-1], ())) for member in members
        )
        signature = (layout.size, tuple((m.offset, m.ctype) for m in members))
        rows.append(
            {
                "record": name,
                "size": layout.size,
                "members": len(members),
                "unknown": unknown,
                "definitions": counts.get(name, 0),
                "same_layout": len(signatures[signature]) - 1,
                "globals": global_counts.get(name, 0),
                "params": param_counts.get(name, 0),
                "accesses": direct.get(name, 0) + c_count,
                "header": header.get(name, ""),
            }
        )
    rows.sort(
        key=lambda row: (
            -row["accesses"] * row["unknown"],
            -row["accesses"],
            row["record"],
        )
    )
    keys = [
        "record",
        "size",
        "members",
        "unknown",
        "definitions",
        "same_layout",
        "globals",
        "params",
        "accesses",
        "header",
    ]
    if args.jsonl:
        for row in rows:
            print(json.dumps({key: row[key] for key in keys}, ensure_ascii=False))
        return 0
    print("\t".join(keys))
    for row in rows:
        print("\t".join(str(row[key]) for key in keys))
    return 0


# --- Signatures, extents and homes from the split assembly -----------------------------------

ASM_ROOT = ROOT / "asm"
SYSTEM_FOLDERS = {
    "engine/slus": "Executable",
    "engine/game": "Game",
    "logo": "Logo",
    "shared": "Shared",
    "overlays/area": "Area",
    "overlays/battle": "Battle",
    "overlays/bmagic": "Battle magic",
    "overlays/boss": "Boss",
    "overlays/commu": "Fairy Village",
    "overlays/menu": "Menu",
    "overlays/plchar": "Player character",
    "overlays/scenario": "Scenario",
    "overlays/title": "Title",
}
ADDRESS_SYMBOL = re.compile(r"(?:func|unk|D|jtbl)_[0-9A-F]{8}$")
UNNAMED_PREFIXES = ("func_", "unk_", "D_", "jtbl_", "g_")


class SymbolIndex:
    """A row lookup over config/symbols.toml: by name, by address and per image."""

    def __init__(self, data: dict[str, dict[str, dict]]) -> None:
        self.rows: dict[str, list[Row]] = {}
        self.following: dict[str, dict[int, int]] = {}
        self.by_name: dict[str, list[Row]] = collections.defaultdict(list)
        for table in data:
            rows = table_rows(data, table)
            rows.sort(key=lambda row: (row.addr, row.name))
            self.rows[table] = rows
            self.following[table] = next_addresses(rows)
            for row in rows:
                self.by_name[row.name].append(row)
        self._visible: dict[str, dict[str, Row]] = {}
        self._spans: dict[tuple[str, int], int] = {}

    def span(self, row: Row) -> int:
        """Return a row's extent in bytes."""
        key = (row.table, row.addr)
        if key not in self._spans:
            self._spans[key] = row_span(row, self.following.get(row.table, {}))
        return self._spans[key]

    def visible(self, image: str) -> dict[str, Row]:
        """Return the rows an image can name: its own first, then the resident images."""
        found = self._visible.get(image)
        if found is None:
            found = {}
            for table in (image, *RESIDENT):
                for row in self.rows.get(table, ()):
                    found.setdefault(row.name, row)
            self._visible[image] = found
        return found

    def resolve(self, image: str, name: str) -> Row | None:
        """Return the row a name has in one image, else None."""
        return self.visible(image).get(name)

    def canonical(self, name: str, address: int) -> str:
        """Return the table that owns an address of a symbol."""
        candidates = [
            row.table for row in self.by_name.get(name, ()) if row.addr == address
        ]
        for table in RESIDENT:
            if table in candidates:
                return table
        for table in candidates:
            bounds = table_range(table)
            if bounds is not None and bounds[0] <= address < bounds[1]:
                return table
        return candidates[0] if candidates else ""

    def owner(self, image: str):
        """Return a function mapping an address to ``(table, name, offset)``."""
        rows = [row for row in self.visible(image).values() if row.type != "func"]
        rows.sort(key=lambda row: row.addr)
        starts = [row.addr for row in rows]
        spans = [self.span(row) for row in rows]

        def find(address: int):
            index = bisect.bisect_right(starts, address) - 1
            if index >= 0 and address < starts[index] + spans[index]:
                row = rows[index]
                return row.table, row.name, address - row.addr
            return None

        return find


@dataclass
class Assembly:
    """Every split function with its decoded facts, and the indexes the verbs share."""

    functions: dict[str, list]
    facts: dict[tuple[str, str], object]
    by_image: dict[str, dict[str, object]]
    by_name: dict[str, list]
    callers: dict[tuple[str, str], list] | None = None
    systems: frozenset[str] = frozenset()

    def resolve(self, image: str, name: str):
        """Return the function a name calls, else None when the name is ambiguous."""
        found = self.by_image.get(image, {}).get(name)
        if found is not None:
            return found
        for resident in RESIDENT:
            found = self.by_image.get(resident, {}).get(name)
            if found is not None:
                return found
        candidates = self.by_name.get(name, ())
        return candidates[0] if len(candidates) == 1 else None


_ASM_FUNCTIONS: dict[str, list] = {}
_ASSEMBLY: Assembly | None = None
_EXTENT_ROWS: list[dict] | None = None


def _asm_functions(image: str) -> list:
    """Return every split function of one image, read once per process."""
    if image in _ASM_FUNCTIONS:
        return _ASM_FUNCTIONS[image]
    found: list = []
    folder = ASM_ROOT / image
    if folder.is_dir():
        for path in sorted(folder.rglob("*.s")):
            if "data" in path.relative_to(folder).parts:
                continue
            try:
                text = path.read_text(encoding="utf-8", errors="replace")
            except OSError:
                continue
            found.extend(
                asmtext.functions(text, image, path.relative_to(ROOT).as_posix())
            )
    _ASM_FUNCTIONS[image] = found
    return found


def _assembly() -> Assembly:
    """Read every split function of every image and decode its facts, once per process."""
    global _ASSEMBLY
    if _ASSEMBLY is not None:
        return _ASSEMBLY
    manifests = _layer_manifests()
    index = SymbolIndex(symbol_tables())
    functions = {image: _asm_functions(image) for image in sorted(manifests)}
    facts: dict[tuple[str, str], object] = {}
    by_image: dict[str, dict[str, object]] = {}
    by_name: dict[str, list] = collections.defaultdict(list)
    for image, found in functions.items():
        visible = index.visible(image)
        symbols = {name: (row.table, row.addr) for name, row in visible.items()}
        owner = index.owner(image)
        by_image[image] = {function.name: function for function in found}
        for function in found:
            facts[(image, function.name)] = asmtext.decode(function, symbols, owner)
            by_name[function.name].append(function)
    systems = frozenset(
        system
        for functions in functions.values()
        for function in functions
        for system in (_name_system(function.name),)
        if system
    )
    _ASSEMBLY = Assembly(functions, facts, by_image, dict(by_name), systems=systems)
    return _ASSEMBLY


def _visible_sources(tree, manifests: dict) -> dict[str, set[str]]:
    """Return each image's visible C files."""
    return {
        image: _visible_files(tree, manifest) for image, manifest in manifests.items()
    }


def _declared_prototype(tree, name: str, visible: set[str]):
    """Return the prototype or definition a function's image sees, else any of them."""
    options = tree.decls.get(name) or []
    if not options:
        return None
    for kind in ("def", "proto"):
        for decl in options:
            if decl.kind == kind and decl.file in visible:
                return decl
    return options[0]


def _render_declared(name: str, decl) -> str | None:
    """Write one declaration as its readers see it."""
    if decl is None:
        return None
    if decl.unspecified:
        return f"{decl.ret} {name}()"
    params = ", ".join(f"{ctype} {param}".strip() for ctype, param in decl.params)
    return f"{decl.ret} {name}({params or 'void'})"


def _declared_kind(ctype: str) -> str:
    """Return the kind a declared C parameter states."""
    text = _normalized_type(re.sub(r"\bHAND_ASM\b", "", ctype))
    if text.endswith(" *"):
        return "pointer"
    if text == "bool":
        return "bool"
    return {
        "u8": "u8",
        "u_char": "u8",
        "unsigned char": "u8",
        "char": "s8",
        "s8": "s8",
        "u16": "u16",
        "u_short": "u16",
        "unsigned short": "u16",
        "s16": "s16",
        "short": "s16",
    }.get(text, "s32")


def _declared_return_kind(ret: str) -> str:
    """Return the kind a declared return type states."""
    text = _normalized_type(re.sub(r"\bHAND_ASM\b", "", ret))
    if text == "void":
        return "void"
    if text == "bool":
        return "bool"
    if text.endswith(" *"):
        return "pointer"
    return "value"


def _name_system(name: str) -> str | None:
    """Return the system a name's prefix states, else None for an address name."""
    stem = name
    for prefix in UNNAMED_PREFIXES:
        if stem.startswith(prefix):
            if ADDRESS_SYMBOL.match(stem):
                return None
            stem = stem[len(prefix) :]
            break
    head = stem.split("_", 1)[0]
    if not head or len(head) < 2 or not head[0].isupper():
        return None
    return head


def _symbol_system(name: str, systems: frozenset[str] | set[str]) -> str | None:
    """Return the system a global or record name starts with, from the names the code uses."""
    if ADDRESS_SYMBOL.match(name):
        return None
    stem = name[2:] if name.startswith(("g_",)) else name
    for system in sorted(systems, key=len, reverse=True):
        if not stem.startswith(system):
            continue
        if len(stem) == len(system) or stem[len(system)].isupper():
            return system
    return None


def _folder_system(source_dir: str) -> str:
    """Return the subsystem a source folder belongs to."""
    relative = source_dir[4:] if source_dir.startswith("src/") else source_dir
    for prefix, system in sorted(
        SYSTEM_FOLDERS.items(), key=lambda item: -len(item[0])
    ):
        if relative == prefix or relative.startswith(prefix + "/"):
            return system
    return "Other"


def _declared_extent(row: Row) -> int | None:
    """Return the byte extent a row's own declaration states."""
    if row.size is not None:
        return row.size
    text = _normalized_type(row.type)
    if text.endswith(" *"):
        return 4
    width = SCALAR_WIDTH.get(text)
    if width is not None:
        return width
    layout = type_layout(text) if text and text != "func" else None
    return layout.size if layout else None


def _symbol_uses(assembly: Assembly, index: SymbolIndex) -> dict[tuple[str, int], list]:
    """Group every symbol access by ``(name, address)``, from the images that can see it."""
    grouped: dict[tuple[str, int], list] = collections.defaultdict(list)
    for (image, function_name), facts in assembly.facts.items():
        for access in facts.accesses:
            if not access.name:
                continue
            row = index.resolve(image, access.name)
            if row is None:
                continue
            grouped[(access.name, row.addr)].append((image, function_name, access))
    return grouped


def _symbol_strides(assembly: Assembly) -> dict[str, set[int]]:
    """Group the index stride every function uses on a symbol, by symbol name."""
    grouped: dict[str, set[int]] = collections.defaultdict(set)
    for facts in assembly.facts.values():
        for key, values in facts.strides.items():
            grouped[key[-1]].update(values)
    return grouped


def _unique_data_rows(index: SymbolIndex) -> list[Row]:
    """Return each data and bss symbol once, preferring the resident table's declaration."""
    order = {
        table: position
        for position, table in enumerate(
            [*RESIDENT] + sorted(t for t in index.rows if t not in RESIDENT)
        )
    }
    seen: dict[tuple[str, int], Row] = {}
    for table in sorted(index.rows, key=lambda table: order.get(table, len(order))):
        for row in index.rows[table]:
            if row.type == "func":
                continue
            seen.setdefault((row.name, row.addr), row)
    return list(seen.values())


def _section_of(layout, address: int) -> str:
    """Return the section kind an address sits in for its target layout."""
    if layout is None:
        return "unknown"
    for boundary in layout.boundaries:
        if boundary.virtual_start <= address < (boundary.virtual_end or 0):
            return {
                ".data": "data",
                ".rodata": "rodata",
                ".bss": "bss",
            }.get(boundary.kind, "other")
    return "unknown"


def _extent_rows(assembly: Assembly, index: SymbolIndex, manifests: dict) -> list[dict]:
    """Build one extent row per data and bss symbol the images hold."""
    global _EXTENT_ROWS
    if _EXTENT_ROWS is not None:
        return _EXTENT_ROWS
    from bof3.resolve.layout import parse_splat_layout

    uses = _symbol_uses(assembly, index)
    strides = _symbol_strides(assembly)
    used_names = {name for (name, _address), found in uses.items() if found}
    universes: dict[str, list[int]] = {}
    ladders: dict[tuple[str, int], int] = {}
    for table, table_rows in index.rows.items():
        addresses = sorted({row.addr for row in table_rows if row.type != "func"})
        universes[table] = addresses
        for position, address in enumerate(addresses[:-1]):
            ladders[(table, address)] = addresses[position + 1]
    rows: list[dict] = []
    for row in _unique_data_rows(index):
        image = index.canonical(row.name, row.addr) or row.table
        manifest = manifests.get(image)
        layout = None
        if manifest is not None:
            try:
                layout = parse_splat_layout(
                    ROOT / manifest.splat, manifest.load_address
                )
            except (OSError, ValueError):
                layout = None
        following_address = ladders.get((row.table, row.addr))
        if following_address is not None:
            gap = following_address - row.addr
        else:
            addresses = universes.get(row.table, [])
            gap = addresses[-1] - row.addr if addresses else None
        declared = _declared_extent(row)
        found = uses.get((row.name, row.addr), [])
        beyond = [
            {
                "offset": f"0x{access.offset:X}",
                "width": access.width,
                "signed": access.signed,
                "mnemonic": access.mnemonic,
                "function": function,
                "address": f"0x{access.address:08X}",
            }
            for _image, function, access in found
            if declared is not None and access.offset >= declared
        ]
        item = {
            "symbol": row.name,
            "image": image,
            "address": f"0x{row.addr:08X}",
            "gap": gap,
            "declared_size": declared,
            "stride": sorted(strides.get(row.name, set())),
            "beyond": beyond[:20],
            "beyond_count": len(beyond),
            "absorbs": [],
            "section": _section_of(layout, row.addr),
            "type": row.type,
            "evidence": [
                f"{use_image}@0x{access.address:08X} {function} {access.mnemonic}"
                for use_image, function, access in found[:5]
            ],
        }
        start = row.addr
        end = start + (gap or 0)
        hit = {
            start + access.offset
            for _image, _function, access in uses.get((row.name, start), ())
        }
        for other in index.rows.get(row.table, ()):
            if other.type == "func" or not start < other.addr < end:
                continue
            if other.name == row.name or other.name in used_names:
                continue
            size = index.span(other)
            if any(other.addr <= address < other.addr + size for address in hit):
                item["absorbs"].append(other.name)
        rows.append(item)
    _EXTENT_ROWS = rows
    return rows


def _pointer_record(
    use, index: SymbolIndex, callers: list, position: int, declared
) -> str | None:
    """Return the record a pointer argument's accesses and callers support, else None."""
    accesses = [access for access in use.accesses if access.width]
    if not accesses:
        return None
    if (
        declared is not None
        and not declared.unspecified
        and position < len(declared.params)
    ):
        ctype = declared.params[position][0]
        text = _normalized_type(ctype)
        if text.endswith(" *") and "*" not in text[:-2]:
            record = text[:-2].strip()
            if _fits(record, accesses):
                return record
    for caller, call in callers:
        if 4 + position not in call.arguments:
            continue
        row = _argument_global(index, caller, call, position)
        if row is None:
            continue
        record = _record_type(row)
        if record and _fits(record, accesses):
            return record
    return None


def _argument_global(index: SymbolIndex, caller, call, position: int):
    """Return the global whose address one caller puts in one argument register, if any."""
    insns = caller.insns
    start = next(
        (number for number, insn in enumerate(insns) if insn.address == call.address),
        None,
    )
    if start is None:
        return None
    for number in range(start - 1, max(-1, start - 20), -1):
        insn = insns[number]
        if insn.mnemonic in ("jal", "jalr", "jr"):
            break
        ops = asmtext.operands(insn.operands)
        dest, _reads = asmtext.read_write(insn.mnemonic, ops)
        if dest != 4 + position or insn.mnemonic != "lui" or len(ops) < 2:
            continue
        named = asmtext.symbol(ops[1])
        if named is None:
            continue
        row = index.resolve(caller.image, named[0])
        if row is not None:
            return row
    return None


def _record_type(row: Row) -> str | None:
    """Return the record a global row is or points at, when its type names one."""
    text = _normalized_type(row.type)
    if not text:
        return None
    if text.endswith(" *"):
        text = text[:-2].strip()
    layout = type_layout(text) if text else None
    return text if layout is not None and layout.record else None


def _fits(record: str, accesses: list) -> bool:
    """Whether every access of a pointer argument lands on a member of one record."""
    layout = type_layout(record)
    if layout is None or not layout.record:
        return False
    for access in accesses:
        if access.offset < 0 or access.offset + access.width > layout.size:
            return False
        if not locate(layout, access.offset):
            return False
    return True


def _v0_after_call(caller, call) -> str | None:
    """Return how a caller uses the value a call returns, else None."""
    insns = caller.insns
    start = next(
        (number for number, insn in enumerate(insns) if insn.address == call.address),
        None,
    )
    if start is None:
        return None
    for insn in insns[start + 2 : start + 9]:
        mnemonic = insn.mnemonic
        ops = asmtext.operands(insn.operands)
        dest, reads = asmtext.read_write(mnemonic, ops)
        if 2 in reads:
            for operand in ops:
                part = asmtext.memory(operand)
                if part is not None and part[1] == 2:
                    return "pointer"
            if mnemonic in ("slt", "sltu", "slti", "sltiu"):
                return "bool"
            if mnemonic in ("beq", "bne", "beqz", "bnez", "bgez", "blez", "bltz"):
                return "bool"
            return "value"
        if mnemonic in ("jal", "jalr", "jr", "j") or dest == 2:
            break
    return None


def _caller_map(assembly: Assembly) -> dict[tuple[str, str], list]:
    """Return, per function, its direct callers with the call's evidence."""
    if assembly.callers is not None:
        return assembly.callers
    found: dict[tuple[str, str], list] = collections.defaultdict(list)
    for (image, name), facts in assembly.facts.items():
        caller = assembly.by_image[image][name]
        for call in facts.calls:
            target = assembly.resolve(image, call.callee)
            if target is None:
                continue
            found[(target.image, target.name)].append((caller, call))
    assembly.callers = dict(found)
    return assembly.callers


def _table_callees(
    assembly: Assembly, manifests: dict, tree
) -> dict[tuple[str, str], list]:
    """Return the function names each function's indirect calls reach through a table."""
    known = {
        function.name
        for functions in assembly.functions.values()
        for function in functions
    }
    tables, names = _layer_tables(tree, known, manifests)
    symbols = symbol_tables()
    for rows in symbols.values():
        for name, row in rows.items():
            if isinstance(row, dict) and _looks_like_table(row):
                names.add(name)
    referenced: dict[str, set[str]] = collections.defaultdict(set)
    for (image, _name), facts in assembly.facts.items():
        if facts.indirect:
            referenced[image].update(name for _table, name in facts.symbols)
    wanted = names & {name for values in referenced.values() for name in values}
    if not wanted:
        return {}
    layouts, payloads = _layer_layouts(manifests)
    by_address: dict[int, list] = collections.defaultdict(list)
    for functions in assembly.functions.values():
        for function in functions:
            by_address[function.address].append(function)
    found: dict[tuple[str, str], list[str]] = {}

    def resolve_table(image: str, name: str) -> list[str]:
        entries = _table_entries(tables, image, name)
        if not entries:
            entries = _retail_table_entries(
                image, name, symbols, layouts, payloads, by_address
            )
        return entries

    for image, names_here in sorted(referenced.items()):
        for name in sorted(names_here & wanted):
            found[(image, name)] = resolve_table(image, name)
    return found


def _table_callers(
    assembly: Assembly, table_callees: dict[tuple[str, str], list]
) -> dict[tuple[str, str], list]:
    """Return, per function, the functions whose indirect calls reach it through a table."""
    reverse: dict[tuple[str, str], list] = collections.defaultdict(list)
    for (image, caller_name), names in table_callees.items():
        for callee in names:
            target = assembly.resolve(image, callee)
            if target is not None:
                reverse[(target.image, target.name)].append((image, caller_name))
    return reverse


def _layers(
    assembly: Assembly,
    table_callees: dict[tuple[str, str], list],
) -> dict[tuple[str, str], int]:
    """Return every function's call-graph layer."""
    nodes = [
        (image, function.name)
        for image, functions in sorted(assembly.functions.items())
        for function in functions
    ]
    position = {node: index for index, node in enumerate(nodes)}
    edges: list[set[int]] = [set() for _ in nodes]
    for index, (image, name) in enumerate(nodes):
        facts = assembly.facts[(image, name)]
        callees = [call.callee for call in facts.calls]
        callees.extend(table_callees.get((image, name), ()))
        for callee in callees:
            target = assembly.resolve(image, callee)
            other = position.get((target.image, target.name)) if target else None
            if other is not None:
                edges[index].add(other)
    levels = assign_layers(len(nodes), edges)
    return {node: levels[index] for index, node in enumerate(nodes)}


def _majority(votes: collections.Counter, lowest: dict[str, int], tiebreak: int) -> str:
    """Return the system with the most votes; a tie goes to the lowest layer, then the name."""
    if not votes:
        return ""
    return min(
        votes,
        key=lambda system: (-votes[system], lowest.get(system, tiebreak), system),
    )


def _confidence(votes: collections.Counter, found_home: str) -> str:
    """Return proven when every vote agrees, likely over 80% and open otherwise."""
    total = sum(votes.values())
    if not total or not found_home:
        return "open"
    share = votes[found_home] / total
    if share == 1.0 and total >= 2:
        return "proven"
    if share >= 0.8:
        return "likely"
    return "open"


def _function_home(function, manifests: dict) -> str:
    """Return the system a function belongs to by its name prefix or its folder."""
    return _name_system(function.name) or _folder_system(
        manifests[function.image].source_dir
    )


def _call_window(caller, call) -> list[int]:
    """Return the instructions a caller writes an argument in, nearest first."""
    insns = caller.insns
    start = next(
        (number for number, insn in enumerate(insns) if insn.address == call.address),
        None,
    )
    if start is None:
        return []
    positions = [start + 1] if start + 1 < len(insns) else []
    for step in range(1, 13):
        position = start - step
        if position < 0:
            break
        if insns[position].mnemonic in ("jal", "jalr", "jr", "j"):
            break
        positions.append(position)
    return positions


def _call_sources(caller, call) -> dict[int, int]:
    """Return, per callee argument position, the register its value was copied from."""
    sources: dict[int, int] = {}
    for position in _call_window(caller, call):
        insn = caller.insns[position]
        dest, reads = asmtext.read_write(insn.mnemonic, asmtext.operands(insn.operands))
        if dest is None or dest not in asmtext.ARG_REGISTERS or dest - 4 in sources:
            continue
        source = next(
            (register for register in reads if register in asmtext.ARG_REGISTERS),
            -1,
        )
        sources[dest - 4] = source
    return sources


def _previous_call(insns, index: int, skip: int) -> str | None:
    """Return the callee of the call whose result a register still holds, if any."""
    for position in range(index - 1, max(-1, index - 10), -1):
        if position == skip:
            continue
        insn = insns[position]
        if insn.mnemonic in ("jal", "jalr"):
            ops = asmtext.operands(insn.operands)
            named = asmtext.symbol(ops[0]) if ops else None
            return named[0] if named is not None else None
        if insn.mnemonic in ("jr", "j"):
            break
    return None


def _caller_argument_kind(caller, call, position: int, tree, visible: set[str]) -> str:
    """Return the type a caller's argument register holds before one call."""
    narrow = {"lb": "s8", "lbu": "u8", "lh": "s16", "lhu": "u16"}
    start = next(
        (
            number
            for number, insn in enumerate(caller.insns)
            if insn.address == call.address
        ),
        None,
    )
    for index in _call_window(caller, call):
        insn = caller.insns[index]
        ops = asmtext.operands(insn.operands)
        dest, reads = asmtext.read_write(insn.mnemonic, ops)
        if dest != 4 + position:
            continue
        if 2 in reads:
            callee = _previous_call(caller.insns, index, start)
            if callee:
                decl = _declared_prototype(tree, callee, visible)
                if decl is not None and _declared_return_kind(decl.ret) == "pointer":
                    return "pointer"
        if insn.mnemonic in narrow:
            return narrow[insn.mnemonic]
        if insn.mnemonic == "andi" and len(ops) >= 3:
            mask = asmtext.integer(ops[2])
            if mask == 0xFF:
                return "u8"
            if mask == 0xFFFF:
                return "u16"
        if insn.mnemonic in ("sll", "sra", "srl") and len(ops) >= 3:
            amount = asmtext.integer(ops[2])
            if amount == 24:
                return "s8"
            if amount == 16:
                return "s16"
        if insn.mnemonic == "lui" or any(
            "%hi(" in operand or "%lo(" in operand for operand in ops
        ):
            return "pointer"
        return "s32"
    return "s32"


def _argument_live_at(function, call, position: int) -> bool:
    """Whether an argument register still holds the caller's value when a call copies it."""
    insns = function.insns
    writer = None
    for index in _call_window(function, call):
        dest, _reads = asmtext.read_write(
            insns[index].mnemonic, asmtext.operands(insns[index].operands)
        )
        if dest == 4 + position:
            writer = index
            break
    if writer is None:
        return True
    for insn in insns[:writer]:
        if insn.mnemonic in ("jal", "jalr"):
            return False
        dest, _reads = asmtext.read_write(
            insn.mnemonic, asmtext.operands(insn.operands)
        )
        if dest == 4 + position:
            return False
    return True


def _forwarded_pointer(
    function, facts, position: int, tree, visible: set[str]
) -> str | None:
    """Return the pointer type an argument is forwarded as to one declared callee parameter."""
    for call in facts.calls:
        if not _argument_live_at(function, call, position):
            continue
        declared = _declared_prototype(tree, call.callee, visible)
        if declared is None or declared.unspecified:
            continue
        params = [
            ctype
            for ctype, param in declared.params
            if not (ctype == "void" and not param) and ctype != "..."
        ]
        sources = _call_sources(function, call)
        for callee_position, ctype in enumerate(params):
            text = _normalized_type(ctype)
            if not text.endswith(" *"):
                continue
            if sources.get(callee_position) == 4 + position:
                return text[:-2].strip() or "void"
    return None


def _function_signature(
    function,
    facts,
    callers: list,
    index: SymbolIndex,
    tree,
    visible: set[str],
    table_callers: list = (),
) -> dict:
    """Build one signature row from a function's facts and its callers."""
    declared = _declared_prototype(tree, function.name, visible)
    arguments = []
    counts = [
        max(call.arguments) - 3 if call.arguments else 0 for _caller, call in callers
    ]
    used = max(facts.args) + 1 if facts.args else 0
    for position in range(used):
        use = facts.args.get(position)
        record = None
        forwarded = None
        proof = None
        if use and use.accesses:
            kind = "pointer"
            proof = "callee"
            record = _pointer_record(use, index, callers, position, declared)
        else:
            forwarded = _forwarded_pointer(function, facts, position, tree, visible)
            caller_kinds = [
                _caller_argument_kind(caller, call, position, tree, visible)
                for caller, call in callers
            ]
            if forwarded is not None:
                kind = "pointer"
                proof = "forwarded"
                layout = type_layout(forwarded) if forwarded != "void" else None
                record = forwarded if layout is not None and layout.record else None
            elif callers and all(value == "pointer" for value in caller_kinds):
                kind = "pointer"
                proof = "callers"
                forwarded = "void"
            else:
                kind = use.narrow if use and use.narrow else "s32"
                proof = "callee" if use and use.narrow else None
        arguments.append(
            {
                "index": position,
                "register": _reg_name(4 + position),
                "kind": kind,
                "type": f"{record}*" if record else ("void*" if forwarded else kind),
                "record": record,
                "narrow": use.narrow if use else None,
                "proof": proof,
                "used": use is not None,
                "accesses": [
                    {
                        "offset": f"0x{access.offset:X}",
                        "width": access.width,
                        "signed": access.signed,
                        "mnemonic": access.mnemonic,
                        "write": access.write,
                    }
                    for access in use.accesses
                ]
                if use
                else [],
            }
        )
    for position in range(facts.stack_arguments):
        pointer = position in facts.stack_pointers
        arguments.append(
            {
                "index": 4 + position,
                "register": f"0x{0x10 + position * 4:X}(sp)",
                "kind": "pointer" if pointer else "s32",
                "type": "void*" if pointer else "s32",
                "record": None,
                "narrow": None,
                "accesses": [],
            }
        )
    caller_uses = [_v0_after_call(caller, call) for caller, call in callers]
    returns = list(facts.return_writes)
    if not returns:
        returned = {"kind": "void", "width": None, "sign": None}
    elif all(asmtext.bool_write(mnemonic, text) for mnemonic, text in returns):
        returned = {"kind": "bool", "width": 1, "sign": False}
    elif any(kind == "pointer" for kind in caller_uses):
        returned = {"kind": "pointer", "width": 4, "sign": None}
    else:
        width, sign = facts.return_width or (None, None)
        returned = {"kind": "value", "width": width, "sign": sign}
    declared_text = _render_declared(function.name, declared)
    found_text = _render_found(function.name, arguments, returned)
    differs = []
    declared_params: list = []
    if declared is not None and not declared.unspecified:
        declared_params = [
            (ctype, param)
            for ctype, param in declared.params
            if not (ctype == "void" and not param) and ctype != "..."
        ]
        if len(declared_params) != len(arguments):
            differs.append(
                f"arguments {len(declared_params)} declared, {len(arguments)} found"
            )
        for position, (ctype, _param) in enumerate(declared_params):
            if position >= len(arguments):
                break
            kind = _declared_kind(ctype)
            if kind != arguments[position]["kind"]:
                differs.append(
                    f"arg{position} {kind} declared, "
                    f"{arguments[position]['kind']} found"
                )
        declared_return = _declared_return_kind(declared.ret)
        if declared_return != returned["kind"]:
            differs.append(
                f"return {declared_return} declared, {returned['kind']} found"
            )
    confidence = "open"
    if counts:
        share = sum(1 for count in counts if count == used) / len(counts)
        if share == 1.0 and not facts.stack_arguments:
            confidence = "proven"
        elif share >= 0.8:
            confidence = "likely"
    elif facts.args or returns:
        confidence = "likely"
    narrow = {"u8", "s8", "u16", "s16"}
    if any(
        argument["kind"] == "pointer" and argument.get("proof") == "callers"
        for argument in arguments
    ):
        confidence = "likely" if confidence == "proven" else confidence
    if not returns and facts.ambiguous_return:
        confidence = "likely" if confidence == "proven" else confidence
    for position, argument in enumerate(arguments):
        declared_kind = (
            _declared_kind(declared_params[position][0])
            if declared_params and position < len(declared_params)
            else None
        )
        if argument["kind"] in narrow:
            caller_kinds = [
                _caller_argument_kind(caller, call, position, tree, visible)
                for caller, call in callers
            ]
            if not all(kind in narrow for kind in caller_kinds):
                confidence = "likely" if confidence == "proven" else confidence
        elif declared_kind in narrow and argument["kind"] == "s32":
            confidence = "likely" if confidence == "proven" else confidence
        elif declared_kind == "pointer" and argument["kind"] != "pointer":
            confidence = "likely" if confidence == "proven" else confidence
    evidence = [
        f"{caller.image}@0x{call.address:08X} {caller.name} "
        f"args={','.join(_reg_name(register) for register in call.arguments)}"
        for caller, call in callers[:5]
    ]
    evidence.extend(f"table caller {image}:{name}" for image, name in table_callers[:3])
    for access in facts.accesses[:5]:
        offset = f"+0x{access.offset:X}" if access.offset else ""
        evidence.append(
            f"{function.image}@0x{access.address:08X} {access.mnemonic} "
            f"{access.name or 'argument'}{offset}"
        )
    return {
        "function": function.name,
        "image": function.image,
        "address": f"0x{function.address:08X}",
        "declared": declared_text,
        "found": found_text,
        "callee_args": used,
        "stack_args": facts.stack_arguments,
        "caller_args_min": min(counts) if counts else None,
        "caller_args_max": max(counts) if counts else None,
        "disagree": bool(differs),
        "differs": differs,
        "args": arguments,
        "return": returned,
        "callers": len(callers) + len(table_callers),
        "evidence": evidence,
        "confidence": confidence,
    }


def _render_found(name: str, arguments: list[dict], returned: dict) -> str:
    params = ", ".join(argument["type"] for argument in arguments)
    return f"{_return_type(returned)} {name}({params or 'void'})"


def _return_type(returned: dict) -> str:
    """Write a returned kind as the C type its width and sign state."""
    kind = returned["kind"]
    if kind in ("void", "bool"):
        return kind
    if kind == "pointer":
        return "void*"
    width = returned["width"]
    sign = returned["sign"]
    if width == 1:
        return "u8" if sign is False else "s8"
    if width == 2:
        return "u16" if sign is False else "s16"
    return "s32"


def _home_of(manifests: dict, key: tuple[str, str]) -> str:
    """Return a function's declared system from its name prefix or its folder."""
    image, name = key
    return _name_system(name) or _folder_system(manifests[image].source_dir)


def _function_candidates(
    function,
    facts,
    index: SymbolIndex,
    manifests: dict,
    callers: dict[tuple[str, str], list],
    writers: dict,
    readers: dict,
    previous,
    following,
    declared: str,
    local: bool,
) -> dict[str, list[str]]:
    """Return the systems a function's bytes move it to, each with its rule evidence."""
    rules: dict[str, list[str]] = collections.defaultdict(list)
    sites = callers.get((function.image, function.name), ())
    caller_systems = collections.Counter(
        _function_home(caller, manifests) for caller, _call in sites
    )
    if not local and sum(caller_systems.values()) >= 3:
        system, count = caller_systems.most_common(1)[0]
        if count / sum(caller_systems.values()) >= 0.8:
            rules[system].append(
                f"rule a: {count} of {sum(caller_systems.values())} callers are {system}"
            )
    if not local:
        for access in facts.accesses:
            if not access.write or not access.name:
                continue
            row = index.resolve(function.image, access.name)
            if row is None:
                continue
            key = (access.name, row.addr)
            if writers.get(key) != {(function.image, function.name)}:
                continue
            others = readers.get(key, set()) - {(function.image, function.name)}
            if not others:
                continue
            systems = {_home_of(manifests, other) for other in others}
            if len(systems) == 1:
                system = next(iter(systems))
                rules[system].append(
                    f"rule b: only writer of {access.name}, read by "
                    f"{len(others)} function(s) in {system}"
                )
    if previous is not None and following is not None:
        left = _function_home(previous, manifests)
        right = _function_home(following, manifests)
        if left == right and left != declared:
            declared_callers = [
                caller
                for caller, _call in sites
                if _function_home(caller, manifests) == declared
            ]
            if not declared_callers:
                rules[left].append(
                    f"rule c: between {previous.name} and {following.name} in address "
                    f"order and no {declared} caller"
                )
    return rules


def _function_rows(
    assembly: Assembly,
    manifests: dict,
    index: SymbolIndex,
    layers: dict[tuple[str, str], int],
    callers: dict[tuple[str, str], list],
    table_callees: dict[tuple[str, str], list],
    writers: dict,
    readers: dict,
) -> list[dict]:
    """Build one home row per function, from the call and data graph."""
    rows = []
    for image, functions in sorted(assembly.functions.items()):
        folder = _folder_system(manifests[image].source_dir)
        order = sorted(functions, key=lambda function: function.address)
        prefixes = {_name_system(function.name) for function in functions}
        for position, function in enumerate(order):
            key = (image, function.name)
            facts = assembly.facts[key]
            declared = _name_system(function.name) or folder
            local = image.startswith("emi/") and declared in prefixes
            rules = _function_candidates(
                function,
                facts,
                index,
                manifests,
                callers,
                writers,
                readers,
                order[position - 1] if position else None,
                order[position + 1] if position + 1 < len(order) else None,
                declared,
                local,
            )
            if rules:
                found_home = min(
                    rules, key=lambda system: (-len(rules[system]), system)
                )
                evidence = rules[found_home]
            else:
                found_home = declared
                evidence = []
            sites = callers.get(key, ())
            rows.append(
                {
                    "kind": "function",
                    "name": function.name,
                    "image": image,
                    "address": f"0x{function.address:08X}",
                    "layer": layers.get(key, 0),
                    "declared_home": declared,
                    "found_home": found_home,
                    "folder": folder,
                    "counts": {
                        "callers": len(sites),
                        "callees": len(facts.calls),
                        "data": sum(1 for table, _name in facts.symbols if table),
                        "systems": dict(
                            collections.Counter(
                                _function_home(caller, manifests)
                                for caller, _call in sites
                            )
                        ),
                    },
                    "evidence": evidence[:4],
                    "confidence": "proven"
                    if len(evidence) >= 2
                    else "likely"
                    if evidence
                    else "open",
                }
            )
    return rows


def _global_rows(
    assembly: Assembly,
    manifests: dict,
    index: SymbolIndex,
    layers: dict[tuple[str, str], int],
    functions: dict[tuple[str, str], dict],
    extents: list[dict],
    uses: dict,
    writers: dict,
    readers: dict,
) -> list[dict]:
    """Build one home row per global whose writers all sit in one system."""
    absorbed: dict[tuple[str, int], str] = {}
    for row in extents:
        start = int(row["address"], 16)
        for name in row["absorbs"]:
            absorbed[(name, start)] = row["symbol"]
    rows = []
    for row in _unique_data_rows(index):
        key = (row.name, row.addr)
        written_by = writers.get(key)
        if not written_by:
            continue
        systems = {
            functions.get(item, {}).get("found_home") or _home_of(manifests, item)
            for item in written_by
        }
        if len(systems) != 1:
            continue
        found_home = next(iter(systems))
        image = index.canonical(row.name, row.addr) or row.table
        declared = _symbol_system(row.name, assembly.systems) or _folder_system(
            manifests[image].source_dir if image in manifests else row.table
        )
        read_by = readers.get(key, set())
        found = uses.get(key, ())
        rows.append(
            {
                "kind": "global",
                "name": row.name,
                "image": image,
                "address": f"0x{row.addr:08X}",
                "declared_home": declared,
                "found_home": found_home,
                "member_of": absorbed.get(key),
                "counts": {
                    "reads": sum(1 for _i, _f, access in found if not access.write),
                    "writes": sum(1 for _i, _f, access in found if access.write),
                    "writers": len(written_by),
                    "readers": len(read_by),
                    "images": len(assembly.functions) if image in RESIDENT else 1,
                    "systems": {
                        system: sum(
                            1
                            for item in written_by
                            if (
                                functions.get(item, {}).get("found_home")
                                or _home_of(manifests, item)
                            )
                            == system
                        )
                        for system in systems
                    },
                },
                "evidence": [
                    f"writer {item[0]}:{item[1]}" for item in sorted(written_by)[:4]
                ],
                "confidence": "proven",
            }
        )
    return rows


def _unit_of(tree, visible: set[str], function) -> str:
    """Return the source file a function belongs to: its C unit, else its split unit."""
    for decl in tree.decls.get(function.name, ()):
        if decl.kind == "def" and decl.file in visible:
            return decl.file
    return function.source


def _is_split_unit(unit: str) -> bool:
    """Whether a unit is a split assembly file rather than a C file."""
    return unit.startswith("asm/")


def _file_rows(
    assembly: Assembly,
    manifests: dict,
    tree,
    visible: dict[str, set[str]],
    function_rows: list[dict],
) -> list[dict]:
    """Build one home row per source file, with contiguity evidence from the address order."""
    homes = {(row["image"], row["name"]): row["found_home"] for row in function_rows}
    rows: list[dict] = []
    for image, functions in sorted(assembly.functions.items()):
        order = sorted(functions, key=lambda function: function.address)
        systems: dict[str, collections.Counter] = collections.defaultdict(
            collections.Counter
        )
        names: dict[str, list[str]] = collections.defaultdict(list)
        unit_runs: list[tuple[str, str]] = []
        system_runs: list[str] = []
        folder = _folder_system(manifests[image].source_dir)
        for function in order:
            unit = _unit_of(tree, visible.get(image, set()), function)
            system = homes.get((image, function.name)) or folder
            systems[unit][system] += 1
            names[unit].append(function.name)
            if not unit_runs or unit_runs[-1][0] != unit:
                unit_runs.append((unit, system))
            if not system_runs or system_runs[-1] != system:
                system_runs.append(system)
        evidence: dict[str, list[str]] = collections.defaultdict(list)
        for position in range(len(unit_runs) - 1):
            unit, system = unit_runs[position]
            other_unit, other_system = unit_runs[position + 1]
            if not (_is_split_unit(unit) or _is_split_unit(other_unit)):
                continue
            if system != other_system:
                continue
            if len(names[unit]) < 2 and len(names[other_unit]) < 2:
                continue
            evidence[unit].append(
                f"continues {other_unit} in the address order: one unit split"
            )
            evidence[other_unit].append(
                f"continues {unit} in the address order: one unit split"
            )
        if len(system_runs) > 1 and all(
            _name_system(function.name) for function in order
        ):
            evidence_for_all = (
                f"the systems are split into {len(system_runs)} address runs: "
                "another system's units sit between"
            )
            for unit, _system in unit_runs:
                evidence[unit].append(evidence_for_all)
        for unit, counter in systems.items():
            declared = _folder_system(manifests[image].source_dir)
            found_home = _majority(counter, {}, 0) or declared
            for name in names[unit][:4]:
                if homes.get((image, name)) != found_home:
                    evidence[unit].append(f"{name} is {homes.get((image, name))}")
            rows.append(
                {
                    "kind": "file",
                    "name": unit,
                    "image": image,
                    "declared_home": declared,
                    "found_home": found_home,
                    "counts": {
                        "functions": len(names[unit]),
                        "systems": dict(counter),
                    },
                    "evidence": evidence.get(unit, [])[:6],
                    "confidence": _confidence(counter, found_home),
                }
            )
    return [row for row in rows if not row["name"].startswith("asm/")]


def signatures(args: argparse.Namespace) -> int:
    """Print the signature the bytes prove for each function, beside its declaration."""
    assembly = _assembly()
    index = SymbolIndex(symbol_tables())
    manifests = _layer_manifests()
    tree = _layer_tree()
    visible = _visible_sources(tree, manifests)
    callers = _caller_map(assembly)
    table_callers = _table_callers(assembly, _table_callees(assembly, manifests, tree))
    rows = []
    for image, functions in sorted(assembly.functions.items()):
        for function in functions:
            if args.function and function.name != args.function:
                continue
            rows.append(
                _function_signature(
                    function,
                    assembly.facts[(image, function.name)],
                    callers.get((image, function.name), ()),
                    index,
                    tree,
                    visible.get(image, set()),
                    table_callers.get((image, function.name), ()),
                )
            )
    keys = [
        "function",
        "image",
        "address",
        "declared",
        "found",
        "callee_args",
        "stack_args",
        "caller_args_min",
        "caller_args_max",
        "disagree",
        "differs",
        "args",
        "return",
        "callers",
        "evidence",
        "confidence",
    ]
    if args.jsonl:
        for row in rows:
            print(json.dumps({key: row[key] for key in keys}, ensure_ascii=False))
        return 0
    print(
        "\t".join(
            [
                "function",
                "image",
                "address",
                "declared",
                "found",
                "callers",
                "confidence",
            ]
        )
    )
    for row in rows:
        print(
            "\t".join(
                [
                    row["function"],
                    row["image"],
                    row["address"],
                    row["declared"] or "",
                    row["found"],
                    str(row["callers"]),
                    row["confidence"],
                ]
            )
        )
    return 0


def extents(args: argparse.Namespace) -> int:
    """Print each global's extent and the accesses beyond it the bytes prove."""
    assembly = _assembly()
    index = SymbolIndex(symbol_tables())
    manifests = _layer_manifests()
    if args.image and args.image not in manifests:
        raise SystemExit(f"extents: no target {args.image}")
    rows = _extent_rows(assembly, index, manifests)
    if args.image:
        rows = [row for row in rows if row["image"] == args.image]
    keys = [
        "symbol",
        "image",
        "address",
        "gap",
        "declared_size",
        "stride",
        "beyond",
        "beyond_count",
        "absorbs",
        "section",
        "type",
        "evidence",
    ]
    if args.jsonl:
        for row in rows:
            print(json.dumps({key: row[key] for key in keys}, ensure_ascii=False))
        return 0
    print("\t".join(keys))
    for row in rows:
        print(
            "\t".join(
                json.dumps(row[key])
                if isinstance(row[key], (list, dict))
                else str(row[key] if row[key] is not None else "")
                for key in keys
            )
        )
    return 0


def homes(args: argparse.Namespace) -> int:
    """Print each function's, global's and file's home from the call and data graph."""
    assembly = _assembly()
    index = SymbolIndex(symbol_tables())
    manifests = _layer_manifests()
    tree = _layer_tree()
    visible = _visible_sources(tree, manifests)
    callers = _caller_map(assembly)
    table_callees = _table_callees(assembly, manifests, tree)
    layers = _layers(assembly, table_callees)
    uses = _symbol_uses(assembly, index)
    writers: dict[tuple[str, int], set] = collections.defaultdict(set)
    readers: dict[tuple[str, int], set] = collections.defaultdict(set)
    for key, found in uses.items():
        for use_image, function_name, access in found:
            target = writers if access.write else readers
            target[key].add((use_image, function_name))
    function_list = _function_rows(
        assembly,
        manifests,
        index,
        layers,
        callers,
        table_callees,
        writers,
        readers,
    )
    extent_list = _extent_rows(assembly, index, manifests)
    global_list = _global_rows(
        assembly,
        manifests,
        index,
        layers,
        {(row["image"], row["name"]): row for row in function_list},
        extent_list,
        uses,
        writers,
        readers,
    )
    file_list = _file_rows(assembly, manifests, tree, visible, function_list)
    rows = sorted(
        function_list, key=lambda row: (row["layer"], row["image"], row["name"])
    )
    rows.extend(sorted(global_list, key=lambda row: (row["name"], row["image"])))
    rows.extend(sorted(file_list, key=lambda row: (row["name"], row["image"])))
    keys = [
        "kind",
        "name",
        "image",
        "declared_home",
        "found_home",
        "counts",
        "evidence",
        "confidence",
    ]
    if args.jsonl:
        for row in rows:
            print(json.dumps({key: row[key] for key in keys}, ensure_ascii=False))
        return 0
    print("\t".join(keys))
    for row in rows:
        print(
            "\t".join(
                json.dumps(row[key])
                if isinstance(row[key], (list, dict))
                else str(row[key])
                for key in keys
            )
        )
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
    eight = verbs.add_parser(
        "value",
        help="find enum members and macros with one value",
        epilog=(
            "Example: tools/symbol.py value 0x3A --image emi/battle/battle/03 --type ENEMY_ID"
        ),
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    eight.add_argument("number", help="a hexadecimal value, such as 0x3A")
    eight.add_argument(
        "--image", help="a symbols.toml table; scan the headers its sources include"
    )
    eight.add_argument("--type", help="an enum name or a name prefix")
    eight.set_defaults(run=value)
    nine = verbs.add_parser(
        "layers",
        help="print the call-graph layer of every function",
        epilog="Example: tools/symbol.py layers --jsonl",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    nine.add_argument("--jsonl", action="store_true", help="one JSON object per line")
    nine.set_defaults(run=layers)
    ten = verbs.add_parser(
        "accesses",
        help="list the reads and writes of a record or global",
        epilog="Example: tools/symbol.py accesses PartyMember --jsonl",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ten.add_argument("name", help="a record type or a config/symbols.toml global")
    ten.add_argument("--jsonl", action="store_true", help="one JSON object per line")
    ten.set_defaults(run=accesses)
    eleven = verbs.add_parser(
        "records",
        help="summarise every record and its accesses",
        epilog="Example: tools/symbol.py records --jsonl",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    eleven.add_argument("--jsonl", action="store_true", help="one JSON object per line")
    eleven.set_defaults(run=records)
    twelve = verbs.add_parser(
        "values",
        help="scan matched bodies for literals whose role is declared",
        epilog=(
            "Example: tools/symbol.py values --scan --jsonl > values.jsonl\n"
            "         tools/symbol.py values --scan"
        ),
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    twelve.add_argument(
        "--scan", action="store_true", help="scan the matched bodies (the only mode)"
    )
    twelve.add_argument("--jsonl", action="store_true", help="one JSON object per line")
    twelve.set_defaults(run=values)
    thirteen = verbs.add_parser(
        "signatures",
        help="print the signature the bytes prove for each function",
        epilog=(
            "Example: tools/symbol.py signatures Battle_Update\n"
            "         tools/symbol.py signatures --all --jsonl > signatures.jsonl"
        ),
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    thirteen.add_argument("function", nargs="?", help="one function name")
    thirteen.add_argument(
        "--all", action="store_true", help="every function of every image"
    )
    thirteen.add_argument(
        "--jsonl", action="store_true", help="one JSON object per line"
    )
    thirteen.set_defaults(run=signatures)
    fourteen = verbs.add_parser(
        "extents",
        help="print each global's extent and the accesses beyond it",
        epilog="Example: tools/symbol.py extents emi/battle/battle/03 --jsonl",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    fourteen.add_argument("image", nargs="?", help="a symbols.toml table")
    fourteen.add_argument(
        "--jsonl", action="store_true", help="one JSON object per line"
    )
    fourteen.set_defaults(run=extents)
    fifteen = verbs.add_parser(
        "homes",
        help="print each function's, global's and file's home from the graph",
        epilog="Example: tools/symbol.py homes --jsonl > homes.jsonl",
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    fifteen.add_argument(
        "--jsonl", action="store_true", help="one JSON object per line"
    )
    fifteen.set_defaults(run=homes)
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
