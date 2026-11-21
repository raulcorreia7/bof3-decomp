#!/usr/bin/env python3
"""Fail when an invented identifier in include/ or src/ carries an 8-digit hex address.

A name says what a thing is for the game, never where it lives. The default tool names are the
only identifiers allowed to hold an address: ``func_<ADDR>``, ``D_<ADDR>``, ``L<ADDR>``,
``jtbl_*``, ``jpt_*`` and ``s_gap_*``. Comments, strings and config/symbols.toml text are not
checked.

The check is a ratchet. ``config/address_names.txt`` lists the offenders that exist today as
``<file><TAB><identifier>``. A name that is not on the list fails, and so does a listed entry
that no longer occurs, so the list only shrinks. Rename the identifier, then delete its line.

``--diff REF`` checks the lines a change adds. A new identifier must not use a word the
vocabulary rejects where another word is decided ([vocabulary](../docs/naming.md#vocabulary)),
and a parameter must be named. An identifier that already exists at ``REF`` is not a new name:
this check only stops new debt, the rename map clears the old. A file that changes must not gain a
``FIELD``/``SP_REF``/``SP`` use either, outside a draft body (a draft keeps the best form reached): the member of the record or of the scratchpad view is the
form to write, so those uses can only shrink (plan section AY). A rebuild that moves an existing
use changes no count, so it passes.

A layout row must not keep an address name its symbol has left. A ``c`` row fails when its unit
defines no C body under the row name and ``config/symbols.toml`` names its address; a ``bin``,
``.data`` or ``data`` row fails when its address has a named non-alias data symbol. ``--diff``
checks the images whose layout or symbol table the change touches; without it, every image.
``tools/symbol.py rename`` moves the row and the unit file.

Usage: python3 tools/check_names.py [--write]    (--write rewrites the baseline from the tree)
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

from bof3.adapters.config import read_symbols
from bof3.adapters.git import changed_files, git, ls_files, ok
from bof3.diff import added_lines as added_diff_lines
from bof3.diff import renames
from bof3.resolve.layout import target_of
from bof3.symbols import TABLE

BASELINE = Path("config/address_names.txt")
ROOTS = ("include", "src")
SUFFIXES = (".c", ".h", ".inc")

TOKEN = re.compile(
    r"""
      (?P<skip>/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*'|^[ \t]*\#\s*include[^\n]*)
    | (?P<number>\b\d[\w.]*)
    | (?P<ident>[A-Za-z_]\w*)
    """,
    re.DOTALL | re.MULTILINE | re.VERBOSE,
)
ADDRESS = re.compile(r"[0-9A-Fa-f]{8}")
DEFAULT = re.compile(r"(?:func|D)_[0-9A-F]{8}|L[0-9A-F]{8}|jtbl_\w*|jpt_\w*|s_gap_\w*")
UNNAMED = re.compile(r"arg[0-9]+")
OFFSET_MACRO = re.compile(r"\b(FIELD|SP_REF|SP)\s*\(")
OFFSET_DEFINITION = re.compile(r"^[ \t]*\#[ \t]*define[ \t]+(?:FIELD|SP_REF|SP)\b")
SKIP = re.compile(
    r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.DOTALL
)
WORD = re.compile(r"[A-Z]+(?=[A-Z][a-z])|[A-Z]?[a-z]+|[A-Z]+|[0-9]+")

# One word per concept: a new name that uses a rejected word takes the decided word instead.
# See docs/naming.md#vocabulary. Only words with no second sense are here; data/work/record and
# the other nouns with a game sense are reviewed through the rename map.
REJECTED = {
    "array": "name a table for the plural of what its index selects",
    "table": "name a table for the plural of what its index selects",
    "handler": "name the action; Callback is the void (*)(void) type, Func a table element",
    "proc": "name the action",
    "routine": "name the action",
    "fn": "name the action",
    "cb": "name the action",
    "data": "the game noun",
    "info": "the game noun",
    "work": "the game noun",
    "misc": "the game noun",
    "rec": "the game noun",
    "buf": "buffer",
    "idx": "index",
    "cnt": "count",
    "num": "count or id",
    "tmp": "the value it holds",
    "temp": "the value it holds",
    "cur": "current",
    "ptr": "the pointee's game noun",
    "obj": "the object's game noun",
    "object": "the object's game noun",
    "ctrl": "the role it controls",
    "mgr": "the role it manages",
    "spr": "sprite",
    "chara": "character",
    "monster": "enemy",
    "goods": "item",
    "spell": "magic or ability",
    "fx": "effect",
    "render": "draw",
    "lookup": "find or get",
    "fetch": "load or get",
    "put": "set or write",
    "make": "create or alloc",
    "kill": "free",
    "delete": "remove",
    "destroy": "free or remove",
    "check": "is, has, can, test or find",
    "handle": "dispatch, run or update",
    "finish": "end",
    "store": "set or write",
    "kind": "type",
    "class": "type",
    "bits": "flags",
    "len": "length",
    "colour": "color",
    "amount": "count or value",
    "quantity": "count or value",
}

# A tag with one spelling per system; a new name with the left side takes the right side.
PREFIXES = (
    (re.compile(r"^World_"), "WorldMap_"),
    (re.compile(r"^Plchar"), "PlChar"),
    (re.compile(r"^PAD_"), "INPUT_"),
    (re.compile(r"^Mem_"), "SYS_"),
    (re.compile(r"^Matrix_"), "MATH_"),
    (re.compile(r"^Fish_"), "Fishing_"),
    (re.compile(r"^CD_"), "EMI_ or DISC_"),
)


LAYOUT_ROW = re.compile(r"(?:func|D|data)_([0-9A-F]{8})$")
SYMBOL_ROW = re.compile(r"\s*([A-Za-z_]\w*)\s*=\s*\{")
UNIT_KINDS = ("c", "asm")
DATA_KINDS = ("bin", ".data", "data")


def layout_images(ref: str | None) -> list[str]:
    """The images whose layout or symbol table a change touches; every image without a ref."""
    if ref is None:
        return sorted(
            target_of(path)
            for path in Path("config").rglob("splat.yaml")
            if target_of(path)
        )
    changed = changed_files(f"{ref}...HEAD", "--", "config")
    images = {
        name[len("config/") : -len("/splat.yaml")]
        for name in changed
        if name.endswith("/splat.yaml")
    }
    images.update(added_symbol_images(ref))
    return sorted(images)


def added_symbol_images(ref: str) -> set[str]:
    """The images whose table a change gives a new row."""
    diff = git("diff", "-U0", f"{ref}...HEAD", "--", TABLE, check=False)
    added = {
        match.group(1)
        for row in diff.splitlines()
        if row.startswith("+") and not row.startswith("+++")
        for match in [SYMBOL_ROW.match(row[1:])]
        if match
    }
    if not added or not Path("config/symbols.toml").is_file():
        return set()
    tables = read_symbols(Path())
    return {
        image
        for image, rows in tables.items()
        if isinstance(rows, dict) and added & rows.keys()
    }


def _stale_message(
    splat: Path, boundary, image: str, named: dict, claims, source_folder
) -> str | None:
    """The message for one layout row that keeps a stale address name, or None."""
    match = LAYOUT_ROW.fullmatch(boundary.name or "")
    if not match or boundary.kind not in UNIT_KINDS + DATA_KINDS:
        return None
    address = int(match.group(1), 16)
    entry = named.get(address)
    if entry is None:
        return None
    if boundary.kind in UNIT_KINDS:
        unit = Path("src") / source_folder(image) / f"{boundary.name}.c"
        if not unit.is_file() or boundary.name in claims.c_definitions(unit):
            return None
    elif entry.type in ("func", "Callback"):
        return None
    return (
        f"{splat}: [{boundary.file_start:#x}, {boundary.kind}, {boundary.name}]: "
        f"the row keeps the address name of 0x{address:08X}, "
        f"which {entry.name} names"
    )


def stale_rows(images: list[str]) -> list[str]:
    """One message per layout row that keeps an address name its symbol no longer uses."""
    from bof3.link import symbols
    from bof3.resolve.ids import source_folder
    from bof3.resolve.layout import parse_splat_layout, splat_facts
    from bof3.status import claims

    if not images:
        return []
    tables = symbols.load(Path("."))
    messages = []
    for image in images:
        splat = Path("config") / image / "splat.yaml"
        if not splat.is_file():
            continue
        try:
            layout = parse_splat_layout(splat, splat_facts(splat).load_address)
        except (OSError, ValueError, ImportError):
            continue
        named = {
            entry.addr: entry
            for entry in tables.get(image, ())
            if not entry.alias and not symbols.ADDRESS_NAME.match(entry.name)
        }
        for boundary in layout.boundaries:
            message = _stale_message(
                splat, boundary, image, named, claims, source_folder
            )
            if message:
                messages.append(message)
    return messages


def split_words(name: str) -> list[str]:
    """Split an identifier at underscores and camel humps, lower case."""
    return [token.lower() for chunk in name.split("_") for token in WORD.findall(chunk)]


def rejected_reason(name: str) -> str | None:
    """Why a new identifier breaks the vocabulary, or ``None`` when it follows it."""
    for pattern, replacement in PREFIXES:
        if pattern.search(name):
            return f"the system tag is {replacement}"
    for word in split_words(name):
        if word in REJECTED:
            return REJECTED[word]
    return None


def rejected_names(text: str) -> set[str]:
    """Identifiers in ``text`` that use a rejected word or an old tag."""
    return {
        m.group()
        for m in TOKEN.finditer(text)
        if m.lastgroup == "ident"
        and not ADDRESS.fullmatch(m.group())
        and rejected_reason(m.group()) is not None
    }


def in_ref(ref: str, name: str) -> bool:
    """Whether ``name`` occurs as a word in the tracked tree at ``ref``."""
    return ok("grep", "-q", "-w", "-F", "-e", name, ref, "--", ".")


def unnamed_parameters(text: str) -> set[str]:
    """``argN`` identifiers in code; comments, strings and hex literals are skipped."""
    return {
        m.group()
        for m in TOKEN.finditer(text)
        if m.lastgroup == "ident" and UNNAMED.fullmatch(m.group())
    }


def offset_macros(text: str) -> set[str]:
    """``FIELD``, ``SP_REF`` and ``SP`` uses in code; comments and strings are skipped."""
    if OFFSET_DEFINITION.match(text):
        return set()
    return {m.group(1) for m in OFFSET_MACRO.finditer(SKIP.sub(" ", text))}


DRAFT_BRANCH = re.compile(
    r"^[ \t]*#[ \t]*ifdef[ \t]+NON_MATCHING\b.*?(?=^[ \t]*#[ \t]*(?:else|endif))",
    re.S | re.M,
)


def without_drafts(text: str) -> str:
    """``text`` with each draft body (the first branch of ``#ifdef NON_MATCHING``) blank."""
    return DRAFT_BRANCH.sub(lambda m: "\n" * m.group().count("\n"), text)


def macro_counts(text: str) -> dict[str, int]:
    """``FIELD``/``SP_REF``/``SP`` uses in code, per macro name."""
    counts: dict[str, int] = {}
    for match in OFFSET_MACRO.finditer(SKIP.sub(" ", without_drafts(text))):
        counts[match.group(1)] = counts.get(match.group(1), 0) + 1
    return counts


def changed_paths(ref: str) -> list[str]:
    """The paths under include/ or src/ a change adds, changes or renames; deleted paths add no name."""
    return changed_files("--diff-filter=d", f"{ref}...HEAD", "--", *ROOTS)


def renamed_from(ref: str) -> dict[str, str]:
    """Maps each path under include/ or src/ that a change renames to its path at ``ref``."""
    return renames(
        git("diff", "--name-status", "-M", f"{ref}...HEAD", "--", *ROOTS, check=False)
    )


def base_text(ref: str, path: str) -> str:
    """The file at ``path`` as it is in the base revision; empty when new."""
    return git("show", f"{ref}:{path}", check=False)


def added_lines(ref: str):
    """Yield (path, line, text) for each line a change adds under include/ or src/."""
    yield from added_diff_lines(
        git("diff", "-U0", f"{ref}...HEAD", "--", *ROOTS, check=False)
    )


def offenders(text: str) -> set[str]:
    """Identifiers in ``text`` that hold an address and are not a default tool name."""
    found = set()
    for m in TOKEN.finditer(text):
        if m.lastgroup != "ident":
            continue
        name = m.group()
        run = ADDRESS.search(name)
        if (
            run
            and any(c.isdigit() for c in run.group())
            and not DEFAULT.fullmatch(name)
        ):
            found.add(name)
    return found


def moved_paths() -> dict[str, str]:
    """Map each path a staged or unstaged rename moved to the path that holds it now."""
    moved: dict[str, str] = {}
    for staged in ([], ["--cached"]):
        out = git("diff", "--name-status", "-M", "-z", *staged, check=False)
        fields = out.split("\0")
        index = 0
        while index < len(fields) and fields[index]:
            status = fields[index]
            if status.startswith(("R", "C")):
                moved[fields[index + 1]] = fields[index + 2]
                index += 3
            else:
                index += 2
    return moved


def worktree_text(path: str) -> str:
    """Return a path's text; a path a rename moved reads the file that holds it now."""
    moved: dict[str, str] | None = None
    while not Path(path).is_file():
        moved = moved_paths() if moved is None else moved
        if path not in moved:
            break
        path = moved[path]
    if Path(path).is_file():
        return Path(path).read_text(encoding="utf-8", errors="replace")
    return git("show", f"HEAD:{path}", check=False)


def fold_moves(new: set[str], gone: set[str]) -> tuple[set[str], set[str]]:
    """Pair an identifier moved between files of one folder, so a rename keeps its debt."""
    left_new, left_gone = set(new), set(gone)
    for entry in sorted(gone):
        path, name = entry.split("\t", 1)
        folder = path.rsplit("/", 1)[0]
        for candidate in sorted(left_new):
            moved_path, moved_name = candidate.split("\t", 1)
            if moved_name == name and moved_path.rsplit("/", 1)[0] == folder:
                left_gone.discard(entry)
                left_new.discard(candidate)
                break
    return left_new, left_gone


def tree_entries() -> set[str]:
    files = ls_files(*ROOTS)
    entries = set()
    for path in files:
        if path.endswith(SUFFIXES):
            text = worktree_text(path)
            entries |= {f"{path}\t{name}" for name in offenders(text)}
    return entries


def baseline_entries() -> set[str]:
    if not BASELINE.is_file():
        return set()
    return {
        line
        for line in BASELINE.read_text().splitlines()
        if line and not line.startswith("#")
    }


def _report_new_names(ref: str) -> bool:
    """Print each added unnamed parameter and rejected name; True when any was found."""
    bad = False
    seen: set[str] = set()
    for path, line, text in added_lines(ref):
        for name in unnamed_parameters(text):
            print(
                f"{path}:{line}: {name}: an unnamed parameter; rename it to what it holds",
                file=sys.stderr,
            )
            bad = True
        if path.startswith(("include/psyq", "include/psx")):
            continue
        if path == "include/common/util.h":
            continue  # the generic helpers may name arrays and bits directly
        for name in rejected_names(text):
            if name in seen or in_ref(ref, name):
                continue
            seen.add(name)
            print(
                f"{path}:{line}: {name}: {rejected_reason(name)} (new name)",
                file=sys.stderr,
            )
            bad = True
    return bad


def _report_new_offsets(ref: str) -> bool:
    """Print each file that gained offset-macro accesses; True when any did."""
    bad = False
    moved = renamed_from(ref)
    for path in changed_paths(ref):
        before = macro_counts(base_text(ref, moved.get(path, path)))
        after_text = without_drafts(worktree_text(path))
        after = macro_counts(after_text)
        grown = {name: after[name] - before.get(name, 0) for name in after}
        for name, extra in sorted(grown.items()):
            if extra <= 0:
                continue
            where = [
                f"{path}:{number}"
                for number, text in enumerate(after_text.splitlines(), 1)
                if name in offset_macros(text)
            ]
            print(
                f"{where[0]}: {name}(): {extra} new offset access(es); "
                "write the member of the record or of the scratchpad view",
                file=sys.stderr,
            )
            bad = True
    return bad


def check_diff(ref: str) -> int:
    """Check the names a change adds against ``ref``."""
    bad = _report_new_names(ref)
    bad = _report_new_offsets(ref) or bad
    for message in stale_rows(layout_images(ref)):
        print(message, file=sys.stderr)
        bad = True
    if bad:
        print(f"check-names: names against {ref}", file=sys.stderr)
        return 1
    print(
        f"check-names: no new rejected names, unnamed parameters, offset accesses "
        f"or layout rows against {ref}"
    )
    return 0


def write_baseline(now: set[str]) -> int:
    """Rewrite the baseline file with the current entries."""
    BASELINE.write_text(
        "# Identifiers that still carry an address (file, name). check_names.py only lets this shrink.\n"
        + "".join(f"{e}\n" for e in sorted(now))
    )
    print(f"check-names: wrote {len(now)} entries to {BASELINE}")
    return 0


def check_baseline(now: set[str]) -> int:
    """Check that the address names only shrink against the baseline."""
    base = baseline_entries()
    new, gone = fold_moves(now - base, base - now)
    new, gone = sorted(new), sorted(gone)
    for entry in new:
        print(
            f"{entry.replace(chr(9), ': ')}: a name must not carry an address",
            file=sys.stderr,
        )
    for entry in gone:
        print(
            f"{BASELINE}: {entry.replace(chr(9), ': ')} no longer exists; delete the line",
            file=sys.stderr,
        )
    rows = stale_rows(layout_images(None))
    for message in rows:
        print(message, file=sys.stderr)
    if new or gone or rows:
        print(
            f"check-names: {len(new)} new, {len(gone)} stale, "
            f"{len(rows)} layout rows with an address name",
            file=sys.stderr,
        )
        return 1
    print(f"check-names: no new address names ({len(base)} left to rename)")
    return 0


def main(argv: list[str]) -> int:
    if argv and argv[0] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    if argv and argv[0] == "--diff":
        if len(argv) != 2:
            print("usage: python3 tools/check_names.py --diff REF", file=sys.stderr)
            return 2
        return check_diff(argv[1])
    now = tree_entries()
    if argv == ["--write"]:
        return write_baseline(now)
    return check_baseline(now)


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
