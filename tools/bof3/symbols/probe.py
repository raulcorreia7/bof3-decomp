"""Read a C record's byte layout from the compiler."""

from __future__ import annotations

import json
import math
import os
import re
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path

from bof3.symbols.context import Context, grep_files

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
    """One non-alias row of config/symbols/<image>.toml."""

    name: str
    addr: int
    type: str
    size: int | None
    table: str


def _sized_member(member: Member, later: list[Member], size: int) -> Member:
    """Return ``member`` with its length: up to the next member outside it, capped by its type."""
    depth = member.path.count(".")
    end = size
    for after in later:
        if after.path.count(".") <= depth and after.offset > member.offset:
            end = after.offset
            break
    length = end - member.offset
    width = _known_width(member.ctype)
    if width is not None:
        length = min(length, width)
    return Member(member.offset, member.path, member.ctype, length)


def _block_members(lines: list[str]) -> tuple[list[Member], int | None]:
    """Return the members of one record dump and its size (None when the dump has none)."""
    members: list[Member] = []
    stack: list[str] = []
    for line in lines[1:]:
        found = LAYOUT_SIZE.search(line)
        if found:
            return members, int(found.group(1))
        match = LAYOUT_MEMBER.match(line)
        if match:
            offset, indent, ctype, name = match.groups()
            stack = stack[: len(indent) // 2 - 1]
            members.append(
                Member(int(offset), ".".join([*stack, name]), ctype.strip(), 0)
            )
            stack.append(name)
    return members, None


def parse_probe(text: str) -> Layout | None:
    """Read the layout from the ``struct __probe`` block of a clang record dump."""
    for block in text.split("*** Dumping AST Record Layout")[1:]:
        lines = block.strip("\n").split("\n")
        if not PROBE_HEAD.match(lines[0]):
            continue
        members, size = _block_members(lines)
        if size is None:
            continue
        inner = [
            Member(m.offset, m.path.removeprefix("x."), m.ctype, 0)
            for m in members
            if m.path != "x"
        ]
        for index, member in enumerate(inner):
            inner[index] = _sized_member(member, inner[index + 1 :], size)
        return Layout(size, tuple(inner), bool(inner))
    return None


def _type_headers(ctx: Context, name: str) -> list[str]:
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
    for path in grep_files(ctx, base, ["include", "src"]):
        if not path.endswith(".h"):
            continue
        try:
            text = (ctx.root / path).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if end.search(text) or simple.search(text) or definition.search(text):
            headers.append(path)
    return headers


def _dependencies(ctx: Context, dep: Path, source: Path) -> list[list[str | int]]:
    """Return the header stamp clang read: path, mtime and size of every dependency."""
    text = dep.read_text(encoding="utf-8", errors="replace").replace("\\\n", " ")
    _, _, rest = text.partition(":")
    deps: list[list[str | int]] = []
    for token in rest.split():
        path = Path(token)
        if path.resolve() == source.resolve():
            continue
        full = path if path.is_absolute() else ctx.root / path
        try:
            info = full.stat()
        except OSError:
            continue
        deps.append([str(path), info.st_mtime_ns, info.st_size])
    return deps


def _probe(ctx: Context, name: str) -> tuple[Layout, list[list[str | int]], str] | None:
    """Ask clang for ``name``'s layout through a probe record that holds one."""
    for header in _type_headers(ctx, name):
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
                cwd=ctx.root,
                capture_output=True,
                text=True,
                check=False,
            )
            if result.returncode:
                continue
            layout = parse_probe(result.stdout)
            if layout is None:
                continue
            return layout, _dependencies(ctx, dep, source), header
    return None


def _layout_index(ctx: Context) -> dict[str, dict]:
    index = ctx.layout_index
    if index is None:
        try:
            index = json.loads(ctx.layout_cache.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            index = {}
        ctx.layout_index = index
    return index


def _cache_current(ctx: Context, entry: dict) -> bool:
    if entry.get("version") != LAYOUT_VERSION:
        return False
    for name, mtime, size in entry.get("deps", []):
        path = Path(name)
        full = path if path.is_absolute() else ctx.root / path
        try:
            info = full.stat()
        except OSError:
            return False
        if info.st_mtime_ns != mtime or info.st_size != size:
            return False
    return True


def _store_layout(
    ctx: Context, name: str, layout: Layout, deps: list[list[str | int]], header: str
) -> None:
    index = _layout_index(ctx)
    index[name] = {
        "version": LAYOUT_VERSION,
        "header": header,
        "deps": deps,
        "size": layout.size,
        "members": [[m.offset, m.path, m.ctype, m.size] for m in layout.members],
    }
    try:
        ctx.layout_cache.parent.mkdir(parents=True, exist_ok=True)
        handle, tmp = tempfile.mkstemp(
            dir=ctx.layout_cache.parent, prefix="symbol-layouts-"
        )
        with os.fdopen(handle, "w", encoding="utf-8") as stream:
            json.dump(index, stream, sort_keys=True)
        os.replace(tmp, ctx.layout_cache)
    except OSError:
        pass


def type_layout(ctx: Context, name: str) -> Layout | None:
    """Return a C type's record layout from clang, cached by the headers it reads."""
    key = " ".join(name.split())
    if key in ctx.layouts:
        return ctx.layouts[key]
    if "*" in key or key in ("func", "void"):
        ctx.layouts[key] = None
        return None
    entry = _layout_index(ctx).get(key)
    layout = None
    if entry and _cache_current(ctx, entry):
        layout = Layout(
            entry["size"],
            tuple(Member(*member) for member in entry["members"]),
            bool(entry["members"]),
        )
    else:
        try:
            probed = _probe(ctx, key)
        except OSError:
            probed = None
        if probed:
            layout, deps, header = probed
            _store_layout(ctx, key, layout, deps, header)
    ctx.layouts[key] = layout
    return layout


def type_size(ctx: Context, name: str) -> int | None:
    """Return the size of a C type in bytes, from a scalar table or the record layout."""
    key = " ".join(name.split())
    if "*" in key:
        return 4
    if key in SCALAR_WIDTH:
        return SCALAR_WIDTH[key]
    layout = type_layout(ctx, key)
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
        counts = [dim for dim in dims if dim is not None]
        if width is None or len(counts) < len(dims):
            return None
        return width * math.prod(counts)
    return SCALAR_WIDTH.get(text)


def locate(
    ctx: Context, layout: Layout, offset: int, prefix: str = ""
) -> list[tuple[str, int, str]]:
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
        element = type_size(ctx, base)
        if not element:
            found.append((prefix + member.path, member.offset, member.ctype))
            continue
        strides = [0] * len(dims)
        stride = element
        for index in range(len(dims) - 1, -1, -1):
            strides[index] = stride
            if dim := dims[index]:
                stride *= dim
        remaining = offset - member.offset
        indexes = ""
        for index in range(len(dims)):
            indexes += f"[{remaining // strides[index]}]"
            remaining %= strides[index]
        start = member.offset + (offset - member.offset - remaining)
        inner = type_layout(ctx, base)
        if inner is not None and inner.members:
            deeper = locate(ctx, inner, remaining)
            if deeper:
                found.extend(
                    (prefix + member.path + indexes + "." + path, start + at, ctype)
                    for path, at, ctype in deeper
                )
                continue
        found.append((prefix + member.path + indexes, start, base))
    return found
