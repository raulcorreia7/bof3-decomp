#!/usr/bin/env python3
"""Generate include/menu/message_ids.h and check include/msg/messages.def against src/.

A message id is an index into the area message table (include/menu/gameui.h). The
scan recognises the id argument of every call, macro and write that carries one:

    UI_MessageStartArea, UI_MessageRequest, Scene_ShowMessage,
    MESSAGE_START_WAIT, SCENARIO_MESSAGE_WAIT, SCENA14_START_AREA_MESSAGE,
    WORLD_ARM_ANSWER_MESSAGE, WORLD_ARM_ANSWER_MESSAGE_IDLE,
    MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, ...),
    func_801D0DD4, func_801D10AC, and `g_UIMessageRequest = <id>`.

Comments and string literals are ignored. The distinct values become one numbered
define each, in decimal, sorted; uses of the names are collected too, so a value
stays in the header after its last literal is rewritten. MESSAGE_NONE (0xFFFF)
keeps its name.

Ids of a module listed in include/msg/messages.def (the archive is a folder of the file's
path, e.g. area037) use MSG_<ARCHIVE>_<TAG> from the enum in include/msg/message_ids.h; the
commu, shop, start, plchar and Fairy_* files use the AREA175 bank. All other ids stay flat MSG_nnn
in include/menu/message_ids.h until their module is converted.

    tools/message_ids.py            write the flat header
    tools/message_ids.py --check    exit 1 when the header is stale or a module id has no line
    tools/message_ids.py --list     print the values and their sites
    tools/message_ids.py --rewrite  rewrite literal and flat sites to the module names
    tools/message_ids.py --seed     append untagged lines to messages.def for unlisted ids
"""

from __future__ import annotations

import argparse
import re
import sys
from collections import defaultdict
from pathlib import Path

from bof3.core.paths import ROOT

HEADER = ROOT / "include/menu/message_ids.h"
DEF = ROOT / "include/msg/messages.def"
SOURCES = ROOT / "src"
SUFFIXES = (".c", ".h", ".inc")

NUMBER = r"(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*"
MESSAGE_NONE = 0xFFFF
FIRST_ARG = (
    "UI_MessageStartArea",
    "UI_MessageRequest",
    "Scene_ShowMessage",
    "MESSAGE_START_WAIT",
    "SCENARIO_MESSAGE_WAIT",
    "SCENA14_START_AREA_MESSAGE",
    "WORLD_ARM_ANSWER_MESSAGE",
    "func_801D0DD4",
    "func_801D10AC",
)
FIRST_ARG_RE = re.compile(
    r"\b(" + "|".join(FIRST_ARG) + r")\s*\(\s*(" + NUMBER + r")\b"
)
IDLE_RE = re.compile(
    r"\bWORLD_ARM_ANSWER_MESSAGE_IDLE\s*\(\s*("
    + NUMBER
    + r")\s*,\s*("
    + NUMBER
    + r")\s*\)"
)
TEXT_RE = re.compile(
    r"\bMESSAGE_TABLE_TEXT\s*\(\s*AREA_MESSAGE_TABLE\s*,\s*(" + NUMBER + r")\s*\)"
)
WRITE_RE = re.compile(r"\bg_UIMessageRequest\s*=\s*(" + NUMBER + r")\s*;")
NAME_RE = re.compile(r"\bMSG_(\d+)\b")
MASK_RE = re.compile(
    r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.DOTALL
)


def to_int(text: str) -> int:
    return int(text.rstrip("uUlL"), 0)


def masked(text: str) -> str:
    return MASK_RE.sub(lambda match: re.sub(r"[^\n]", " ", match.group(0)), text)


DEF_RE = re.compile(
    r"\bDEFINE_MESSAGE\s*\(\s*(\w+)\s*,\s*(" + NUMBER + r")\s*,\s*(\w+)\s*\)"
)
SYSTEM = "system"
SYSTEM_CALL_RE = re.compile(r"\bUI_MessageRequest\s*\(\s*")
Tags = dict[str, dict[int, str]]
TAG_NAMES: dict[str, tuple[str, int]] = {}
TAG_NAMES_SECTIONS: set[str] = set()


def load_tags() -> Tags:
    """Parse messages.def: lowercase archive -> {id: tag}."""
    tags: Tags = {}
    if DEF.exists():
        text = masked(DEF.read_text(encoding="utf-8"))
        for match in DEF_RE.finditer(text):
            tags.setdefault(match.group(1).lower(), {})[to_int(match.group(2))] = (
                match.group(3)
            )
    TAG_NAMES.clear()
    TAG_NAMES_SECTIONS.clear()
    TAG_NAMES_SECTIONS.update(tags)
    for section, table in tags.items():
        for value, tag in table.items():
            TAG_NAMES[tag_name(section, value, tag)] = (section, value)
    return tags


def tag_name(section: str, value: int, tag: str | None) -> str:
    return f"MSG_{section.upper()}_{tag or f'{value:03d}'}"


# Modules with no archive of their own read the faerie village bank (AREA175): the commu
# overlays, the shop and start menus, plchar and the shared Fairy_* answer headers.
FAERIE_BANK = "area175"
FAERIE_FILES = ("UI_MessageAnswerSet.h",)


def faerie_bank(path: Path) -> bool:
    parts = path.parts
    return (
        path.name.startswith("Fairy")
        or path.name in FAERIE_FILES
        or any(part.startswith("commu") or part in ("shop", "plchar") for part in parts)
        or any(
            a == "menu" and b == "start" for a, b in zip(parts, parts[1:], strict=False)
        )
    )


def module_of(path: Path, tags: Tags) -> str | None:
    """The tagged archive that is a folder of `path`, or the bank its module shares."""
    for part in path.parts:
        if part in tags and part != SYSTEM:
            return part
    if FAERIE_BANK in tags and faerie_bank(path):
        return FAERIE_BANK
    return None


def system_starts(text: str) -> set[int]:
    """Offsets of the id argument of every UI_MessageRequest: the system table, not the area's."""
    if SYSTEM not in TAG_NAMES_SECTIONS:
        return set()
    return {match.end() for match in SYSTEM_CALL_RE.finditer(text)}


def site_section(text, start, end, is_name, module, system):
    """The table a site reads: its own tagged name, the system table, or the file's module."""
    if is_name and text[start:end] in TAG_NAMES:
        return TAG_NAMES[text[start:end]][0]
    return SYSTEM if start in system else module


def sites(text: str) -> list[tuple[int, int, int, bool]]:
    """Return (first offset, last offset, value, is_name) for every message id."""
    found = []
    for match in FIRST_ARG_RE.finditer(text):
        found.append((match.start(2), match.end(2), to_int(match.group(2)), False))
    for match in IDLE_RE.finditer(text):
        for group in (1, 2):
            found.append(
                (
                    match.start(group),
                    match.end(group),
                    to_int(match.group(group)),
                    False,
                )
            )
    for match in TEXT_RE.finditer(text):
        found.append((match.start(1), match.end(1), to_int(match.group(1)), False))
    for match in WRITE_RE.finditer(text):
        found.append((match.start(1), match.end(1), to_int(match.group(1)), False))
    for match in NAME_RE.finditer(text):
        word = match.group(0)
        if word in TAG_NAMES:
            found.append((match.start(), match.end(), TAG_NAMES[word][1], True))
        elif match.group(1) is not None:
            found.append((match.start(), match.end(), int(match.group(1), 10), True))
    return [item for item in found if item[2] != MESSAGE_NONE]


def source_files():
    for path in sorted(SOURCES.rglob("*")):
        if path.suffix in SUFFIXES and path.is_file():
            yield path


Ids = dict[str | None, dict[int, list[tuple[Path, int]]]]


def scan(tags: Tags) -> tuple[Ids, int]:
    """Collect module -> id -> sites; module None holds the flat MSG_nnn ids."""
    ids: Ids = defaultdict(lambda: defaultdict(list))
    width = 3
    for path in source_files():
        rel = path.relative_to(ROOT)
        module = module_of(rel, tags)
        text = masked(path.read_text(encoding="utf-8", errors="surrogateescape"))
        system = system_starts(text)
        for start, end, value, is_name in sites(text):
            key = site_section(text, start, end, is_name, module, system)
            ids[key][value].append((rel, text.count("\n", 0, start) + 1))
            if key is None:
                width = max(width, len(str(value)))
    return ids, width


def name(section: str | None, value: int, width: int, tags: Tags) -> str:
    if section is None:
        return f"MSG_{value:0{width}d}"
    return tag_name(section, value, tags[section].get(value))


def missing(ids: Ids, tags: Tags) -> list[tuple[str, int]]:
    return [
        (section, value)
        for section in sorted(s for s in ids if s is not None)
        for value in sorted(ids[section])
        if value not in tags[section]
    ]


def unknown_names() -> list[tuple[Path, int, str]]:
    """MSG_ names in src/ that neither the flat header nor messages.def defines."""
    found = []
    for path in source_files():
        text = masked(path.read_text(encoding="utf-8", errors="surrogateescape"))
        for match in re.finditer(r"\bMSG_[A-Za-z]\w*", text):
            if match.group(0) not in TAG_NAMES:
                found.append(
                    (
                        path.relative_to(ROOT),
                        text.count("\n", 0, match.start()) + 1,
                        match.group(0),
                    )
                )
    return found


def render(ids: Ids, width: int) -> str:
    lines = [
        "/* Generated by tools/message_ids.py from the literal message ids in src/.",
        " * Do not edit; regenerate with `python3 tools/message_ids.py`.",
        " * The flat ids of modules not yet in include/msg/messages.def; each is an index",
        " * into that module's message table (include/menu/gameui.h). */",
        "#ifndef MENU_MESSAGE_IDS_H",
        "#define MENU_MESSAGE_IDS_H",
        "",
        '#include "msg/message_ids.h"',
    ]
    defines = [
        f"#define {name(None, v, width, {})} {v}" for v in sorted(ids.get(None, {}))
    ]
    if defines:
        lines += ["", *defines]
    lines += ["", "#endif", ""]
    return "\n".join(lines)


def rewrite_text(
    text: str, names: dict[int, str], system_names: dict[int, str] | None = None
) -> str:
    """Rewrite the literal ids and flat MSG_nnn names in `text`: UI_MessageRequest ids to
    `system_names`, the others to `names`; a value with no entry stays as written.
    """
    masked_text = masked(text)
    system = system_starts(masked_text) if system_names is not None else set()
    new = text
    for start, end, value, is_name in sorted(sites(masked_text), reverse=True):
        if is_name and text[start:end] in TAG_NAMES:
            continue
        table = system_names if start in system else names
        if table is None or value not in table:
            continue
        new = new[:start] + table[value] + new[end:]
    return new


def rewrite() -> int:
    """Rewrite the sites of every tagged module and every UI_MessageRequest to their names."""
    tags = load_tags()
    ids, width = scan(tags)
    absent = missing(ids, tags)
    if absent:
        print("message-ids: run --seed first; no line for", absent, file=sys.stderr)
        return 1
    system_names = {v: name(SYSTEM, v, width, tags) for v in ids.get(SYSTEM, {})}
    changed = 0
    for path in source_files():
        module = module_of(path.relative_to(ROOT), tags)
        names = {v: name(module, v, width, tags) for v in ids[module]} if module else {}
        text = path.read_text(encoding="utf-8", errors="surrogateescape")
        new = rewrite_text(text, names, system_names if SYSTEM in tags else None)
        if new != text:
            path.write_text(new, encoding="utf-8")
            changed += 1
    print(f"rewrote {changed} file(s)")
    return 0


def seed(ids: Ids, tags: Tags) -> int:
    """Append an untagged DEFINE_MESSAGE line for every id a tagged module uses without one."""
    text = DEF.read_text(encoding="utf-8")
    for section, value in missing(ids, tags):
        line = f"DEFINE_MESSAGE({section.upper()}, 0x{value:03X}, {value:03d})\n"
        header = f"/* {section.upper()} */\n"
        if header not in text:
            text += f"\n{header}"
        head, _, rest = text.partition(header)
        end = rest.find("\n\n")
        end = len(rest) if end < 0 else end + 1
        text = (
            head
            + header
            + rest[:end].rstrip("\n")
            + "\n"
            + line
            + rest[end:].lstrip("\n")
            if rest[end:].strip() == ""
            else head
            + header
            + rest[:end].rstrip("\n")
            + "\n"
            + line
            + "\n"
            + rest[end:].lstrip("\n")
        )
    DEF.write_text(text, encoding="utf-8")
    print(f"seeded {len(missing(ids, tags))} line(s)")
    return 0


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument(
        "--check", action="store_true", help="fail when the header is stale"
    )
    parser.add_argument(
        "--list", action="store_true", help="print each value with its sites"
    )
    parser.add_argument(
        "--rewrite", action="store_true", help="rewrite the sites to the module names"
    )
    parser.add_argument(
        "--seed", action="store_true", help="append untagged lines to messages.def"
    )
    args = parser.parse_args(argv)

    if args.rewrite:
        return rewrite()

    if not SOURCES.is_dir():
        print("message-ids: no src/ to scan")
        return 0

    tags = load_tags()
    ids, width = scan(tags)
    if not ids and not tags and not HEADER.exists():
        print(f"message-ids: no message ids; {HEADER.relative_to(ROOT)} is not needed")
        return 0
    if args.seed:
        return seed(ids, tags)
    if args.list:
        for section in sorted(ids, key=lambda k: (k is not None, k or "")):
            for value in sorted(ids[section]):
                label = (
                    name(section, value, width, tags)
                    if section in tags or section is None
                    else str(value)
                )
                print(f"{label} {value} ({len(ids[section][value])} site(s))")
                for path, line_no in ids[section][value][:3]:
                    print(f"    {path}:{line_no}")
        return 0

    text = render(ids, width)
    if args.check:
        absent = missing(ids, tags)
        for section, value in absent:
            print(
                f"message-ids: {section} id {value} has no line in {DEF.relative_to(ROOT)}",
                file=sys.stderr,
            )
        for path, line_no, word in unknown_names():
            absent.append((word, 0))
            print(
                f"message-ids: {path}:{line_no} {word} is not in {DEF.relative_to(ROOT)}",
                file=sys.stderr,
            )
        current = HEADER.read_text(encoding="utf-8") if HEADER.exists() else ""
        if current != text:
            print(
                f"{HEADER.relative_to(ROOT)} is stale; run tools/message_ids.py",
                file=sys.stderr,
            )
            return 1
        print(f"message-ids: {HEADER.relative_to(ROOT)} is current")
        return 1 if absent else 0

    HEADER.parent.mkdir(parents=True, exist_ok=True)
    HEADER.write_text(text, encoding="utf-8")
    print(f"wrote {HEADER.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
