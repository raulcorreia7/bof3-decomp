"""Find the symbol, member and references at an address."""

from __future__ import annotations

import collections
import json
import os
import re
import subprocess
import sys
import tempfile
from dataclasses import dataclass
from pathlib import Path

from bof3.adapters.config import read_symbols
from bof3.errors import SymbolError
from bof3.resolve.ids import source_folder
from bof3.source import ctext
from bof3.symbols.context import RESIDENT, Context, grep_files
from bof3.symbols.probe import GLABEL, Row, locate, type_layout


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


def splat_spans(ctx: Context, table: str) -> dict[int, int]:
    """Return the size of each subsegment the target's layout starts."""
    if table in ctx.spans:
        return ctx.spans[table]
    spans: dict[int, int] = {}
    path = ctx.root / "config" / table / "splat.yaml"
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
    ctx.spans[table] = spans
    return spans


def table_range(ctx: Context, table: str) -> tuple[int, int] | None:
    """Return the address range a target's payload occupies, when its layout is known."""
    if table in ctx.ranges:
        return ctx.ranges[table]
    result = None
    path = ctx.root / "config" / table / "splat.yaml"
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
    ctx.ranges[table] = result
    return result


def foreign_visible(ctx: Context, table: str, image: str | None, addr: int) -> bool:
    """Whether a table other than the image's own may own ``addr``."""
    if image is None or table == image:
        return True
    span = table_range(ctx, table)
    return span is None or span[0] <= addr < span[1]


def row_span(ctx: Context, row: Row, following: dict[int, int]) -> int:
    """Return a row's extent: its size, its layout subsegment, its type, or a guess."""
    if row.size is not None:
        return row.size
    span = splat_spans(ctx, row.table).get(row.addr)
    if span is not None:
        return span
    inside = True
    bounds = table_range(ctx, row.table)
    if bounds is not None:
        inside = bounds[0] <= row.addr < bounds[1]
    later = following.get(row.addr)
    gap = (
        later - row.addr if inside and later is not None and later > row.addr else None
    )
    if row.type == "func":
        return gap if gap is not None else 0x100
    layout = type_layout(ctx, row.type) if row.type else None
    if layout is not None and layout.size:
        return max(layout.size, min(gap or 0x100, 0x100))
    return min(gap, 0x100) if gap is not None else 0x100


def owner(ctx: Context, row: Row, addr: int) -> tuple[str, int, str]:
    """Return the deepest member path at ``addr``, its start and type."""
    offset = addr - row.addr
    if offset == 0:
        return row.name, 0, row.type or "untyped"
    layout = type_layout(ctx, row.type) if row.type and row.type != "func" else None
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
    found = locate(ctx, layout, offset)
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
        raise SymbolError(f"symbol: {text} is not an address") from None


def _diff_addresses(ctx: Context, base: str, image: str | None) -> list[int]:
    """Return the D_ addresses the branch adds, under the image's sources when given."""
    scope = ["src", "include"]
    if image:
        try:
            folder = source_folder(image)
        except (IndexError, ValueError):
            raise SymbolError(f"symbol: {image} is not a target") from None
        scope = [f"src/{folder}", "include"]
    diff = ctx.git("diff", f"{base}...HEAD", "--", *scope)
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
    ctx: Context,
    rows: dict[str, list[Row]],
    following: dict[str, dict[int, int]],
    image: str | None,
    addr: int,
) -> list[tuple[Row, int]]:
    """Return the rows that own an address, nearest first."""
    hits = []
    for table, table_rows_ in rows.items():
        if not foreign_visible(ctx, table, image, addr):
            continue
        for row in table_rows_:
            span = row_span(ctx, row, following[table])
            if addr == row.addr or row.addr < addr < row.addr + span:
                hits.append((row, span))
    hits.sort(key=lambda item: (item[0].addr, item[0].name), reverse=True)
    return hits


@dataclass(frozen=True)
class Owner:
    path: str
    delta: int
    size: str
    table: str


@dataclass(frozen=True)
class AtRow:
    addr: int
    owners: list[Owner]


@dataclass(frozen=True)
class AtResult:
    rows: list[AtRow]
    base: str | None = None


def _owners(ctx: Context, hits: list[tuple[Row, int]], addr: int) -> list[Owner]:
    owners = []
    for row, span in hits:
        path, start, _ = owner(ctx, row, addr)
        size = (
            "(size unknown: check the record's members)"
            if row.size is None and not row.type
            else f"({row.type or 'untyped'}, {span:#x})"
        )
        owners.append(Owner(path, addr - (row.addr + start), size, row.table))
    return owners


def at(
    ctx: Context, image: str | None, addresses: list[str], diff: str | None
) -> AtResult:
    """Return the owners of each address, or of the D_ addresses the branch adds."""
    if diff is not None:
        if addresses:
            raise SymbolError("symbol: at takes addresses or --diff, not both")
        found = _diff_addresses(ctx, diff, image)
        if not found:
            return AtResult([], diff)
    elif not image or not addresses:
        raise SymbolError("symbol: at needs IMAGE 0xADDR..., or --diff [BASE]")
    else:
        found = [_address(text) for text in addresses]
    data = read_symbols(ctx.root)
    tables = _visible_tables(data, image)
    rows = {table: table_rows(data, table) for table in tables}
    following = {table: next_addresses(rows[table]) for table in tables}
    return AtResult(
        [
            AtRow(
                addr,
                _owners(ctx, find_hits(ctx, rows, following, image, addr)[:3], addr),
            )
            for addr in found
        ]
    )


def member(ctx: Context, type_name: str, offset_text: str) -> list[tuple[str, str]]:
    """Return the member path and type at one byte offset of a record."""
    name = " ".join(type_name.split())
    layout = type_layout(ctx, name)
    if layout is None or not layout.members:
        raise SymbolError(f"symbol: {name} has no named members")
    offset = _address(offset_text)
    if offset < 0 or offset >= layout.size:
        raise SymbolError(
            f"symbol: {name} is {layout.size:#x} bytes; {offset_text} is outside"
        )
    found = locate(ctx, layout, offset)
    if not found:
        raise SymbolError(f"symbol: no named member at {name}+{offset:#x}")
    return [(path, ctype) for path, _, ctype in found]


def _c_references(ctx: Context, name: str) -> list[tuple[str, int]]:
    """Return the file and line of each C use outside comments and strings."""
    out = []
    word = re.compile(r"\b" + re.escape(name) + r"\b")
    for path in grep_files(ctx, name, ["src", "include"]):
        text = (ctx.root / path).read_text(encoding="utf-8", errors="replace")
        masked = ctext.mask(text)
        for number, (_, code) in enumerate(
            zip(text.split("\n"), masked.split("\n"), strict=True), 1
        ):
            if word.search(code):
                out.append((path, number))
    return out


def _asm_references(ctx: Context, name: str) -> list[tuple[str, int, str, str]]:
    """Return the file, line, open function and instruction of each assembly use."""
    out = []
    word = re.compile(r"\b" + re.escape(name) + r"\b")
    for path in grep_files(ctx, name, ["asm"]):
        if not path.endswith(".s"):
            continue
        function = Path(path).stem
        lines = (
            (ctx.root / path).read_text(encoding="utf-8", errors="replace").split("\n")
        )
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


def _xref_path(ctx: Context, image: str) -> Path:
    return ctx.xref_cache / (image.replace("/", "+") + ".json")


def _read_xrefs(ctx: Context, image: str) -> dict | None:
    """Return one image's cached cross-references, when its project stamp still matches."""
    try:
        return json.loads(_xref_path(ctx, image).read_text(encoding="utf-8"))
    except (OSError, ValueError):
        return None


def _write_xrefs(ctx: Context, image: str, data: dict) -> None:
    try:
        ctx.xref_cache.mkdir(parents=True, exist_ok=True)
        handle, tmp = tempfile.mkstemp(dir=ctx.xref_cache, prefix="xrefs-")
        with os.fdopen(handle, "w", encoding="utf-8") as stream:
            json.dump(data, stream, sort_keys=True)
        os.replace(tmp, _xref_path(ctx, image))
    except OSError:
        pass


def _rizin_xrefs(
    ctx: Context, queries: list[tuple[str, int]]
) -> list[tuple[str, int, str]]:
    """Return each image's Rizin cross-references to the queried addresses."""
    by_image: dict[str, set[int]] = collections.defaultdict(set)
    for image, addr in queries:
        by_image[image].add(addr)
    maps: dict[str, dict] = {}
    for image in sorted(by_image):
        project = ctx.root / f"build/meson/rz+{image.replace('/', '+')}.rzdb"
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
        data = _read_xrefs(ctx, image)
        if data is None or data.get("stamp") != stamp or stale:
            result = subprocess.run(
                [str(ctx.root / "bin/rz"), image, "aaa", "axlj", f"Ps {project}"],
                cwd=ctx.root,
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
            _write_xrefs(ctx, image, data)
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


@dataclass(frozen=True)
class UsesResult:
    image: str | None
    at: AtRow | None
    c: list[tuple[str, int]]
    asm: list[tuple[str, int, str, str]]
    rizin: list[tuple[str, int, str]]


def uses(ctx: Context, spec: str) -> UsesResult:
    """Return every C, assembly and Rizin reference to a symbol or address."""
    data = read_symbols(ctx.root)
    name = None
    queries: list[tuple[str, int]] = []
    image = at_row = None
    if "@" in spec:
        image, _, address = spec.rpartition("@")
        if not image or "/" not in image:
            raise SymbolError("symbol: uses takes NAME or IMAGE@0xADDR")
        addr = _address(address)
        rows = {
            table: table_rows(data, table) for table in _visible_tables(data, image)
        }
        following = {table: next_addresses(rows[table]) for table in rows}
        hits = find_hits(ctx, rows, following, image, addr)
        if hits:
            name = hits[0][0].name
        at_row = AtRow(addr, _owners(ctx, hits[:1], addr))
        queries.append((image, addr))
    else:
        name = spec
        for table, rows in data.items():
            row = rows.get(name)
            if isinstance(row, dict) and "addr" in row and not row.get("alias"):
                queries.append((table, int(row["addr"])))
    return UsesResult(
        image,
        at_row,
        _c_references(ctx, name) if name is not None else [],
        _asm_references(ctx, name) if name is not None else [],
        _rizin_xrefs(ctx, queries),
    )
