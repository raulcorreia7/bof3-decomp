"""Symbols: the one tracked table, the files generated from it, and link-time resolution."""

from __future__ import annotations

import re
import subprocess
from collections.abc import Sequence
from pathlib import Path
from typing import NamedTuple

from bof3.adapters.config import (
    has_splat,
    read_lines,
    read_link,
    read_symbols,
    splat_owners,
    splat_targets,
    symbol_files,
)
from bof3.core.cache import file_memo
from bof3.core.paths import BUILD
from bof3.symbols import SPLIT, Entry, LinkError, overlaps, table_entries

__all__ = [
    "ADDRESS_NAME",
    "Entry",
    "LinkError",
    "MapSymbol",
    "address_of",
    "generate",
    "link_map",
    "imported_map",
    "link_owners",
    "load",
    "read_map",
    "resolve",
    "splat_map",
    "splat_owners",
    "target_rows",
]

#: Generated per-target files.
OUT = f"{BUILD}/symbols"

#: ``D_`` data, ``func_`` code and ``jtbl_`` jump tables, optionally behind an upper-case
#: image prefix; the eight hex digits are the address.
ADDRESS_NAME = re.compile(r"^(?:[A-Z][A-Z0-9]*_)*(?:D|func|jtbl)_([0-9A-Fa-f]{8})$")

_ASSIGNMENT = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", re.MULTILINE)
_SCRIPT_SYMBOL = re.compile(r"^\s*(?:PROVIDE\()?\s*([A-Za-z_]\w*)\s*=", re.MULTILINE)


def address_of(name: str) -> int | None:
    """Return the address an address name spells, or None for a readable name."""
    match = ADDRESS_NAME.match(name)
    return int(match[1], 16) if match else None


def _flat(target: str) -> str:
    return target.replace("/", "+")


def splat_map(target: str) -> str:
    return f"{OUT}/{_flat(target)}.splat"


def link_map(target: str) -> str:
    return f"{OUT}/{_flat(target)}.link"


def link_owners(root: Path, target: str) -> list[str]:
    """Return the targets whose rows an image may link against."""
    link = read_link(root)
    kind = target.split("/", 1)[0]
    order = [target]
    for entry in link.get("resident", ()):
        if (kind in entry["visible_to"] or target in entry["visible_to"]) and (
            entry["target"] not in order
        ):
            order.append(entry["target"])
    order += [o for o in splat_owners(root, target) if o not in order]
    return order


def load(root: Path) -> dict[str, list[Entry]]:
    """Return every target's rows in file order; a bad row is a :class:`LinkError`."""

    def read() -> dict[str, list[Entry]]:
        document = read_symbols(root)
        tables: dict[str, list[Entry]] = {}
        problems: list[str] = []
        for target, rows in document.items():
            if not has_splat(root, target):
                raise LinkError(
                    f"{SPLIT}: [{target}] names no target. Use a folder id under config/ "
                    "that holds a splat.yaml."
                )
            if not isinstance(rows, dict):
                raise LinkError(
                    f'{SPLIT}: [{target}] is not a table. Write `["{target}"]`.'
                )
            entries = table_entries(target, rows)
            problems += overlaps(target, entries)
            tables[target] = entries
        if problems:
            raise LinkError("\n".join(problems))
        return tables

    return file_memo("symbols-table", symbol_files(root), None, read)


def target_rows(root: Path, target: str) -> list[Entry]:
    """Return one target's own rows, sorted by address."""
    return sorted(load(root).get(target, ()), key=lambda e: e.addr)


def generate(root: Path) -> None:
    """Write ``build/symbols/<target>.splat`` and ``.link`` for every target."""
    from bof3.link.inputs import write_if_changed

    tables = load(root)
    for target in splat_targets(root):
        ordered = sorted(tables.get(target, ()), key=lambda e: e.addr)
        splat = [
            f"{e.name} = 0x{e.addr:08X};"
            + (f" // {e.attributes}" if e.attributes else "")
            + "\n"
            for e in ordered
            if not e.alias
        ]
        link = [f"{e.name} 0x{e.addr:08X}\n" for e in ordered]
        write_if_changed(root / splat_map(target), "".join(splat))
        write_if_changed(root / link_map(target), "".join(link))


def imported_map(root: Path, target: str) -> str:
    """Return the Splat map text a target imports from its other owners."""
    tables = load(root)
    own = {e.name: e.addr for e in tables.get(target, ())}
    lines = []
    for owner in splat_owners(root, target):
        if owner == target:
            continue
        for e in sorted(tables.get(owner, ()), key=lambda e: e.addr):
            if e.alias or own.get(e.name, e.addr) != e.addr:
                continue
            attributes = f" // {e.attributes}" if e.attributes else ""
            lines.append(f"{e.name} = 0x{e.addr:08X};{attributes}\n")
    return "".join(lines)


class Scan(NamedTuple):
    """What an image's objects define and need."""

    defined: frozenset[str]
    #: Undefined name -> the first object that needs it.
    needed: dict[str, str]


def scan_objects(nm: Path, objects: list[str]) -> Scan:
    """Read the external symbols of ``objects`` with ``nm``."""
    defined: set[str] = set()
    needed: dict[str, str] = {}
    chunk = 400
    for start in range(0, len(objects), chunk):
        batch = objects[start : start + chunk]
        run = subprocess.run(
            [str(nm), "-g", "-A", "-P", *batch],
            capture_output=True,
            text=True,
            check=False,
        )
        if run.returncode:
            raise LinkError(f"nm failed: {run.stderr.strip() or run.stdout.strip()}")
        for line in run.stdout.splitlines():
            fields = line.split()
            if len(fields) < 3:
                continue
            path = fields[0].removesuffix(":")
            name, kind = fields[1], fields[2]
            if kind == "U":
                needed.setdefault(name, path)
            elif kind not in ("w", "v", "W", "V"):
                defined.add(name)
    return Scan(frozenset(defined), needed)


class MapSymbol(NamedTuple):
    """One symbol a linker map places: its name, address, size and kind."""

    name: str
    address: int
    size: int
    function: bool


_CONTRIBUTION = re.compile(
    r"^\s+(?:(\.\S+)\s+)?0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+\S+\.o$"
)
_MAP_SECTION = re.compile(r"^ (\.\S+)$")
_MAP_SYMBOL = re.compile(r"^\s+0x([0-9a-f]+)\s+([A-Za-z_]\w*)\s*$")
_MAP_ABSOLUTE = re.compile(r"^\s+0x([0-9a-f]{8})\s+([A-Za-z_]\w*)\s+=\s+0x([0-9a-f]+)$")
_PLACED = (".text", ".data", ".rodata", ".sdata", ".bss", ".sbss", ".rdata")


def read_map(path: Path) -> list[MapSymbol]:
    """Return the symbols a linker map lists under placed input sections."""
    symbols: list[MapSymbol] = []
    section = ""
    pending = ""
    start = end = 0
    names: list[tuple[int, str]] = []

    def flush() -> None:
        for index, (address, name) in enumerate(names):
            top = names[index + 1][0] if index + 1 < len(names) else end
            symbols.append(MapSymbol(name, address, top - address, section == ".text"))
        names.clear()

    for line in read_lines(path, "replace"):
        wrapped = _MAP_SECTION.match(line)
        if wrapped is not None:
            pending = wrapped[1]
            continue
        match = _CONTRIBUTION.match(line)
        if match is not None:
            flush()
            name = match[1] or pending
            pending = ""
            start, size = int(match[2], 16), int(match[3], 16)
            section = name if name in _PLACED else ""
            end = start + size
            if start < 0x80000000 or not size:
                section = ""
            continue
        absolute = _MAP_ABSOLUTE.match(line)
        if absolute is not None and int(absolute[1], 16) == int(absolute[3], 16):
            symbols.append(MapSymbol(absolute[2], int(absolute[1], 16), 0, False))
            continue
        match = _MAP_SYMBOL.match(line)
        if section and match is not None and start <= int(match[1], 16) < end:
            names.append((int(match[1], 16), match[2]))
    flush()
    return symbols


def read_maps(root: Path, maps: list[str]) -> dict[str, dict[int, str]]:
    """Return ``name -> {address: owning target}`` over generated link maps."""
    table: dict[str, dict[int, str]] = {}
    for relative in maps:
        owner = Path(relative).stem.replace("+", "/")
        for line in read_lines(root / relative):
            name, _, value = line.partition(" ")
            table.setdefault(name, {}).setdefault(int(value, 16), owner)
    return table


def resolve(
    root: Path,
    target: str,
    maps: list[str],
    scan: Scan,
    script_names: frozenset[str],
    assigned: dict[str, int],
    *,
    partial: bool = False,
) -> dict[str, int]:
    """Return ``name -> address`` for every undefined name an image's objects need."""
    table = read_maps(root, maps)
    result: dict[str, int] = {}
    problems: list[str] = []
    for name, owner in sorted(scan.needed.items()):
        if name in scan.defined:
            continue
        spelled = address_of(name)
        rows = table.get(name, {})
        if name in assigned or name in script_names:
            expected = assigned.get(name)
            if expected is not None and rows and set(rows) != {expected}:
                problems.append(
                    f"{name}: the split link script gives 0x{expected:08X} but {SPLIT} gives "
                    f"{_where(rows)}. Fix the row so one address remains."
                )
            continue
        if spelled is not None:
            if rows and set(rows) != {spelled}:
                problems.append(
                    f"{name}: the name spells 0x{spelled:08X} but {SPLIT} gives {_where(rows)}. "
                    "Rename the row or fix its address."
                )
            else:
                result[name] = spelled
        elif len(rows) == 1:
            result[name] = next(iter(rows))
        elif rows:
            problems.append(
                f"{name} (needed by {Path(owner).name}) has {len(rows)} addresses visible to "
                f"{target}: {_where(rows)}. Rename one of the rows in {SPLIT} so each name has "
                "one address."
            )
        elif not partial:
            problems.append(
                f"{name} (needed by {Path(owner).name}) has no address. Add "
                f"`{name} = {{ addr = 0x... }}` to [{target}] in {SPLIT}, or fix the spelling."
            )
    if problems:
        raise LinkError(
            f"{target}: cannot resolve {len(problems)} symbol(s) for certain:\n  "
            + "\n  ".join(problems)
        )
    return result


def _where(rows: dict[int, str]) -> str:
    return ", ".join(f"0x{a:08X} ([{t}])" for a, t in sorted(rows.items()))


def script_symbols(texts: list[str]) -> tuple[frozenset[str], dict[str, int]]:
    """Return the names link scripts define, and the ``name = 0xADDRESS;`` rows among them."""
    names: set[str] = set()
    rows: dict[str, int] = {}
    for text in texts:
        names.update(match[1] for match in _SCRIPT_SYMBOL.finditer(text))
        rows.update((m[1], int(m[2], 16)) for m in _ASSIGNMENT.finditer(text))
    return frozenset(names), rows


def render(symbols: dict[str, int], checks: Sequence[str] = ()) -> str:
    """Return the link script text: ``symbols`` where nothing else defines them, then ``checks``."""
    lines = ["/* Generated by tools/link_symbols.py; never edit. */\n"]
    lines += [
        f"PROVIDE({name} = 0x{addr:08X});\n" for name, addr in sorted(symbols.items())
    ]
    lines += [line + "\n" for line in checks]
    return "".join(lines)


def own_checks(
    root: Path, target: str, maps: list[str], defined: frozenset[str]
) -> list[str]:
    """Return one ``ASSERT`` per row of the image's own table that its objects define."""
    table = read_maps(root, maps)
    return [
        f'ASSERT({name} == 0x{addr:08X}, "{SPLIT} [{target}] {name}: the row says '
        f'0x{addr:08X} but the image links it elsewhere");'
        for name in sorted(defined & table.keys())
        for addr, owner in table[name].items()
        if owner == target
    ]


def explain(root: Path, target: str, map_path: Path) -> list[str]:
    """Return a message per row of ``target``'s table that the linked image places elsewhere."""
    own = read_maps(root, [link_map(target)])
    try:
        mapped = read_map(map_path)
    except OSError:
        return []
    placed: dict[str, int] = {}
    for symbol in mapped:
        if symbol.name in own:
            placed.setdefault(symbol.name, symbol.address)
    return [
        f"{SPLIT} [{target}] {name}: the row says 0x{want:08X} but the image links it at "
        f"0x{placed[name]:08X}. Fix the row's address, or the source that moved the symbol."
        for name, rows in sorted(own.items())
        if name in placed
        for want in rows
        if want != placed[name]
    ]
