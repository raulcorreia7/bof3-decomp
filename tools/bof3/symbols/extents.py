"""Print each global's extent and each symbol's home."""

from __future__ import annotations

import argparse
import collections
import json

from bof3.adapters.config import read_symbols
from bof3.errors import SymbolError
from bof3.symbols.assembly import (
    SymbolIndex,
    _assembly,
    _extent_rows,
    _symbol_uses,
    _visible_sources,
)
from bof3.symbols.context import Context
from bof3.symbols.layers import _layer_manifests, _layer_tree
from bof3.symbols.signatures import (
    _caller_map,
    _file_rows,
    _function_rows,
    _global_rows,
    _layers,
    _table_callees,
)


def extents(ctx: Context, args: argparse.Namespace) -> int:
    """Print each global's extent and the accesses beyond it the bytes prove."""
    assembly = _assembly(ctx)
    index = SymbolIndex(ctx, read_symbols(ctx.root))
    manifests = _layer_manifests(ctx)
    if args.image and args.image not in manifests:
        raise SymbolError(f"extents: no target {args.image}")
    rows = _extent_rows(ctx, assembly, index, manifests)
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


def homes(ctx: Context, args: argparse.Namespace) -> int:
    """Print each function's, global's and file's home from the call and data graph."""
    assembly = _assembly(ctx)
    index = SymbolIndex(ctx, read_symbols(ctx.root))
    manifests = _layer_manifests(ctx)
    tree = _layer_tree(ctx)
    visible = _visible_sources(tree, manifests)
    callers = _caller_map(assembly)
    table_callees = _table_callees(ctx, assembly, manifests, tree)
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
    extent_list = _extent_rows(ctx, assembly, index, manifests)
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
