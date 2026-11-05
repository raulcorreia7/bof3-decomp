"""The report scores an INCLUDE_ASM body as unmatched and a compiled body as matched."""

from __future__ import annotations

import json
import re
import struct
import subprocess
from pathlib import Path

import pytest

import objdiff_config

ROOT = Path(__file__).resolve().parents[2]
SUFFIX = ".NON_MATCHING"
#: `jr $ra; nop` and `jr $ra; addiu $v0, $zero, 1`, little-endian.
INCLUDE_BODY = struct.pack("<II", 0x03E00008, 0)
COMPILED_BODY = struct.pack("<II", 0x03E00008, 0x24020001)


def unit_object(path: Path) -> Path:
    """Write a two-function MIPS object whose first function is an INCLUDE_ASM body.

    The compiled object marks an INCLUDE_ASM body with a ``<name>.NON_MATCHING`` alias.
    """
    text = INCLUDE_BODY + COMPILED_BODY
    names = [b"func_A", b"func_A" + SUFFIX.encode(), b"func_B"]
    strings = b"\0" + b"\0".join(names) + b"\0"
    starts = [1 + sum(len(name) + 1 for name in names[:i]) for i in range(len(names))]
    symbols = struct.pack("<IIIBBH", 0, 0, 0, 0, 0, 0)
    for start, value in zip(starts, (0, 0, 8), strict=True):
        symbols += struct.pack("<IIIBBH", start, value, 8, 0x12, 0, 1)
    shstrtab = b"\0.text\0.symtab\0.strtab\0.shstrtab\0"
    bodies = [b"", text, symbols, strings, shstrtab]
    offsets = []
    position = 52
    for body in bodies:
        offsets.append(position)
        position += len(body)
    names_at = [0, 1, 7, 15, 23]
    kinds = [0, 1, 2, 3, 3]
    sections = b"".join(
        struct.pack(
            "<10I",
            names_at[i],
            kinds[i],
            6 if i == 1 else 0,
            0,
            offsets[i],
            len(bodies[i]),
            3 if i == 2 else 0,
            1 if i == 2 else 0,
            4 if i == 1 else 1,
            16 if i == 2 else 0,
        )
        for i in range(len(bodies))
    )
    header = (
        b"\x7fELF\x01\x01\x01"
        + bytes(9)
        + struct.pack(
            "<HHIIIIIHHHHHH", 1, 8, 1, 0, 0, position, 0x1000, 52, 0, 0, 40, 5, 4
        )
    )
    path.write_bytes(header + b"".join(bodies) + sections)
    return path


def project(tmp_path: Path) -> objdiff_config.Project:
    cfg = {"nonmatching_suffix": SUFFIX, "report_objects": str(tmp_path / "report")}
    pattern = re.compile("")
    return objdiff_config.Project(tmp_path, cfg, pattern, pattern, pattern, pattern)


def test_an_include_asm_body_is_overwritten_and_a_compiled_body_is_kept(
    tmp_path: Path,
) -> None:
    built = unit_object(tmp_path / "src+unit.c.o")
    copy, unlifted = project(tmp_path).report_base(built)
    assert unlifted
    assert copy != built
    text = copy.read_bytes()[52:68]
    assert text[:8] != INCLUDE_BODY
    assert text[8:] == COMPILED_BODY
    assert built.read_bytes()[52:68] == INCLUDE_BODY + COMPILED_BODY


def test_an_object_without_an_include_asm_body_is_used_as_built(tmp_path: Path) -> None:
    built = tmp_path / "src+unit.c.o"
    unit_object(built)
    built.write_bytes(built.read_bytes().replace(SUFFIX.encode(), b".OTHERNAME_"))
    assert project(tmp_path).report_base(built) == (built, False)


def objdiff() -> str | None:
    found = subprocess.run(
        [str(ROOT / "bin/internal/find-tool"), "objdiff-cli"],
        capture_output=True,
        text=True,
        check=False,
    )
    return found.stdout.strip() or None


@pytest.mark.skipif(objdiff() is None, reason="objdiff-cli is not installed")
def test_objdiff_scores_the_include_asm_function_unmatched(tmp_path: Path) -> None:
    unit_object(tmp_path / "target.o")
    base, unlifted = project(tmp_path).report_base(unit_object(tmp_path / "base.o"))
    assert unlifted
    (tmp_path / "objdiff.json").write_text(
        json.dumps(
            {
                "build_target": False,
                "build_base": False,
                "units": [
                    {
                        "name": "t/unit",
                        "target_path": "target.o",
                        "base_path": str(base.relative_to(tmp_path)),
                        "metadata": {
                            "complete": False,
                            "progress_categories": ["game"],
                        },
                    }
                ],
                "progress_categories": [{"id": "game", "name": "game"}],
            }
        )
    )
    output = tmp_path / "report.json"
    subprocess.run(
        [str(objdiff()), "report", "generate", "-p", str(tmp_path), "-o", str(output)],
        check=True,
        capture_output=True,
    )
    unit = json.loads(output.read_text())["units"][0]
    scores = {
        fn["name"]: fn.get("fuzzy_match_percent", 0.0) for fn in unit["functions"]
    }
    assert scores["func_A"] < 100.0
    assert scores["func_B"] == 100.0
    assert unit["measures"]["matched_functions"] == 1
    assert unit["measures"]["total_functions"] == 2


def test_a_readable_data_name_is_defined_at_its_row_address(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    """A target reference to a readable data row takes its address, as an address name does.

    The compiled base folds ``g_BattleActionLock`` into a constant; without the definition the
    target keeps a relocation and objdiff scores the same bytes as a mismatch.
    """
    calls: list[list[str]] = []

    def command(self: objdiff_config.Project, argv: list[str]) -> str:
        calls.append(argv)
        if argv[1:2] == ["-u"]:
            return (
                "         U g_BattleActionLock\n"
                "         U D_80140000\n"
                "         U func_8014D978\n"
                "         U g_Unknown\n"
            )
        return ""

    monkeypatch.setattr(objdiff_config.Project, "command", command)
    cfg = {
        "assembler": "as",
        "nm": "nm",
        "objcopy": "objcopy",
        "assembler_flags": [],
        "asm_include": [],
        "data_label": "dlabel",
        "nonmatching_suffix": SUFFIX,
    }
    pattern = re.compile(r"^(?:D|T|jtbl)_([0-9A-Fa-f]+)$")
    proj = objdiff_config.Project(tmp_path, cfg, pattern, pattern, pattern, pattern)
    source = tmp_path / "f.s"
    source.write_text("nop\n", encoding="utf-8")
    proj.assemble(
        [source], tmp_path / "out" / "f.o", {"g_BattleActionLock": 0x801463CE}
    )
    flags = [arg for argv in calls for arg in argv if arg.startswith("--defsym=")]
    assert flags == [
        "--defsym=g_BattleActionLock=0x801463CE",
        "--defsym=D_80140000=0x80140000",
    ]


def test_a_function_or_unlisted_name_is_left_to_the_link() -> None:
    rows = objdiff_config._readable_data(ROOT, "emi/battle/battle/03")
    assert rows["g_BattleActionLock"] == 0x801463CE
    assert "Actor_Clear" not in rows
    assert not any(name.startswith(("func_", "D_")) for name in rows)
