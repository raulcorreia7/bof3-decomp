"""Index every split function and each global's extent."""

from __future__ import annotations

import bisect
import collections
import re
from dataclasses import dataclass

from bof3.adapters.config import manifest_layout, read_symbols
from bof3.source import asmtext
from bof3.symbols.accesses import _normalized_type
from bof3.symbols.context import RESIDENT, Context
from bof3.symbols.layers import _layer_manifests, _visible_files
from bof3.symbols.lookup import (
    next_addresses,
    row_span,
    table_range,
    table_rows,
)
from bof3.symbols.probe import SCALAR_WIDTH, Row, type_layout

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
    """A row lookup over config/symbols/<image>.toml: by name, by address and per image."""

    def __init__(self, ctx: Context, data: dict[str, dict[str, dict]]) -> None:
        self.ctx = ctx
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
            self._spans[key] = row_span(
                self.ctx, row, self.following.get(row.table, {})
            )
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
            bounds = table_range(self.ctx, table)
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
    facts: dict[tuple[str, str], asmtext.Facts]
    by_image: dict[str, dict[str, asmtext.Function]]
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


def _asm_functions(ctx: Context, image: str) -> list:
    """Return every split function of one image, read once per process."""
    if image in ctx.asm_functions:
        return ctx.asm_functions[image]
    found: list = []
    folder = ctx.asm_root / image
    split = [
        p
        for p in sorted(folder.rglob("*.s"))
        if "data" not in p.relative_to(folder).parts
    ]
    for path in [*split, *sorted((ctx.root / "asm" / image / "hand").glob("*.s"))]:
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        found.extend(
            asmtext.functions(text, image, path.relative_to(ctx.root).as_posix())
        )
    ctx.asm_functions[image] = found
    return found


def _assembly(ctx: Context) -> Assembly:
    """Read every split function of every image and decode its facts, once per process."""
    if ctx.assembly is not None:
        return ctx.assembly
    manifests = _layer_manifests(ctx)
    index = SymbolIndex(ctx, read_symbols(ctx.root))
    functions = {image: _asm_functions(ctx, image) for image in sorted(manifests)}
    facts: dict[tuple[str, str], asmtext.Facts] = {}
    by_image: dict[str, dict[str, asmtext.Function]] = {}
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
    ctx.assembly = Assembly(functions, facts, by_image, dict(by_name), systems=systems)
    return ctx.assembly


def _visible_sources(tree, manifests: dict) -> dict[str, set[str]]:
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


def _declared_extent(ctx: Context, row: Row) -> int | None:
    """Return the byte extent a row's own declaration states."""
    if row.size is not None:
        return row.size
    text = _normalized_type(row.type)
    if text.endswith(" *"):
        return 4
    width = SCALAR_WIDTH.get(text)
    if width is not None:
        return width
    layout = type_layout(ctx, text) if text and text != "func" else None
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


def _extent_ladders(
    index: SymbolIndex,
) -> tuple[dict[str, list[int]], dict[tuple[str, int], int]]:
    """Each table's sorted data addresses, and the next address after each one."""
    universes: dict[str, list[int]] = {}
    ladders: dict[tuple[str, int], int] = {}
    for table, table_list in index.rows.items():
        addresses = sorted({row.addr for row in table_list if row.type != "func"})
        universes[table] = addresses
        for position, address in enumerate(addresses[:-1]):
            ladders[(table, address)] = addresses[position + 1]
    return universes, ladders


def _manifest_layout(ctx: Context, manifest):
    """The splat layout of an image manifest, or None when it cannot be read."""
    if manifest is None:
        return None
    try:
        return manifest_layout(ctx.root, manifest)
    except (OSError, ValueError):
        return None


def _absorbed_names(
    row, uses: dict, index: SymbolIndex, used_names: set[str], gap: int | None
) -> list[str]:
    """The unused symbols inside ``row``'s gap that its own accesses reach."""
    start = row.addr
    end = start + (gap or 0)
    hit = {
        start + access.offset
        for _image, _function, access in uses.get((row.name, start), ())
    }
    absorbed = []
    for other in index.rows.get(row.table, ()):
        if other.type == "func" or not start < other.addr < end:
            continue
        if other.name == row.name or other.name in used_names:
            continue
        size = index.span(other)
        if any(other.addr <= address < other.addr + size for address in hit):
            absorbed.append(other.name)
    return absorbed


def _extent_rows(
    ctx: Context, assembly: Assembly, index: SymbolIndex, manifests: dict
) -> list[dict]:
    """Build one extent row per data and bss symbol the images hold."""
    if ctx.extent_rows is not None:
        return ctx.extent_rows
    uses = _symbol_uses(assembly, index)
    strides = _symbol_strides(assembly)
    used_names = {name for (name, _address), found in uses.items() if found}
    universes, ladders = _extent_ladders(index)
    rows: list[dict] = []
    for row in _unique_data_rows(index):
        image = index.canonical(row.name, row.addr) or row.table
        layout = _manifest_layout(ctx, manifests.get(image))
        following_address = ladders.get((row.table, row.addr))
        if following_address is not None:
            gap = following_address - row.addr
        else:
            addresses = universes.get(row.table, [])
            gap = addresses[-1] - row.addr if addresses else None
        declared = _declared_extent(ctx, row)
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
        rows.append(
            {
                "symbol": row.name,
                "image": image,
                "address": f"0x{row.addr:08X}",
                "gap": gap,
                "declared_size": declared,
                "stride": sorted(strides.get(row.name, set())),
                "beyond": beyond[:20],
                "beyond_count": len(beyond),
                "absorbs": _absorbed_names(row, uses, index, used_names, gap),
                "section": _section_of(layout, row.addr),
                "type": row.type,
                "evidence": [
                    f"{use_image}@0x{access.address:08X} {function} {access.mnemonic}"
                    for use_image, function, access in found[:5]
                ],
            }
        )
    ctx.extent_rows = rows
    return rows
