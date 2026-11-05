"""Symbols: the one tracked table, the files generated from it, and link-time resolution.

``config/symbols.toml`` is the only hand-kept symbol file. One table per target holds that
target's rows, one row per name:

    ["exe/slus_004_22"]
    SND_PlayCue = { addr = 0x8015DF18, type = "func", source = "..." }

A row takes ``addr`` (required), ``type`` and ``size`` (Splat attributes), ``source`` (the evidence),
and ``alias`` (a name only the link reads; Splat never sees it, and it may sit inside another
row). :func:`generate` writes two files per target
into ``build/symbols``: ``<target>.splat`` for Splat and ``<target>.link`` for the link.

An image's objects name two kinds of external symbols. An address name (``D_80140000``,
``func_8014AA04``, ``jtbl_8014AA04``, or the same behind an upper-case prefix such as
``SCENA16_D_80010004``) spells its address. A readable name (``g_Zenny``) takes its address from a
row of a map the image can see. :func:`resolve` answers for one image from its objects; a name
that cannot be resolved for certain is an error that names the row and the fix.

:func:`target_rows` is the one function that reads a target's rows from the table.
"""

from __future__ import annotations

import re
import subprocess
from pathlib import Path
from typing import TYPE_CHECKING, NamedTuple

from bof3.core.cache import file_memo
from bof3.core.paths import BUILD, CONFIG

if TYPE_CHECKING:
    from bof3.state.rows import Row

__all__ = [
    "ADDRESS_NAME",
    "LinkError",
    "address_of",
    "generate",
    "link_map",
    "imported_map",
    "link_owners",
    "load",
    "resolve",
    "splat_map",
    "splat_owners",
    "target_rows",
]

TABLE = f"{CONFIG}/symbols.toml"
#: Generated per-target files.
OUT = f"{BUILD}/symbols"

#: ``D_`` data, ``func_`` code and ``jtbl_`` jump tables, optionally behind an upper-case
#: image prefix; the eight hex digits are the address.
ADDRESS_NAME = re.compile(r"^(?:[A-Z][A-Z0-9]*_)*(?:D|func|jtbl)_([0-9A-Fa-f]{8})$")

_NAME = re.compile(r"^[A-Za-z_]\w*$")
_TYPE = re.compile(r"^[A-Za-z_][\w*]*$")
_KEYS = ("addr", "type", "size", "source", "alias")
_ASSIGNMENT = re.compile(r"^\s*([A-Za-z_]\w*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", re.MULTILINE)
_SCRIPT_SYMBOL = re.compile(r"^\s*(?:PROVIDE\()?\s*([A-Za-z_]\w*)\s*=", re.MULTILINE)


class LinkError(Exception):
    """A symbol cannot be handled for certain; the message states the fix."""


class Entry(NamedTuple):
    """One table row."""

    name: str
    addr: int
    type: str = ""
    size: int = 0
    source: str = ""
    alias: bool = False

    @property
    def attributes(self) -> str:
        """The Splat attribute text of the row (no evidence, no link-only marks)."""
        parts = []
        if self.type:
            parts.append(f"type:{self.type}")
        if self.size:
            parts.append(f"size:0x{self.size:X}")
        return " ".join(parts)

    def row(self) -> Row:
        """The row in the form tools read: name, address and a Splat-style comment."""
        parts = [self.attributes]
        if self.alias:
            parts.append("alias:true")
        if self.source:
            parts.append(f'source="{self.source}"')
        from bof3.state.rows import Row

        return Row(self.name, self.addr, " ".join(p for p in parts if p))


def address_of(name: str) -> int | None:
    """Return the address an address name spells, or None for a readable name."""
    match = ADDRESS_NAME.match(name)
    return int(match[1], 16) if match else None


def _flat(target: str) -> str:
    return target.replace("/", "+")


def splat_map(target: str) -> str:
    """Return the repository path of a target's generated Splat map."""
    return f"{OUT}/{_flat(target)}.splat"


def link_map(target: str) -> str:
    """Return the repository path of a target's generated link map."""
    return f"{OUT}/{_flat(target)}.link"


def splat_owners(root: Path, target: str) -> list[str]:
    """Return the targets whose rows Splat reads for ``target``, in order."""
    from bof3.resolve.layout import read_splat

    _, document = read_splat(root / CONFIG / target / "splat.yaml")
    return list(document["symbol_owners"])


def link_owners(root: Path, target: str) -> list[str]:
    """Return the targets whose rows an image may link against.

    The image itself, the resident images ``config/link.toml`` shows to it, then the maps Splat
    reads for it (twin overlays share names).
    """
    import tomllib

    link = tomllib.loads((root / CONFIG / "link.toml").read_text(encoding="utf-8"))
    kind = target.split("/", 1)[0]
    order = [target]
    for entry in link.get("resident", ()):
        if (kind in entry["visible_to"] or target in entry["visible_to"]) and (
            entry["target"] not in order
        ):
            order.append(entry["target"])
    order += [o for o in splat_owners(root, target) if o not in order]
    return order


def _row_error(target: str, name: str, problem: str, fix: str) -> LinkError:
    return LinkError(f"{TABLE} [{target}] {name}: {problem}. {fix}")


def _entry(target: str, name: str, value: object) -> Entry:
    if not _NAME.match(name):
        raise _row_error(
            target, name, "the name is not a C identifier", "Rename the row."
        )
    if not isinstance(value, dict):
        raise _row_error(
            target,
            name,
            "the row is not an inline table",
            f"Write `{name} = {{ addr = 0x... }}`.",
        )
    unknown = sorted(set(value) - set(_KEYS))
    if unknown:
        raise _row_error(
            target, name, f"unknown key {unknown[0]!r}", f"Use only {', '.join(_KEYS)}."
        )
    addr = value.get("addr")
    if (
        not isinstance(addr, int)
        or isinstance(addr, bool)
        or not 0 <= addr <= 0xFFFFFFFF
    ):
        raise _row_error(
            target,
            name,
            "`addr` is missing or not a 32-bit integer",
            "Write `addr = 0x8015DF18`.",
        )
    size = value.get("size", 0)
    if not isinstance(size, int) or isinstance(size, bool) or size < 0:
        raise _row_error(
            target, name, "`size` is not a byte count", "Write `size = 0x10`."
        )
    type_ = value.get("type", "")
    if not isinstance(type_, str) or (type_ and not _TYPE.match(type_)):
        raise _row_error(
            target,
            name,
            "`type` is not one word",
            'Write `type = "func"` or a C type name.',
        )
    source = value.get("source", "")
    if not isinstance(source, str) or '"' in source or "\n" in source:
        raise _row_error(
            target,
            name,
            "`source` is not a one-line string without quotes",
            "Reword the evidence.",
        )
    alias = value.get("alias", False)
    if not isinstance(alias, bool):
        raise _row_error(
            target, name, "`alias` is not true or false", "Write `alias = true`."
        )
    return Entry(name, addr, type_, size, source, alias)


def _overlaps(target: str, entries: list[Entry]) -> list[str]:
    """Return a message per row whose range overlaps an earlier row without a recorded reason."""
    problems = []
    ordered = sorted(entries, key=lambda e: e.addr)
    reach = 0
    holder = None
    for entry in ordered:
        if holder is not None and entry.addr < reach:
            if not (entry.alias or holder.alias):
                problems.append(
                    f"{TABLE} [{target}] {entry.name} (0x{entry.addr:08X}) overlaps {holder.name} "
                    f"(0x{holder.addr:08X}+0x{max(holder.size, 1):X}). Fix an address or size, or "
                    "mark the second name `alias = true` (a link-only name)."
                )
        end = entry.addr + max(entry.size, 1)
        if holder is None or end >= reach:
            reach, holder = end, entry
    return problems


def load(root: Path) -> dict[str, list[Entry]]:
    """Return every target's rows in file order; a bad row is a :class:`LinkError`."""
    import tomllib

    path = root / TABLE

    def read() -> dict[str, list[Entry]]:
        try:
            document = tomllib.loads(path.read_text(encoding="utf-8"))
        except tomllib.TOMLDecodeError as error:
            raise LinkError(f"{TABLE}: {error}. Fix the line named above.") from None
        tables: dict[str, list[Entry]] = {}
        problems: list[str] = []
        for target, rows in document.items():
            if not (root / CONFIG / target / "splat.yaml").is_file():
                raise LinkError(
                    f"{TABLE}: [{target}] names no target. Use a folder id under config/ "
                    "that holds a splat.yaml."
                )
            if not isinstance(rows, dict):
                raise LinkError(
                    f'{TABLE}: [{target}] is not a table. Write `["{target}"]`.'
                )
            entries = [_entry(target, name, value) for name, value in rows.items()]
            problems += _overlaps(target, entries)
            tables[target] = entries
        if problems:
            raise LinkError("\n".join(problems))
        return tables

    return file_memo("symbols-table", [path], None, read)


def target_rows(root: Path, target: str) -> list[Row]:
    """Return one target's own rows, sorted by address.

    Every reader of the table goes through this function, so the file format is a detail of
    this module.
    """
    entries = sorted(load(root).get(target, ()), key=lambda e: e.addr)
    return [entry.row() for entry in entries]


def generate(root: Path) -> None:
    """Write ``build/symbols/<target>.splat`` and ``.link`` for every target.

    A file is written only when its bytes change, so editing one row touches one target's files.
    """
    from bof3.link.inputs import write_if_changed

    tables = load(root)
    for yaml_path in sorted((root / CONFIG).rglob("splat.yaml")):
        target = yaml_path.parent.relative_to(root / CONFIG).as_posix()
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
    """Return the Splat map text a target imports from its other owners.

    A twin overlay may name a function that the target also defines elsewhere; Splat 0.50 keeps
    both addresses and the link then finds two. The target's own address wins, so an owner's
    row is dropped when the target holds a row of the same name at another address.
    """
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


def read_maps(root: Path, maps: list[str]) -> dict[str, dict[int, str]]:
    """Return ``name -> {address: owning target}`` over generated link maps."""
    table: dict[str, dict[int, str]] = {}
    for relative in maps:
        owner = Path(relative).stem.replace("+", "/")
        for line in (root / relative).read_text(encoding="utf-8").splitlines():
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
    """Return ``name -> address`` for every undefined name an image's objects need.

    ``script_names`` are names the link scripts already define; ``assigned`` are the
    ``name = address`` rows among them, which must agree with the maps. A ``partial`` link
    leaves a name with no address to the caller.
    """
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
                    f"{name}: the split link script gives 0x{expected:08X} but {TABLE} gives "
                    f"{_where(rows)}. Fix the row so one address remains."
                )
            continue
        if spelled is not None:
            if rows and set(rows) != {spelled}:
                problems.append(
                    f"{name}: the name spells 0x{spelled:08X} but {TABLE} gives {_where(rows)}. "
                    "Rename the row or fix its address."
                )
            else:
                result[name] = spelled
        elif len(rows) == 1:
            result[name] = next(iter(rows))
        elif rows:
            problems.append(
                f"{name} (needed by {Path(owner).name}) has {len(rows)} addresses visible to "
                f"{target}: {_where(rows)}. Rename one of the rows in {TABLE} so each name has "
                "one address."
            )
        elif not partial:
            problems.append(
                f"{name} (needed by {Path(owner).name}) has no address. Add "
                f"`{name} = {{ addr = 0x... }}` to [{target}] in {TABLE}, or fix the spelling."
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


def render(symbols: dict[str, int], checks: list[str] = ()) -> str:
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
    """Return one ``ASSERT`` per row of the image's own table that its objects define.

    The linker proves the row's address against the address the image gave the symbol; a
    wrong row fails the link, and :func:`explain` then names both addresses.
    """
    table = read_maps(root, maps)
    return [
        f'ASSERT({name} == 0x{addr:08X}, "{TABLE} [{target}] {name}: the row says '
        f'0x{addr:08X} but the image links it elsewhere");'
        for name in sorted(defined & table.keys())
        for addr, owner in table[name].items()
        if owner == target
    ]


_MAP_SYMBOL = re.compile(r"^\s+0x([0-9a-f]+)\s+([A-Za-z_]\w*)\s*$")


def explain(root: Path, target: str, map_path: Path) -> list[str]:
    """Return a message per row of ``target``'s table that the linked image places elsewhere.

    ``map_path`` is the ``-Map`` file ld writes even when an ``ASSERT`` fails the link.
    """
    own = read_maps(root, [link_map(target)])
    placed: dict[str, int] = {}
    try:
        text = map_path.read_text(encoding="utf-8", errors="replace")
    except OSError:
        return []
    for line in text.splitlines():
        match = _MAP_SYMBOL.match(line)
        if match and match[2] in own:
            placed.setdefault(match[2], int(match[1], 16) & 0xFFFFFFFF)
    return [
        f"{TABLE} [{target}] {name}: the row says 0x{want:08X} but the image links it at "
        f"0x{placed[name]:08X}. Fix the row's address, or the source that moved the symbol."
        for name, rows in sorted(own.items())
        if name in placed
        for want in rows
        if want != placed[name]
    ]
