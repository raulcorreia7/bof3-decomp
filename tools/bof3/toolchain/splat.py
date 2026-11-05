"""The Splat toolchain and the per-target split stamps."""

from __future__ import annotations

import contextlib
import hashlib
import re
import shutil
import subprocess
from pathlib import Path

import yaml

from bof3.core.io import write_atomic
from bof3.core.paths import ASM, BUILD, CONFIG
from bof3.link.inputs import write_if_changed
from bof3.link.symbols import imported_map, splat_map
from bof3.link.symbols import load as load_symbols
from bof3.resolve.layout import read_splat


def split_target(root: Path, manifest_splat: str) -> subprocess.CompletedProcess[str]:
    """Run one target's Splat split; the caller decides what a failure means.

    A successful split records the digest of the files it read in
    ``asm/<target>/.splat.stamp``, so a later reader can identify stale output
    without trusting file timestamps. The split starts from an empty generated
    tree and leaves one folder per image: functions in ``asm/<target>/``, data
    in ``asm/<target>/data/``, and authored assembly in ``asm/<target>/hand/``.
    """
    executable = root / ".venv/bin/splat"
    if not executable.is_file():
        raise FileNotFoundError(
            f"missing Splat executable: {executable}; run tools/setup.sh"
        )
    target = _target_of(root, manifest_splat)
    srcdir = root / "src"
    before = set(srcdir.rglob("*.c")) if srcdir.is_dir() else set()
    # Splat only adds files: a unit the map no longer splits would leave
    # its old split assembly behind for the link to pick up.
    _clean_asm_tree(root / ASM / target)
    result = subprocess.run(
        [
            str(executable),
            "split",
            "--make-full-disasm-for-code",
            str(_build_manifest(root, target)),
        ],
        cwd=root,
        capture_output=True,
        text=True,
        check=False,
    )
    if result.returncode == 0:
        _normalize_stubs(srcdir, before)
        _extract_functions(root / ASM / target)
        _close_functions(root / ASM / target)
        _flatten_asm_tree(root / ASM / target)
        record_splat_stamp(root, target)
        normalize_linker_script(root, target)
    return result


_HAND_DIR = "hand"
_DATA_DIR = "data"


def _clean_asm_tree(base: Path) -> None:
    """Remove one target's generated assembly, keeping authored ``hand/`` files."""
    if not base.is_dir():
        return
    for name in ("nonmatchings", "matchings", _DATA_DIR):
        shutil.rmtree(base / name, ignore_errors=True)
    for child in base.iterdir():
        if child.name in (_HAND_DIR, ".splat.stamp"):
            continue
        if child.is_dir():
            shutil.rmtree(child, ignore_errors=True)
        elif child.suffix == ".s":
            child.unlink()


_NONMATCHING = re.compile(r"^nonmatching\s+([A-Za-z_]\w*),")
_GLABEL = re.compile(r"^glabel\s+([A-Za-z_]\w*)\s*$")
_ENDLABEL = re.compile(r"^endlabel\s+([A-Za-z_]\w*)\s*$")


def _extract_functions(base: Path) -> None:
    """Write one file per function from Splat's per-TU full-disassembly files."""
    for path in sorted(base.glob("*.s")):
        lines = path.read_text(encoding="utf-8", errors="replace").splitlines(
            keepends=True
        )
        index = 0
        while index < len(lines):
            start = _NONMATCHING.match(lines[index]) or _GLABEL.match(lines[index])
            if start is None:
                index += 1
                continue
            name = start[1]
            end = next(
                (
                    offset
                    for offset in range(index, len(lines))
                    if (match := _ENDLABEL.match(lines[offset])) and match[1] == name
                ),
                None,
            )
            if end is None:
                index += 1
                continue
            destination = base / f"{name}.s"
            if not destination.exists():
                destination.write_text(
                    "".join(lines[index : end + 1]), encoding="utf-8"
                )
            index = end + 1


def _close_functions(base: Path) -> None:
    """Close every function that Splat leaves open.

    Splat writes ``endlabel`` only when a function ends at its declared symbol
    size. A function that a segment boundary cuts short keeps its ``.ent`` open
    and the assembler warns about the missing ``.end``.
    """
    for path in base.rglob("*.s"):
        if path.relative_to(base).parts[0] in (_HAND_DIR, _DATA_DIR):
            continue
        text = path.read_text(encoding="utf-8", errors="replace")
        open_name = None
        for line in text.splitlines():
            if match := _GLABEL.match(line):
                open_name = match[1]
            elif _ENDLABEL.match(line):
                open_name = None
        if open_name is not None:
            suffix = "" if text.endswith("\n") else "\n"
            path.write_text(f"{text}{suffix}endlabel {open_name}\n", encoding="utf-8")


_TWO_ARG_INCLUDE = re.compile(r'INCLUDE_ASM\(\s*"[^"]*"\s*,\s*([A-Za-z_]\w*)\s*\)')
_MACRO_PROLOGUE = (
    "\n#if BOF3_USE_ASM\n"
    '__asm__(".include \\"include/match/macro.inc\\"\\n");\n'
    "#endif\n"
)
_IDENTIFIER = re.compile(r"^[A-Za-z_]\w*$")


def _normalize_stubs(srcdir: Path, before: set[Path]) -> None:
    """Write a Splat-generated C stub in the source convention.

    A code row links one object, so its C file includes the row's whole split
    assembly once, by the row's name; the per-TU file holds every function in
    order with its inter-function padding. Splat writes one
    ``INCLUDE_ASM("<asm folder>", name)`` per function instead; the build passes
    the folder as ``ASM_DIR``, so the source names only the unit.
    """
    for path in sorted(set(srcdir.rglob("*.c")) - before):
        text = path.read_text(encoding="utf-8", errors="replace")
        if "INCLUDE_ASM(" not in text:
            continue
        if _IDENTIFIER.match(path.stem):
            head = text[: text.index("INCLUDE_ASM(")]
            updated = head + f"INCLUDE_ASM({path.stem});\n"
        else:
            updated = _TWO_ARG_INCLUDE.sub(r"INCLUDE_ASM(\1)", text)
            if "macro.inc" not in updated:
                anchor = '#include "common.h"\n'
                updated = updated.replace(anchor, anchor + _MACRO_PROLOGUE, 1)
        if updated != text:
            path.write_text(updated, encoding="utf-8")


def _flatten_asm_tree(base: Path) -> None:
    """Move Splat's per-TU function files up into the image's one asm folder.

    A TU whose stem is also a function name writes both the full disassembly
    ``<stem>.s`` and the per-function ``<stem>/<stem>.s``. The full file is the
    one a C stub includes, so it wins; the matching per-function copy is
    dropped. Any other duplicate is a layout error.
    """
    for path in sorted(base.rglob("*.s")):
        relative = path.relative_to(base)
        if len(relative.parts) == 1 or relative.parts[0] in (_HAND_DIR, _DATA_DIR):
            continue
        destination = base / path.name
        if destination.exists():
            if path.parent.name != path.stem:
                raise RuntimeError(f"duplicate split assembly: {destination}")
            path.unlink()
            continue
        path.replace(destination)
    for directory in sorted(
        (path for path in base.rglob("*") if path.is_dir()), reverse=True
    ):
        if directory.parent == base and directory.name in (_HAND_DIR, _DATA_DIR):
            continue
        with contextlib.suppress(OSError):
            directory.rmdir()


def _build_manifest(root: Path, target: str) -> Path:
    """Write ``build/splat/<target>/splat.yaml``: the full manifest Splat reads.

    ``config/<target>/splat.yaml`` holds the checksum, the segments and the options
    that differ for the image; the copy under ``build/`` adds every derived option,
    so a build never rewrites ``config/`` and ``base_path`` is absolute. The copy lists
    the generated symbol maps of the target's owners, then a generated map that types
    every text row's start as a function: with one code segment per region, a forward
    reference from an earlier row would otherwise name a later function's start as a
    local ``.L`` label and the split assembly would not link.
    """
    manifest = root / CONFIG / target / "splat.yaml"
    text, document = read_splat(manifest)
    start = text.find("\nsegments:")
    if start < 0 or not document.get("sha1"):
        raise ValueError(f"{manifest}: needs `sha1:` and `segments:`")
    directory = root / BUILD / "splat" / target
    imported = directory / "symbols.imported.txt"
    write_if_changed(imported, imported_map(root, target))
    maps = [splat_map(target), str(imported)]
    auto = directory / "symbols.auto.txt"
    write_if_changed(auto, _function_symbols(document, root, [root / m for m in maps]))
    options = {
        **document["options"],
        "base_path": f"{root}/",
        "symbol_addrs_path": [*maps, str(auto)],
    }
    head = yaml.safe_dump(
        {"name": document["name"], "sha1": document["sha1"], "options": options},
        sort_keys=False,
        width=1 << 30,
    )
    path = directory / "splat.yaml"
    write_atomic(path, head + text[start + 1 :])
    return path


def _function_symbols(document: dict, root: Path, maps: list[Path]) -> str:
    """Return one ``type:func`` row per text subsegment start not already named."""
    declared = _declared_addresses(maps)
    lines = ["// Generated from the layout's text rows; never edit.\n"]
    seen: set[int] = set()
    for segment in document.get("segments") or []:
        if not isinstance(segment, dict) or not isinstance(
            segment.get("subsegments"), list
        ):
            continue
        vram = _integer(segment.get("vram", 0))
        start = _integer(segment.get("start", 0))
        for row in segment["subsegments"]:
            if isinstance(row, list):
                offset = _integer(row[0])
                kind = str(row[1])
            else:
                offset = _integer(row["start"])
                kind = str(row["type"])
            if kind not in ("c", "asm"):
                continue
            address = vram + offset - start
            if address in seen or address in declared:
                continue
            seen.add(address)
            lines.append(f"func_{address:08X} = 0x{address:08X}; // type:func\n")
    return "".join(lines)


_SYMBOL_ROW = re.compile(r"=\s*0x([0-9A-Fa-f]+)\s*;")


def _declared_addresses(maps: list[Path]) -> set[int]:
    """Return every address the generated symbol maps already name."""
    found: set[int] = set()
    for path in maps:
        found.update(
            int(m, 16) for m in _SYMBOL_ROW.findall(path.read_text(encoding="utf-8"))
        )
    return found


def _integer(value: object) -> int:
    return int(value, 0) if isinstance(value, str) else int(value)


def normalize_linker_script(root: Path, target: str) -> bool:
    """Correct Splat's build prefix in generated asset and PsyQ object selectors.

    Splat roots every object under ``build/``, and twice for a path outside it. Staged PsyQ members live in
    ``toolchains/psyq``, which an ``o`` row names as ``toolchains/psyq/...``. PsyQ objects name their read-only
    section ``.rdata``; Splat selects ``.rodata``.
    """
    path = root / BUILD / ASM / target / "linker.ld"
    try:
        original = path.read_text(encoding="utf-8")
    except FileNotFoundError:
        return False
    updated = original.replace("build/build/assets", "build/assets").replace(
        "build/build/toolchains/psyq/", "toolchains/psyq/"
    )
    updated = re.sub(r"(toolchains/psyq/\S+\.o)\(\.rodata\)", r"\1(.rdata)", updated)
    if updated == original:
        return False
    write_atomic(path, updated)
    return True


#: Digest of the files that decide one target's generated ``asm/`` tree.
SPLAT_STAMP = ".splat.stamp"


def _target_of(root: Path, manifest_splat: str) -> str:
    """Return the target id a manifest path belongs to."""
    parent = Path(manifest_splat)
    if parent.is_absolute():
        try:
            return parent.resolve().parent.relative_to(root / CONFIG).as_posix()
        except ValueError:
            return parent.parent.name
    return parent.parent.as_posix().removeprefix("config/")


def splat_inputs(root: Path, target: str) -> list[Path]:
    """Return the files that decide one target's Splat output.

    ``splat.yaml``, its owners' generated symbol maps, and the target bytes named by
    ``options.target_path`` all affect the generated assembly and linker script. The
    target's own ``config/symbols.toml`` rows count too (see :func:`splat_input_digest`).
    """
    manifest = root / CONFIG / target / "splat.yaml"
    paths = [manifest]
    try:
        _text, document = read_splat(manifest)
    except (OSError, yaml.YAMLError):
        document = None
    data = document or {}
    paths += [root / splat_map(owner) for owner in data.get("symbol_owners") or ()]
    target_path = (data.get("options") or {}).get("target_path")
    if isinstance(target_path, str):
        paths.append(root / target_path)
    return [path for path in paths if path.is_file()]


def splat_input_digest(root: Path, target: str) -> str:
    """Digest over the paths and bytes Splat reads for one target and this post-processor."""
    digest = hashlib.sha1(Path(__file__).read_bytes())
    try:
        _text, document = read_splat(root / CONFIG / target / "splat.yaml")
        # The options the id derives (src_path, asm_path, ...) decide the output too.
        digest.update(repr(sorted((document.get("options") or {}).items())).encode())
    except (OSError, yaml.YAMLError):
        pass
    # The target's own rows decide the names of its split functions only when its
    # ``symbol_owners`` list it; hashing them here means an edit to one target's rows
    # re-splits that target and no other, whatever ``symbol_owners`` says.
    for entry in load_symbols(root).get(target, ()):
        if not entry.alias:
            digest.update(
                f"{entry.name} {entry.addr:x} {entry.type} {entry.size}\n".encode()
            )
    for path in sorted(splat_inputs(root, target)):
        digest.update(path.relative_to(root).as_posix().encode())
        digest.update(hashlib.sha1(path.read_bytes()).digest())
    return digest.hexdigest()


def splat_output_current(root: Path, target: str) -> bool:
    """Return True when ``asm/<target>`` was split from the current Splat inputs.

    A symbol-map or payload edit changes ``splat_input_digest``, so the
    generated tree is stale even though its files still exist.
    """
    recorded = root / ASM / target / SPLAT_STAMP
    try:
        saved = recorded.read_text(encoding="utf-8").strip()
    except OSError:
        return False
    return saved == splat_input_digest(root, target)


def record_splat_stamp(root: Path, target: str) -> None:
    """Record the digest of the inputs used to produce ``asm/<target>``."""
    write_atomic(
        root / ASM / target / SPLAT_STAMP, splat_input_digest(root, target) + "\n"
    )
