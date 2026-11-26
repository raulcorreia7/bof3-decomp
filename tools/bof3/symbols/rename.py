"""Rename a function or global across the tracked tree."""

from __future__ import annotations

import os
import re
import shutil
import tempfile
from dataclasses import dataclass
from pathlib import Path

from bof3.adapters.config import image_layout, symbol_edits, symbols_text
from bof3.errors import RenameError
from bof3.link import symbols
from bof3.resolve.ids import source_folder
from bof3.source import ctext, symtab
from bof3.status import claims
from bof3.symbols import parse
from bof3.symbols.context import (
    DEFAULT_SCOPE,
    HISTORY,
    RESIDENT,
    Context,
    grep_files,
    local_scope,
    tables_with,
)


@dataclass(frozen=True)
class RenameRequest:
    old: str
    new: str
    image: list[str] | None = None
    local: bool = False
    scope: list[str] | None = None
    source: str | None = None
    type: str | None = None
    size: str | None = None
    dry_run: bool = False


@dataclass(frozen=True)
class RenameResult:
    files: list[str]
    applied: bool


UNIT_KINDS = ("c", "asm")


ROW_KINDS = UNIT_KINDS + ("bin", ".data", ".rodata", "data")


LAYOUT_ADDRESS = re.compile(r"(?:func|D|data)_(?P<addr>[0-9A-F]{8})$")


OFFSET_NAME = re.compile(r"[0-9A-F]+")


LIST_ROW = re.compile(
    r"^(?P<before>\s*-\s*\[\s*0x)(?P<start>[0-9A-Fa-f]+)"
    r"(?P<middle>\s*,\s*(?P<kind>[A-Za-z_.]+)\s*,\s*)(?:[./A-Za-z0-9_]*/)?(?P<name>[A-Za-z0-9_]+)"
    r"(?P<after>.*)$"
)


KEYED_ROW = re.compile(
    r"^(?P<before>\s*-\s*\{\s*start:\s*0x)(?P<start>[0-9A-Fa-f]+)"
    r"(?P<middle>.*?\btype:\s*(?P<kind>[A-Za-z_.]+).*?\bname:\s*)"
    r"(?:[./A-Za-z0-9_]*/)?(?P<name>[A-Za-z0-9_]+)(?P<after>.*)$"
)


@dataclass(frozen=True)
class RowRef:
    """One layout row that names a source."""

    image: str
    splat: Path
    start: int
    address: int
    kind: str
    name: str
    source: Path


def layout_rows(ctx: Context, image: str, name: str) -> list[RowRef]:
    """Return the layout rows of one image that name ``name``."""
    layout = image_layout(ctx.root, image)
    if layout is None:
        return []
    splat = ctx.root / "config" / image / "splat.yaml"
    return [
        RowRef(
            image,
            splat,
            boundary.file_start,
            boundary.virtual_start,
            boundary.kind,
            name,
            Path(
                os.path.normpath(
                    ctx.root
                    / "src"
                    / source_folder(image)
                    / f"{boundary.folder}{name}.c"
                )
            ),
        )
        for boundary in layout.boundaries
        if boundary.name == name and boundary.kind in ROW_KINDS
    ]


def unit_definitions(path: Path) -> set[str]:
    return claims.unit_definitions(path) if path.is_file() else set()


def under_scope(ctx: Context, path: Path, scope: list[str]) -> bool:
    return any(
        path == ctx.root / folder or ctx.root / folder in path.parents
        for folder in scope
    )


def link_owners(ctx: Context, image: str) -> list[str]:
    """The images one image's link reads names from: itself, the residents and its owners."""
    try:
        return symbols.link_owners(ctx.root, image)
    except (OSError, KeyError, TypeError, ValueError):
        return [image]


def _file_naming(ctx: Context, name: str, image: str) -> str | None:
    """The first file of the image's folders that uses ``name`` outside comments and strings."""
    pattern = re.compile(r"\b" + re.escape(name) + r"\b")
    own = [f"src/{source_folder(image)}", f"config/{image}"]
    for path in grep_files(ctx, name, [f for f in own if (ctx.root / f).is_dir()]):
        text = (ctx.root / path).read_text(encoding="utf-8", errors="replace")
        if pattern.search(ctext.mask(text)):
            return path
    return None


def address_clash(ctx: Context, name: str, images: list[str]) -> str | None:
    """Why an address name cannot be used again, or None when its address is free."""
    address = symbols.address_of(name)
    for image in images:
        other = (
            f"[{owner}] {name} is 0x{row.addr:08X}"
            for owner in link_owners(ctx, image)
            for row in symbols.target_rows(ctx.root, owner)
            if row.name == name and row.addr != address
        )
        found = _file_naming(ctx, name, image) or next(other, None)
        if found:
            return found
    return None


def rename_layout_row(ctx: Context, text: str, row: RowRef, new: str) -> str:
    """Return ``text`` with one layout row named ``new``; a row already renamed stays."""
    lines = text.split("\n")
    found = 0
    for index, line in enumerate(lines):
        for pattern in (LIST_ROW, KEYED_ROW):
            match = pattern.match(line)
            if (
                match
                and int(match["start"], 16) == row.start
                and match["kind"] == row.kind
                and match["name"] in (row.name, new)
            ):
                if match["name"] == row.name:
                    lines[index] = (
                        line[: match.start("name")] + new + line[match.end("name") :]
                    )
                found += 1
                break
    if found != 1:
        raise RenameError(
            f"symbol: {row.splat.relative_to(ctx.root)}: no one {row.kind} row at "
            f"0x{row.start:X} named {row.name}"
        )
    return "\n".join(lines)


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
    ctx: Context, old: str, edits: dict[Path, str], scope: list[str], address: bool
) -> None:
    """Reject old references in the planned or current source tree."""
    pattern = re.compile(rb"\b" + re.escape(old.encode()) + rb"\b")
    names = ctx.git("ls-files", "-z", "--cached", "--others", "--", *scope)
    for name in names.rstrip("\0").split("\0"):
        path = ctx.root / name
        if not name.startswith(("src/", "include/", "config/")) or not path.is_file():
            continue
        if name.startswith(HISTORY):
            continue
        data = edits[path].encode("utf-8") if path in edits else path.read_bytes()
        if address:
            data = re.sub(
                rb"(?m)^\s*/\* " + re.escape(old.encode()) + rb" \*/\s*$", b"", data
            )
        if pattern.search(data):
            raise RenameError(
                f"symbol: {old} remains in {name}; include every reference in the rename"
            )


def _stage(
    ctx: Context,
    edits: dict[Path, str],
    moves: list[tuple[str, str]],
    scratch: Path,
    env: dict,
) -> dict[Path, Path]:
    """Back up each edited file and dry-run each move; return the backups."""
    backups = {}
    for number, path in enumerate(edits):
        writable = os.access(path, os.W_OK) and os.access(path.parent, os.W_OK)
        if path.is_symlink() or not path.is_file() or not writable:
            raise RenameError(f"symbol: cannot rewrite {path.relative_to(ctx.root)}")
        backups[path] = Path(shutil.copy2(path, scratch / str(number)))
    for source, target in moves:
        if not os.access((ctx.root / source).parent, os.W_OK):
            raise RenameError(f"symbol: cannot move {source}")
        if os.path.lexists(ctx.root / target):
            raise RenameError(f"symbol: destination already exists: {target}")
        ctx.git("mv", "-n", "--", source, target, env=env)
    return backups


def apply_rename(
    ctx: Context,
    edits: dict[Path, str],
    moves: list[tuple[str, str]],
    old: str,
    scope: list[str],
    address: bool,
    verify: bool = True,
) -> None:
    """Publish the index only after every file edit, move and reference check succeeds."""
    index = Path(
        ctx.git("rev-parse", "--path-format=absolute", "--git-path", "index").strip()
    )
    lock = index.with_name(index.name + ".lock")
    # Hold Git's real index lock while git mv operates on a private copy.
    lock.open("xb").close()
    published = False
    try:
        with tempfile.TemporaryDirectory(
            prefix=".symbol-rename-", dir=ctx.root
        ) as folder:
            private_index = Path(folder) / "index"
            shutil.copy2(index, private_index)
            env = dict(os.environ, GIT_INDEX_FILE=str(private_index))
            backups = _stage(ctx, edits, moves, Path(folder), env)
            try:
                for path, contents in edits.items():
                    path.write_text(contents, encoding="utf-8")
                for source, target in moves:
                    ctx.git("mv", "--", source, target, env=env)
                if verify:
                    check_rename(ctx, old, {}, scope, address)
                shutil.copyfile(private_index, lock)
                os.chmod(lock, index.stat().st_mode)
                os.replace(lock, index)
                published = True
            except BaseException:
                for _, target in moves:
                    (ctx.root / target).unlink(missing_ok=True)
                for path, backup in backups.items():
                    os.replace(backup, path)
                raise
    finally:
        if not published:
            lock.unlink(missing_ok=True)


def _rename_scope(
    ctx: Context,
    req: RenameRequest,
    address: re.Match | None,
    images: list[str],
) -> list[str]:
    """The paths a rename may touch."""
    if req.local:
        return local_scope(ctx, images)
    if req.scope:
        return req.scope
    if address and any(i not in RESIDENT for i in images):
        raise RenameError(
            f"symbol: {req.old} is unique only inside its image. Add --local, or --scope PATH..."
        )
    return list(DEFAULT_SCOPE)


def _require_rows_in_scope(
    ctx: Context, rows: list[RowRef], scope: list[str], old: str
) -> None:
    """Reject a layout row or its source file that lies outside the scope."""
    outside = [row for row in rows if not under_scope(ctx, row.splat, scope)]
    if outside:
        raise RenameError(
            f"symbol: {outside[0].splat.relative_to(ctx.root)} names {old}; "
            "add its folder to --scope"
        )
    outside = [
        row
        for row in rows
        if row.source.is_file() and not under_scope(ctx, row.source, scope)
    ]
    if outside:
        raise RenameError(
            f"symbol: {outside[0].source.relative_to(ctx.root)} is named {old}; "
            "add its folder to --scope"
        )


def _old_name_is_live(old: str, rows: list[RowRef], units: list[RowRef]) -> bool:
    """Whether the code still holds the old name, as a unit definition or in a source file."""
    if any(old in unit_definitions(row.source) for row in units):
        return True
    if units:
        return False
    pattern = re.compile(r"\b" + re.escape(old) + r"\b")
    return any(
        pattern.search(row.source.read_text(encoding="utf-8", errors="replace"))
        for row in rows
        if row.source.is_file()
    )


def _reject_clash(
    ctx: Context,
    text: str,
    old: str,
    new: str,
    images: list[str],
    scope: list[str],
    address: re.Match | None,
) -> None:
    """Stop when the new name is already in use, unless it is the same address's own row."""
    if symbols.ADDRESS_NAME.fullmatch(new):
        use = address_clash(ctx, new, images)
        clash = [use] if use else []
    else:
        clash = grep_files(ctx, new, scope)
    if not clash:
        return
    document = parse(text)
    allowed = bool(address) and any(
        isinstance(document.get(image, {}).get(new), dict)
        and int(document[image][new].get("addr", -1)) == int(address["addr"], 16)
        for image in images
    )
    if not allowed:
        raise RenameError(
            f"symbol: {new} already occurs in {clash[0]}; pick another name"
        )


def _name_address(
    text: str,
    old: str,
    new: str,
    images: list[str],
    address: re.Match,
    req: RenameRequest,
) -> str:
    """The symbol table with the address name replaced by ``new`` in every image."""
    addr = int(address["addr"], 16)
    kind = req.type or ("func" if old.startswith("func_") else None)
    document = parse(text)
    for image in images:
        named = document.get(image, {}).get(new)
        if isinstance(named, dict):
            found = int(named.get("addr", -1))
            if found != addr:
                raise RenameError(
                    f"symbol: [{image}] {new} is 0x{found:08X}, not 0x{addr:08X}"
                )
            text = symtab.remove_row(text, image, old) or text
            continue
        if not req.source:
            raise RenameError(
                f"symbol: naming {old} needs --source, a description of the symbol"
            )
        # The row keeps the type, size and alias it had under the address name unless the request sets them.
        was = document.get(image, {}).get(old)
        was = was if isinstance(was, dict) else {}
        row = symtab.format_row(
            new,
            addr,
            type=kind or was.get("type"),
            size=int(req.size, 0) if req.size else was.get("size"),
            source=req.source,
            alias=bool(was.get("alias")),
        )
        # A row already keyed with the address name would be rewritten by the source
        # substitution below and repeat the new key.
        text = symtab.remove_row(text, image, old) or text
        text = symtab.add_row(text, image, new, row, addr)
    return text


def _verify_repair(
    ctx: Context,
    text: str,
    rows: list[RowRef],
    units: list[RowRef],
    new: str,
    offset_rename: bool,
) -> None:
    """Check that a repair finds the new name already defined in the code or table."""
    if units:
        for row in units:
            if new in unit_definitions(row.source):
                continue
            if offset_rename and new == f"{row.start:X}":
                continue
            raise RenameError(
                f"symbol: {row.source.relative_to(ctx.root)} does not define {new}; "
                "rename the function first"
            )
        return
    table = parse(text)
    for row in rows:
        named = table.get(row.image, {}).get(new)
        if not (isinstance(named, dict) and int(named.get("addr", -1)) == row.address):
            raise RenameError(
                f"symbol: [{row.image}] has no {new} at 0x{row.address:08X}; "
                "add the row first"
            )


def _rename_edits(
    ctx: Context,
    text: str,
    files: list[str],
    rows: list[RowRef],
    old: str,
    new: str,
    address: re.Match | None,
    repair: bool,
) -> dict[Path, str]:
    """The new contents of every file the rename rewrites."""
    edits = symbol_edits(ctx.root, text)
    if not repair:
        pattern = re.compile(r"\b" + re.escape(old) + r"\b")
        for name in files:
            path = ctx.root / name
            contents = edits.get(path)
            if contents is None:
                contents = path.read_text(encoding="utf-8")
            contents = pattern.sub(new, contents)
            if address and name.startswith(("src/", "include/")):
                contents = with_address_comment(path, old, new, contents)
            edits[path] = contents
    for row in rows:
        contents = edits.get(row.splat)
        if contents is None:
            contents = row.splat.read_text(encoding="utf-8")
        edits[row.splat] = rename_layout_row(ctx, contents, row, new)
    return edits


def _rename_moves(
    ctx: Context,
    rows: list[RowRef],
    files: list[str],
    old: str,
    new: str,
    scope: list[str],
) -> list[tuple[str, str]]:
    """The ``old.c`` to ``new.c`` file moves the rename needs."""
    moves: list[tuple[str, str]] = []

    def add_move(path: Path) -> None:
        if not path.is_file() or not under_scope(ctx, path, scope):
            return
        pair = (
            path.relative_to(ctx.root).as_posix(),
            path.with_name(f"{new}.c").relative_to(ctx.root).as_posix(),
        )
        if pair not in moves:
            moves.append(pair)

    for row in rows:
        add_move(row.source)
    for name in files:
        path = ctx.root / name
        if path.name == f"{old}.c":
            add_move(path)
    return moves


def rename(ctx: Context, req: RenameRequest) -> RenameResult:
    """Rename one symbol across the scope, its layout rows and the symbol table."""
    old, new = req.old, req.new
    offset_rename = bool(OFFSET_NAME.fullmatch(old))
    if not re.fullmatch(r"[A-Za-z_]\w*", new) and not (
        offset_rename and OFFSET_NAME.fullmatch(new)
    ):
        raise RenameError(f"symbol: {new} is not an identifier")
    address = LAYOUT_ADDRESS.match(old)
    text = symbols_text(ctx.root)
    images = req.image or ([] if address else tables_with(text, old))
    if not images:
        raise RenameError(
            f"symbol: give --image for {old}; no table has a row of that name"
        )
    scope = _rename_scope(ctx, req, address, images)
    rows = [row for image in images for row in layout_rows(ctx, image, old)]
    files = grep_files(ctx, old, scope)
    if not files and not rows:
        raise RenameError(f"symbol: {old} does not occur under {' '.join(scope)}")
    _require_rows_in_scope(ctx, rows, scope, old)
    # A unit that still holds the old name renames the code itself; one that does not is a
    # repair of the row and file left behind when the symbol was named elsewhere.
    units = [row for row in rows if row.kind in UNIT_KINDS]
    repair = bool(rows) and not _old_name_is_live(old, rows, units)
    if not repair:
        _reject_clash(ctx, text, old, new, images, scope, address)
    if req.dry_run:
        planned = set(files)
        planned.update(row.splat.relative_to(ctx.root).as_posix() for row in rows)
        return RenameResult(sorted(planned), applied=False)
    if address:
        text = _name_address(text, old, new, images, address, req)
    elif not repair:
        for image in images:
            text = symtab.rename_row(text, image, old, new) or text
    if repair:
        _verify_repair(ctx, text, rows, units, new, offset_rename)
    edits = _rename_edits(ctx, text, files, rows, old, new, address, repair)
    moves = _rename_moves(ctx, rows, files, old, new, scope)
    # The edits are the files the scope allows; --local and --scope limit the check with them.
    if not repair:
        check_rename(ctx, old, edits, scope, bool(address))
    apply_rename(ctx, edits, moves, old, scope, bool(address), verify=not repair)
    return RenameResult([str(path) for path in edits], applied=True)
