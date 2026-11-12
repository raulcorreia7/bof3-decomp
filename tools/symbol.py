#!/usr/bin/env python3
"""Add, rename and inspect symbols everywhere they live.

    tools/symbol.py add IMAGE NAME 0xADDR --source TEXT [--type T] [--size N] [--alias]
    tools/symbol.py rename OLD NEW [--image IMAGE...] [--local | --scope PATH...] [--source TEXT]
                           [--type T] [--size N] [--dry-run]
    tools/symbol.py params FUNC OLD=NEW...
    tools/symbol.py refs [DIR...]

`add` writes one row of config/symbols.toml in address order.

`rename` changes a function or global in every tracked file of the scope: the definition, each
prototype and use, `config/` references, and the unit file `OLD.c` (`git mv`). It writes the
row of config/symbols.toml: a new row for an address name (`--source` describes the symbol), or the
renamed key of an existing row. An address name (`func_<ADDR>`, `D_<ADDR>`) stays in a comment
above its definition and declaration. A named symbol is one name in every image: with no
`--image` its row is renamed in every table that has it. An address name is unique only per
image, so give `--image` once per image that holds the twin; `--local` limits the files to those
images' `src/` and `config/` folders (`--scope` to the given paths). The resident images
(`exe/slus_004_22`, `emi/etc/game/00`) are visible everywhere and rename with no scope.

`rename` checks the planned edits and moves before changing sources. A failure restores the
files, paths and index; success also requires no old named reference in src/include/config,
including untracked files. Address-name comments and unrelated images retain their provenance.

`params` renames parameters of one function in its unit file `FUNC.c` and on its prototype
lines in headers.

`refs` ranks the address-named units (`func_<ADDR>.c`) under the folders (default `src`) by how
often their name occurs in `src`, `include` and `asm`: the most used are the best to name first.

Run `meson compile -C build/meson check-<image>` for every touched image afterwards.
"""

from __future__ import annotations

import argparse
import collections
import json
import os
import re
import shutil
import subprocess
import tempfile
from pathlib import Path

from bof3.resolve.ids import source_folder
from bof3.source import symtab

ROOT = Path(__file__).resolve().parent.parent
SYMBOLS = ROOT / "config/symbols.toml"
ADDRESS_NAME = re.compile(r"(func|D|jtbl)_([0-9A-F]{8})$")
RESIDENT = ("exe/slus_004_22", "emi/etc/game/00")
DEFAULT_SCOPE = ("src", "include", "config", "docs", "asm")


def git(*args: str, check: bool = True, env: dict[str, str] | None = None) -> str:
    """Run Git in the repository and return stdout."""
    return subprocess.run(
        ["git", *args], cwd=ROOT, capture_output=True, text=True, check=check, env=env
    ).stdout


def grep_files(word: str, scope: list[str]) -> list[str]:
    """Return the tracked files under ``scope`` that hold ``word`` as a whole word."""
    names = git("grep", "-l", "-z", "-w", "-e", word, "--", *scope, check=False)
    return [name for name in names.split("\0") if name]


def add(args: argparse.Namespace) -> int:
    """Insert one row."""
    addr = int(args.addr, 16)
    row = symtab.format_row(
        args.name, addr, type=args.type, size=int(args.size, 0) if args.size else None,
        source=args.source, alias=args.alias,
    )  # fmt: skip
    text = SYMBOLS.read_text(encoding="utf-8")
    SYMBOLS.write_text(
        symtab.add_row(text, args.image, args.name, row, addr), encoding="utf-8"
    )
    print(f"added {args.name} to [{args.image}]")
    return 0


def tables_with(text: str, name: str) -> list[str]:
    """Return the images whose table has a row ``name``."""
    images, image = [], ""
    for line in text.split("\n"):
        if line.startswith('["'):
            image = line[2:-2]
        elif line.startswith(name + " = "):
            images.append(image)
    return images


def local_scope(images: list[str]) -> list[str]:
    """Return the folders that belong to the images."""
    folders = [
        f
        for image in images
        for f in (f"src/{source_folder(image)}", f"config/{image}")
    ]
    missing = [f for f in folders if not (ROOT / f).is_dir()]
    if missing:
        raise SystemExit(f"symbol: no such folder {', '.join(missing)}")
    return folders


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
    old: str, edits: dict[Path, str], scope: list[str], address: bool
) -> None:
    """Reject old references in the planned or current source tree."""
    pattern = re.compile(rb"\b" + re.escape(old.encode()) + rb"\b")
    names = git("ls-files", "-z", "--cached", "--others", "--", *scope)
    for name in names.rstrip("\0").split("\0"):
        path = ROOT / name
        if not name.startswith(("src/", "include/", "config/")) or not path.is_file():
            continue
        data = edits[path].encode("utf-8") if path in edits else path.read_bytes()
        if address:
            data = re.sub(
                rb"(?m)^\s*/\* " + re.escape(old.encode()) + rb" \*/\s*$", b"", data
            )
        if pattern.search(data):
            raise SystemExit(
                f"symbol: {old} remains in {name}; include every reference in the rename"
            )


def apply_rename(
    edits: dict[Path, str],
    moves: list[tuple[str, str]],
    old: str,
    scope: list[str],
    address: bool,
) -> None:
    """Publish the index only after every file edit, move and reference check succeeds."""
    index = Path(
        git("rev-parse", "--path-format=absolute", "--git-path", "index").strip()
    )
    lock = index.with_name(index.name + ".lock")
    # Hold Git's real index lock while git mv operates on a private copy.
    lock.open("xb").close()
    published = False
    try:
        with tempfile.TemporaryDirectory(prefix=".symbol-rename-", dir=ROOT) as folder:
            scratch = Path(folder)
            private_index = scratch / "index"
            shutil.copy2(index, private_index)
            env = dict(os.environ, GIT_INDEX_FILE=str(private_index))
            backups = {}
            for number, path in enumerate(edits):
                if (
                    path.is_symlink()
                    or not path.is_file()
                    or not os.access(path, os.W_OK)
                    or not os.access(path.parent, os.W_OK)
                ):
                    raise SystemExit(f"symbol: cannot rewrite {path.relative_to(ROOT)}")
                backup = scratch / str(number)
                shutil.copy2(path, backup)
                backups[path] = backup
            for source, target in moves:
                if not os.access((ROOT / source).parent, os.W_OK):
                    raise SystemExit(f"symbol: cannot move {source}")
                if os.path.lexists(ROOT / target):
                    raise SystemExit(f"symbol: destination already exists: {target}")
                git("mv", "-n", "--", source, target, env=env)
            try:
                for path, contents in edits.items():
                    path.write_text(contents, encoding="utf-8")
                for source, target in moves:
                    git("mv", "--", source, target, env=env)
                check_rename(old, {}, scope, address)
                shutil.copyfile(private_index, lock)
                os.chmod(lock, index.stat().st_mode)
                os.replace(lock, index)
                published = True
            except BaseException:
                for _, target in moves:
                    (ROOT / target).unlink(missing_ok=True)
                for path, backup in backups.items():
                    os.replace(backup, path)
                raise
    finally:
        if not published:
            lock.unlink(missing_ok=True)


def rename(args: argparse.Namespace) -> int:
    """Rename one symbol across the scope and in the symbol table."""
    old, new = args.old, args.new
    if not re.fullmatch(r"[A-Za-z_]\w*", new):
        raise SystemExit(f"symbol: {new} is not an identifier")
    address = ADDRESS_NAME.match(old)
    text = SYMBOLS.read_text(encoding="utf-8")
    images = args.image or ([] if address else tables_with(text, old))
    if not images:
        raise SystemExit(
            f"symbol: give --image for {old}; no table has a row of that name"
        )
    if args.local:
        scope = local_scope(images)
    elif args.scope:
        scope = args.scope
    elif address and any(i not in RESIDENT for i in images):
        raise SystemExit(
            f"symbol: {old} is unique only inside its image. Add --local, or --scope PATH..."
        )
    else:
        scope = list(DEFAULT_SCOPE)
    files = grep_files(old, scope)
    if not files:
        raise SystemExit(f"symbol: {old} does not occur under {' '.join(scope)}")
    clash = grep_files(new, scope)
    if clash:
        raise SystemExit(
            f"symbol: {new} already occurs in {clash[0]}; pick another name"
        )
    if args.dry_run:
        print("\n".join(files))
        return 0
    if address:
        if not args.source:
            raise SystemExit(
                f"symbol: naming {old} needs --source, a description of the symbol"
            )
        addr = int(address[2], 16)
        kind = args.type or ("func" if old.startswith("func_") else None)
        row = symtab.format_row(
            new,
            addr,
            type=kind,
            size=int(args.size, 0) if args.size else None,
            source=args.source,
        )
        for image in images:
            text = symtab.add_row(text, image, new, row, addr)
    else:
        for image in images:
            text = symtab.rename_row(text, image, old, new) or text
    pattern = re.compile(r"\b" + re.escape(old) + r"\b")
    edits = {SYMBOLS: text}
    moves = []
    for name in files:
        path = ROOT / name
        contents = edits.get(path)
        if contents is None:
            contents = path.read_text(encoding="utf-8")
        contents = pattern.sub(new, contents)
        if address and name.startswith(("src/", "include/")):
            contents = with_address_comment(path, old, new, contents)
        edits[path] = contents
        if path.name == f"{old}.c":
            moves.append(
                (name, path.with_name(f"{new}.c").relative_to(ROOT).as_posix())
            )
    check_scope = scope if address else ["src", "include", "config"]
    check_rename(old, edits, check_scope, bool(address))
    apply_rename(edits, moves, old, check_scope, bool(address))
    print(f"renamed {old} -> {new} in {len(files)} files")
    return 0


def params(args: argparse.Namespace) -> int:
    """Rename parameters in one function's unit file and its prototypes."""
    pairs = [p.split("=", 1) for p in args.pairs]
    if any(len(p) != 2 or not p[0] or not p[1] for p in pairs):
        raise SystemExit("symbol: write each rename as OLD=NEW")
    prototype = re.compile(r"\S[^=]*\b" + re.escape(args.func) + r"\s*\(.*\)\s*;")
    for name in grep_files(args.func, ["src", "include"]):
        path = ROOT / name
        lines = path.read_text(encoding="utf-8").split("\n")
        own = path.name == f"{args.func}.c"
        for i, line in enumerate(lines):
            if own or (name.endswith(".h") and prototype.match(line)):
                for a, b in pairs:
                    line = re.sub(r"\b" + re.escape(a) + r"\b", b, line)
                lines[i] = line
        path.write_text("\n".join(lines), encoding="utf-8")
    return 0


def ref_rows(dirs: list[str]) -> list[dict]:
    """Return the address-named units with their reference counts, most used first."""
    units = {}
    for folder in dirs:
        for path in sorted((ROOT / folder).rglob("func_????????.c")):
            units[path.stem] = path.relative_to(ROOT).as_posix()
    counts: collections.Counter[str] = collections.Counter()
    word = re.compile(r"func_[0-9A-F]{8}")
    for folder in ("asm", "src", "include"):
        for path in (ROOT / folder).rglob("*"):
            if path.suffix in (".s", ".c", ".h") and path.is_file():
                counts.update(
                    word.findall(path.read_text(encoding="utf-8", errors="replace"))
                )
    return [
        {"count": counts[name], "name": name, "unit": units[name]}
        for name in sorted(units, key=lambda n: (-counts[n], n))
    ]


def refs(args: argparse.Namespace) -> int:
    """Print the address-named units with their reference counts, most used first."""
    for row in ref_rows(args.dirs or ["src"]):
        if args.jsonl:
            print(json.dumps(row, ensure_ascii=False))
        else:
            print(row["count"], row["name"], row["unit"], sep="\t")
    return 0


def main(argv: list[str] | None = None) -> int:
    """Run one verb."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    verbs = parser.add_subparsers(dest="verb", required=True)
    one = verbs.add_parser("add", help="add a symbols.toml row")
    one.add_argument("image")
    one.add_argument("name")
    one.add_argument("addr")
    one.add_argument("--source", help="a description of the symbol")
    one.add_argument("--type")
    one.add_argument("--size")
    one.add_argument("--alias", action="store_true")
    one.set_defaults(run=add)
    two = verbs.add_parser("rename", help="rename a function or global")
    two.add_argument("old")
    two.add_argument("new")
    two.add_argument(
        "--image",
        action="append",
        help="a symbols.toml table, such as emi/battle/battle/03; repeat it per image "
        "(default for a named symbol: every table that has it)",
    )
    two.add_argument(
        "--local",
        action="store_true",
        help="only this image's src/ and config/ folders",
    )
    two.add_argument("--scope", nargs="+", help="only these paths")
    two.add_argument("--source", help="a description (required for an address name)")
    two.add_argument("--type")
    two.add_argument("--size")
    two.add_argument(
        "--dry-run", action="store_true", help="list the files; change nothing"
    )
    two.set_defaults(run=rename)
    three = verbs.add_parser("params", help="rename parameters of one function")
    three.add_argument("func")
    three.add_argument("pairs", nargs="+", metavar="OLD=NEW")
    three.set_defaults(run=params)
    four = verbs.add_parser("refs", help="rank address-named units by references")
    four.add_argument("dirs", nargs="*")
    four.add_argument("--jsonl", action="store_true", help="one JSON object per line")
    four.set_defaults(run=refs)
    args = parser.parse_args(argv)
    if args.verb == "add" and not args.source and not args.alias:
        parser.error("add needs --source (a description) or --alias")
    try:
        return args.run(args)
    except (symtab.SymtabError, OSError) as error:
        raise SystemExit(f"symbol: {error}") from None
    except subprocess.CalledProcessError as error:
        raise SystemExit(
            f"symbol: {error.stderr.strip() if error.stderr else error}"
        ) from None


if __name__ == "__main__":
    raise SystemExit(main())
