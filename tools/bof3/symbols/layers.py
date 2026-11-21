"""Order every function into call-graph layers."""

from __future__ import annotations

import collections
import hashlib
import re
from dataclasses import dataclass
from pathlib import Path

from bof3.adapters.config import read_symbols
from bof3.errors import SymbolError
from bof3.source import ctext
from bof3.source.decls import Decl
from bof3.symbols.context import RESIDENT, Context, Table
from bof3.symbols.headers import IDENT, _match_brace

LAYER_RESIDENT = RESIDENT


FUNC_ADDRESS_NAME = re.compile(r"func_[0-9A-F]{8}$")


NON_MATCHING_DEF = re.compile(r"\bNON_MATCHING\b")


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
    definition: Decl | None = None


def _layer_manifests(ctx: Context) -> dict:
    from bof3.resolve import load_target_manifests

    manifests = load_target_manifests(ctx.root)
    if not manifests:
        raise SymbolError("layers: no targets under config/")
    return manifests


def _index_nodes(ctx: Context, manifests: dict) -> list[LayerNode] | None:
    """Return the built function index when every image is present, else None."""
    from bof3.source.index import load_index

    elfs = list((ctx.root / "build/meson").glob("*.elf"))
    if len(elfs) < len(manifests):
        return None
    funcs = load_index(ctx.root)
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


def _splat_nodes(ctx: Context, manifests: dict) -> list[LayerNode]:
    """Return every split function without a build, with its bytes hashed for copies."""
    from bof3.resolve.layout import parse_splat_layout

    nodes = []
    seen = set()
    for image, manifest in manifests.items():
        layout = parse_splat_layout(ctx.root / manifest.splat, manifest.load_address)
        payload_path = ctx.root / manifest.binary
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


def _layer_tree(ctx: Context):
    """Read every tracked C file once for definitions, calls and data initializers."""
    from bof3.source import decls

    texts = {name: ctext.read(ctx.root, name) for name in ctext.tracked_c(ctx.root)}
    return decls.Tree(texts=texts)


def _visible_files(tree, manifest) -> set[str]:
    folder = manifest.source_dir
    outside = set(manifest.outside_sources)
    visible: set[str] = set()
    for name in tree.texts:
        if (name.startswith(folder + "/") or name in outside) and name.endswith(".c"):
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


def _asm_path(ctx: Context, image: str, name: str) -> Path | None:
    for folder in (ctx.root / "build/asm" / image, ctx.root / "asm" / image / "hand"):
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

    owners = {
        path: image
        for image, manifest in manifests.items()
        for path in manifest.outside_sources
    }

    def image_of(name: str) -> str | None:
        if name in owners:
            return owners[name]
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
    ctx: Context,
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
    path = _asm_path(ctx, node.image, node.name)
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


def _layer_layouts(ctx: Context, manifests: dict) -> tuple[dict, dict]:
    """Return each target's reviewed layout and retail payload."""
    from bof3.resolve.layout import parse_splat_layout

    layouts = {}
    payloads = {}
    for image, manifest in manifests.items():
        layouts[image] = parse_splat_layout(
            ctx.root / manifest.splat, manifest.load_address
        )
        try:
            payloads[image] = (ctx.root / manifest.binary).read_bytes()
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
    """Return each node's layer: 0 when it calls no game function, else 1 + its deepest callee."""
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


def layers(ctx: Context) -> Table:
    """Print the call-graph layer of every function of every image."""
    manifests = _layer_manifests(ctx)
    index_nodes = _index_nodes(ctx, manifests)
    notes = ()
    if index_nodes is None:
        notes = (
            "symbol: no complete built image index; reading the split layouts by unit",
        )
        nodes = _splat_nodes(ctx, manifests)
    else:
        nodes = index_nodes
    if not nodes:
        raise SymbolError("layers: no functions found")
    nodes.sort(key=lambda node: (node.image, node.addr, node.name))
    tree = _layer_tree(ctx)
    _prepare_nodes(nodes, manifests, tree)
    by_file = _defs_by_file(tree)
    calls_by_file: dict[str, list] = collections.defaultdict(list)
    for call in tree.calls:
        calls_by_file[call.file].append(call)
    known = {node.name for node in nodes}
    tables, table_names = _layer_tables(tree, known, manifests)
    symbols = read_symbols(ctx.root)
    for rows in symbols.values():
        for name, row in rows.items():
            if isinstance(row, dict) and _looks_like_table(row):
                table_names.add(name)
    layouts, payloads = _layer_layouts(ctx, manifests)
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
                ctx,
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
    keys = "image name address layer callers callees status named copies shared"
    return Table(
        keys,
        rows,
        notes,
        cells=lambda row: [
            ",".join(v) if k == "callees" else str(v) for k, v in row.items()
        ],
    )
