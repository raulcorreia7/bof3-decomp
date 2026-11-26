"""List the reads and writes of a record or global."""

from __future__ import annotations

import collections
import re

from bof3.adapters.config import read_symbols
from bof3.errors import SymbolError
from bof3.source import ctext
from bof3.symbols.context import Context, Table
from bof3.symbols.headers import record_blocks, source_files
from bof3.symbols.layers import LAYER_RESIDENT, _layer_manifests, _layer_tree
from bof3.symbols.mips import (
    MIPS_READ,
    MIPS_WRITE,
    AccessRange,
    MipsAccess,
    decode_accesses,
)
from bof3.symbols.probe import SCALAR_WIDTH, _known_width, locate, type_layout


def _normalized_type(value: str) -> str:
    return " ".join(value.replace("*", " * ").split())


def _pointer_target(value: str) -> str | None:
    text = _normalized_type(value)
    return text[:-2].strip() if text.endswith(" *") else None


def _task_types(ctx: Context) -> dict[str, str]:
    """Return image -> the record type its g_Self macro reads the scratchpad cell as."""
    pattern = re.compile(
        r"#\s*define\s+g_Self\s+\(\(\s*(?:volatile\s+)?(\w+)\s*\*\s*\)\s*g_Self\s*\)"
    )
    headers = []
    for path in (ctx.root / "src").rglob("*.h"):
        text = path.read_text(encoding="utf-8", errors="replace")
        match = pattern.search(text)
        if match is not None:
            headers.append(
                (path.parent.relative_to(ctx.root).as_posix(), match.group(1))
            )
    found: dict[str, str] = {}
    for image, manifest in _layer_manifests(ctx).items():
        folder = manifest.source_dir
        best: tuple[int, str] | None = None
        for parent, type_name in headers:
            if folder == parent or folder.startswith(parent + "/"):
                if best is None or len(parent) > best[0]:
                    best = (len(parent), type_name)
        if best is not None:
            found[image] = best[1]
    return found


def _c_member_uses(
    ctx: Context, names: set[str]
) -> dict[str, list[tuple[str, int, str]]]:
    """Return one entry per ``.member``/``->member`` use of the names, comments masked."""
    pattern = re.compile(r"(?:->|\.)\s*(\w+)")
    found: dict[str, list[tuple[str, int, str]]] = collections.defaultdict(list)
    if not names:
        return found
    for path, text in source_files(ctx, headers=False):
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
    ctx: Context,
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
            found = locate(ctx, layout, offset)
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
                last = locate(ctx, layout, offset + width - 1)
                first = locate(ctx, layout, offset)
                if first and last and first[0][0] != last[0][0]:
                    problems.append("straddles members")
        item["member"] = member
        item["member_type"] = member_type
        item["problem"] = ", ".join(dict.fromkeys(problems))
        out.append(item)
    return out


def _index_by_image(ctx: Context) -> dict[str, list]:
    """Return every indexed function grouped by image; accesses need the built images."""
    from bof3.source.index import load_index

    funcs = load_index(ctx.root)
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
    ctx: Context,
    name: str,
    layout,
    accesses: list[MipsAccess],
    c_uses: dict[str, list[tuple[str, int, str]]],
    kind: str,
) -> list[dict]:
    rows = _aggregate_accesses(ctx, layout, accesses, c_uses)
    for row in rows:
        row["name"] = name
        row["kind"] = kind
    return rows


def accesses(ctx: Context, name: str) -> Table:
    """List the reads and writes of a record type or a global, per offset."""
    data = read_symbols(ctx.root)
    globals_found: list[tuple[str, dict]] = []
    for table, rows in data.items():
        row = rows.get(name)
        if isinstance(row, dict) and "addr" in row and not row.get("alias"):
            globals_found.append((table, row))
    functions = _index_by_image(ctx)
    images = sorted(functions)
    task_types = _task_types(ctx)
    all_accesses: list[MipsAccess] = []
    counts = [0, 0]

    def scan(
        scanned: list[str], ranges: list[AccessRange], cells: dict[int, str]
    ) -> None:
        for image in scanned:
            names = {func.addr: func.name for func in functions.get(image, ())}
            found, traced, untraced = _scan_image(
                image, functions, ranges, cells, names
            )
            all_accesses.extend(found)
            counts[0] += traced
            counts[1] += untraced

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
            row_layout = type_layout(ctx, type_name) if type_name else None
            if row_layout is not None and row_layout.record:
                layout = row_layout
            extent = _row_extent(row, row_layout)
            start = int(row["addr"])
            item_range = AccessRange(start, start + extent, name, type_name)
            scan(_visible_images(table, images), [item_range], {})
        member_names = (
            {member.path.rsplit(".", 1)[-1] for member in layout.members}
            if layout is not None
            else set()
        )
        if member_names:
            all_uses = _c_member_uses(ctx, member_names)
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
        layout = type_layout(ctx, name)
        if layout is None or not layout.record:
            raise SymbolError(f"symbol: {name} is neither a global nor a record type")
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
            scan(_visible_images(table, images), [item_range], {})
        for table, row in pointer_rows:
            cell = int(row["addr"])
            scan(_visible_images(table, images), [], {cell: name})
        for image, task_type in task_types.items():
            if task_type == _normalized_type(name):
                scan([image], [], {0x1F800044: name})
        member_names = {member.path.rsplit(".", 1)[-1] for member in layout.members}
        c_uses = _c_member_uses(ctx, member_names)
        all_accesses = [access for access in all_accesses if access.type_name == name]
    rows = _access_rows(ctx, name, layout, all_accesses, c_uses, kind)
    notes = ()
    traced, untraced = counts
    if traced + untraced:
        share = 100.0 * traced / (traced + untraced)
        notes = (
            f"accesses: traced {traced} of {traced + untraced} memory operations "
            f"({share:.1f}%)",
        )
    keys = "name kind offset widths reads writes member member_type examples constants slots problem"
    return Table(keys, rows, notes, cells=_access_cells)


def _access_cells(row: dict) -> list[str]:
    widths = ",".join(f"{key}:{value}" for key, value in sorted(row["widths"].items()))
    return [
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


TYPEDEF_RECORD = re.compile(r"(?m)^\s*typedef\s+(?:struct|union)\s+(\w+)\s+(\w+)\s*;")


def _record_definitions(
    ctx: Context,
) -> tuple[dict[str, int], dict[str, str], set[str]]:
    """Return each record name's definition count, its first header, and the record names."""
    counts: dict[str, int] = collections.Counter()
    header: dict[str, str] = {}
    names: set[str] = set()
    for path, text in source_files(ctx, psyq=True):
        masked = ctext.mask(text)
        for _opening, _closing, found in record_blocks(masked):
            for name in found:
                counts[name] += 1
                header.setdefault(name, path)
                names.add(name)
        for match in TYPEDEF_RECORD.finditer(masked):
            name = match.group(2)
            counts[name] += 1
            header.setdefault(name, path)
            names.add(name)
    return dict(counts), header, names


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


def records(ctx: Context) -> Table:
    """Summarise every record: size, members, duplicates, globals, parameters and accesses."""
    counts, header, names = _record_definitions(ctx)
    layouts = {}
    for name in sorted(names):
        layout = type_layout(ctx, name)
        if layout is not None and layout.record:
            layouts[name] = layout
    symbols = read_symbols(ctx.root)
    global_counts = _record_globals(symbols, set(layouts))
    tree = _layer_tree(ctx)
    param_counts = _record_params(tree, set(layouts))
    member_names = {
        member.path.rsplit(".", 1)[-1]
        for layout in layouts.values()
        for member in layout.members
    }
    c_uses = _c_member_uses(ctx, member_names)
    functions = _index_by_image(ctx)
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
        members = list(layout.members)
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
    keys = "record size members unknown definitions same_layout globals params accesses header"
    return Table(keys, rows)
