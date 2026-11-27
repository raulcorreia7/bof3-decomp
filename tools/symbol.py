#!/usr/bin/env python3
"""Add, rename and inspect symbols everywhere they live.

    tools/symbol.py add IMAGE NAME 0xADDR --source TEXT [--type T] [--size N]
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

`add` writes one row of config/symbols/<image>.toml in address order. The image is a folder under
`config/` that holds a `splat.yaml`; any other id is refused.

`rename` changes a function or global in every tracked file of the scope: the definition, each
prototype and use, `config/` references, and the unit file `OLD.c` (`git mv`). It never edits
`config/attempts.jsonl`: the history keeps the names it was written with. It writes the
row of config/symbols/<image>.toml: a new row for an address name (`--source` describes the symbol), or the
renamed key of an existing row. Naming an address replaces the row already keyed with its address
name and keeps its `type`, `size` and `alias` unless `--type` or `--size` set them. An address name (`func_<ADDR>`, `D_<ADDR>`) stays in a comment
above its definition and declaration. A named symbol is one name in every image: with no
`--image` its row is renamed in every table that has it. An address name is unique only per
image, so give `--image` once per image that holds the twin; `--local` limits the files to those
images' `src/` and `config/` folders (`--scope` to the given paths). The resident images
(`exe/slus_004_22`, `emi/etc/game/00`) are visible everywhere and rename with no scope. The new
name follows the same scope: a readable name must occur nowhere in the tree, an address-form name
only in the image and the images its link sees.

Every layout row that names `OLD` follows the rename, the unit file is moved with it, and a
`--scope` that leaves the layout or the unit outside is refused rather than leaving a stale name.
A row whose unit no longer holds `OLD`, because the symbol is already named elsewhere, is repaired:
the row and unit file take `NEW` and the code stays as it is. An offset name (`1EFC`) repairs the
same way, to the row's own offset (`1EDC`).

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
built function index: direct globals, globals that point at the type, and the image's `g_Self` view
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
import dataclasses
import json
import subprocess
import sys

from bof3.adapters.cli import run_main
from bof3.errors import SymbolError
from bof3.source import symtab
from bof3.symbols.accesses import accesses, records
from bof3.symbols.check import AddRequest, UnknownImageError, add, check, params, refs
from bof3.symbols.context import Context, Table
from bof3.symbols.headers import value
from bof3.symbols.layers import layers
from bof3.symbols.lookup import AtRow, at, member, uses
from bof3.symbols.rename import RenameRequest, rename
from bof3.symbols.signatures import extents, homes, signatures
from bof3.symbols.values import values


def _show(table: Table, jsonl: bool) -> int:
    for note in table.notes:
        print(note, file=sys.stderr)
    keys = table.keys.split()
    if jsonl:
        for row in table.rows:
            print(json.dumps({key: row[key] for key in keys}, ensure_ascii=False))
        return 0
    heads = keys if table.heads is None else table.heads.split()
    if heads:
        print("\t".join(heads))
    for row in table.rows:
        cells = table.cells(row) if table.cells else [str(row[k]) for k in keys]
        print("\t".join(cells))
    return 0


def _owner_lines(prefix: str, row: AtRow) -> None:
    if not row.owners:
        print(f"{prefix}  no named owner")
    for found in row.owners:
        print(f"{prefix}  {found.path}+{found.delta:#x}  {found.size}  [{found.table}]")


def _add(ctx: Context, args: argparse.Namespace) -> int:
    try:
        add(
            ctx,
            AddRequest(
                args.image,
                args.name,
                args.addr,
                args.source,
                args.type,
                args.size,
            ),
        )
    except UnknownImageError as error:
        print(error, file=sys.stderr)
        return 2
    print(f"added {args.name} to [{args.image}]")
    return 0


def _rename(ctx: Context, args: argparse.Namespace) -> int:
    done = rename(ctx, RenameRequest(
        args.old, args.new, args.image, args.local, args.scope, args.source, args.type, args.size, args.dry_run,
    ))  # fmt: skip
    if done.applied:
        print(f"renamed {args.old} -> {args.new} in {len(done.files)} files")
    else:
        print("\n".join(done.files))
    return 0


def _params(ctx: Context, args: argparse.Namespace) -> int:
    params(ctx, args.func, args.pairs)
    return 0


def _check(ctx: Context, args: argparse.Namespace) -> int:
    report = check(ctx)
    if report.error:
        print(f"symbols: {report.error}")
        return 1
    print("\n".join(report.findings))
    sys.stderr.write(
        f"symbols: {report.tables} tables, {report.rows} rows, {len(report.findings)} findings; "
        f"{'FAIL' if report.failed else 'ok'}\n"
    )
    return int(report.failed)


def _at(ctx: Context, args: argparse.Namespace) -> int:
    found = at(ctx, args.image, args.addresses, args.diff)
    if found.base is not None:
        print(f"no added D_ address in {found.base}...HEAD")
    for row in found.rows:
        _owner_lines(f"{row.addr:#010x}", row)
    return 0


def _member(ctx: Context, args: argparse.Namespace) -> int:
    for path, ctype in member(ctx, args.type, args.offset):
        print(f"{path}\t{ctype}")
    return 0


def _uses(ctx: Context, args: argparse.Namespace) -> int:
    found = uses(ctx, args.symbol)
    if found.at is not None:
        _owner_lines(f"{found.image}@0x{found.at.addr:08X}", found.at)
    for path, number in found.c:
        print(f"c\t{path}:{number}")
    for path, number, function, instruction in found.asm:
        print(f"asm\t{path}:{number}\t{function}\t{instruction}")
    for image, source, kind in found.rizin:
        print(f"rizin\t{image}\t0x{source:08X}\t{kind}")
    return 0


def _value(ctx: Context, args: argparse.Namespace) -> int:
    for item in value(ctx, args.number, args.image, args.type):
        print(f"{item.name}\t{item.header}:{item.line}\t{item.family}")
    return 0


def _values(ctx: Context, args: argparse.Namespace) -> int:
    found = values(ctx)
    if args.jsonl:
        for site in found.sites:
            print(json.dumps(dataclasses.asdict(site), ensure_ascii=False))
        return 0
    print(f"{len(found.sites)} sites")
    for title, counter in found.counts.items():
        print(f"\n{title}")
        for key, count in counter.most_common():
            print(f"{count}\t{key}")
    return 0


def _table_verb(run):
    def handle(ctx: Context, args: argparse.Namespace) -> int:
        return _show(run(ctx, args), args.jsonl)

    return handle


def main(argv: list[str] | None = None, ctx: Context | None = None) -> int:
    """Run one verb."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    verbs = parser.add_subparsers(dest="verb", required=True)

    def verb(name: str, help: str, epilog: str | None = None):
        extra = (
            {"epilog": epilog, "formatter_class": argparse.RawDescriptionHelpFormatter}
            if epilog
            else {}
        )
        return verbs.add_parser(name, help=help, **extra)

    def jsonl(sub: argparse.ArgumentParser) -> None:
        sub.add_argument(
            "--jsonl", action="store_true", help="one JSON object per line"
        )

    sub = verb("add", "add a symbols.toml row")
    sub.add_argument("image")
    sub.add_argument("name")
    sub.add_argument("addr")
    sub.add_argument("--source", help="a description of the symbol")
    sub.add_argument("--type")
    sub.add_argument("--size")
    sub.set_defaults(run=_add)
    sub = verb("rename", "rename a function or global")
    sub.add_argument("old")
    sub.add_argument("new")
    sub.add_argument(
        "--image",
        action="append",
        help="a symbols.toml table, such as emi/battle/battle/03; repeat it per image "
        "(default for a named symbol: every table that has it)",
    )
    sub.add_argument(
        "--local",
        action="store_true",
        help="only this image's src/ and config/ folders",
    )
    sub.add_argument("--scope", nargs="+", help="only these paths")
    sub.add_argument("--source", help="a description (required for an address name)")
    sub.add_argument("--type")
    sub.add_argument("--size")
    sub.add_argument(
        "--dry-run", action="store_true", help="list the files; change nothing"
    )
    sub.set_defaults(run=_rename)
    sub = verb("params", "rename parameters of one function")
    sub.add_argument("func")
    sub.add_argument("pairs", nargs="+", metavar="OLD=NEW")
    sub.set_defaults(run=_params)
    sub = verb("refs", "rank address-named units by references")
    sub.add_argument("dirs", nargs="*")
    jsonl(sub)
    sub.set_defaults(run=_table_verb(lambda ctx, a: refs(ctx, a.dirs or ["src"])))
    verb("check", "report symbol-table problems").set_defaults(run=_check)
    sub = verb(
        "at",
        "show the symbol and member at an address",
        "Example: tools/symbol.py at exe/slus_004_22 0x8014630C",
    )
    sub.add_argument("image", nargs="?", help="a symbols.toml table")
    sub.add_argument("addresses", nargs="*", metavar="0xADDR")
    sub.add_argument(
        "--diff",
        nargs="?",
        const="public/main",
        metavar="BASE",
        help="read the D_ addresses the branch adds (default base: public/main)",
    )
    sub.set_defaults(run=_at)
    sub = verb(
        "member",
        "show the member at a byte offset of a record",
        "Example: tools/symbol.py member Actor 0xB",
    )
    sub.add_argument("type", help="a C record type")
    sub.add_argument("offset", help="a byte offset, such as 0x44")
    sub.set_defaults(run=_member)
    sub = verb(
        "uses",
        "list every reference to a symbol",
        "Examples: tools/symbol.py uses g_Battle\n"
        "          tools/symbol.py uses exe/slus_004_22@0x8014630C",
    )
    sub.add_argument("symbol", help="a name, or IMAGE@0xADDR")
    sub.set_defaults(run=_uses)
    sub = verb(
        "value",
        "find enum members and macros with one value",
        "Example: tools/symbol.py value 0x3A --image emi/battle/battle/03 --type ENEMY_ID",
    )
    sub.add_argument("number", help="a hexadecimal value, such as 0x3A")
    sub.add_argument(
        "--image", help="a symbols.toml table; scan the headers its sources include"
    )
    sub.add_argument("--type", help="an enum name or a name prefix")
    sub.set_defaults(run=_value)
    sub = verb(
        "layers",
        "print the call-graph layer of every function",
        "Example: tools/symbol.py layers --jsonl",
    )
    jsonl(sub)
    sub.set_defaults(run=_table_verb(lambda ctx, a: layers(ctx)))
    sub = verb(
        "accesses",
        "list the reads and writes of a record or global",
        "Example: tools/symbol.py accesses PartyMember --jsonl",
    )
    sub.add_argument(
        "name", help="a record type or a config/symbols/<image>.toml global"
    )
    jsonl(sub)
    sub.set_defaults(run=_table_verb(lambda ctx, a: accesses(ctx, a.name)))
    sub = verb(
        "records",
        "summarise every record and its accesses",
        "Example: tools/symbol.py records --jsonl",
    )
    jsonl(sub)
    sub.set_defaults(run=_table_verb(lambda ctx, a: records(ctx)))
    sub = verb(
        "values",
        "scan matched bodies for literals whose role is declared",
        "Example: tools/symbol.py values --scan --jsonl > values.jsonl\n"
        "         tools/symbol.py values --scan",
    )
    sub.add_argument(
        "--scan", action="store_true", help="scan the matched bodies (the only mode)"
    )
    jsonl(sub)
    sub.set_defaults(run=_values)
    sub = verb(
        "signatures",
        "print the signature the bytes prove for each function",
        "Example: tools/symbol.py signatures Battle_Update\n"
        "         tools/symbol.py signatures --all --jsonl > signatures.jsonl",
    )
    sub.add_argument("function", nargs="?", help="one function name")
    sub.add_argument("--all", action="store_true", help="every function of every image")
    jsonl(sub)
    sub.set_defaults(run=_table_verb(lambda ctx, a: signatures(ctx, a.function)))
    sub = verb(
        "extents",
        "print each global's extent and the accesses beyond it",
        "Example: tools/symbol.py extents emi/battle/battle/03 --jsonl",
    )
    sub.add_argument("image", nargs="?", help="a symbols.toml table")
    jsonl(sub)
    sub.set_defaults(run=_table_verb(lambda ctx, a: extents(ctx, a.image)))
    sub = verb(
        "homes",
        "print each function's, global's and file's home from the graph",
        "Example: tools/symbol.py homes --jsonl > homes.jsonl",
    )
    jsonl(sub)
    sub.set_defaults(run=_table_verb(lambda ctx, a: homes(ctx)))
    args = parser.parse_args(argv)
    if args.verb == "add" and not args.source:
        parser.error("add needs --source (a description)")
    try:
        return args.run(ctx or Context(), args)
    except (symtab.SymtabError, OSError) as error:
        raise SymbolError(f"symbol: {error}") from None
    except subprocess.CalledProcessError as error:
        raise SymbolError(
            f"symbol: {error.stderr.strip() if error.stderr else error}"
        ) from None


if __name__ == "__main__":
    raise SystemExit(run_main(main))
