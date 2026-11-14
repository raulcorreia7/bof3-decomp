from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "tools/check_tree.sh"
ENUM = ROOT / "tools/check_enum_members.py"
SOURCES = ROOT / "tools/check_sources.py"
PACKAGE = ROOT / "tools/bof3"


def run_tree(
    repo: Path,
    base_files: dict[str, str],
    change_files: dict[str, str],
    removed: tuple[str, ...] = (),
) -> subprocess.CompletedProcess[str]:
    (repo / "tools").mkdir()
    (repo / "tools/check_tree.sh").write_text(SCRIPT.read_text())
    (repo / "tools/check_enum_members.py").write_text(ENUM.read_text())
    (repo / "tools/check_sources.py").write_text(SOURCES.read_text())
    shutil.copytree(
        PACKAGE, repo / "tools/bof3", ignore=shutil.ignore_patterns("__pycache__")
    )
    # One image whose layout compiles the sources the cases add.
    layout = repo / "config/emi/test/arc/00/splat.yaml"
    layout.parent.mkdir(parents=True)
    layout.write_text(
        "segments:\n"
        "  - type: code\n"
        "    start: 0\n"
        "    subsegments:\n"
        "      - [0x0, c, a]\n"
        "      - [0x4, c, b]\n"
    )

    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    for name, text in base_files.items():
        path = repo / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    git("add", ".")
    git("commit", "-qm", "base")
    for name in removed:
        (repo / name).unlink()
    for name, text in change_files.items():
        path = repo / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    git("add", "-A")
    git("commit", "-qm", "change")
    return subprocess.run(
        ["sh", "tools/check_tree.sh", "HEAD~1"],
        cwd=repo,
        check=False,
        capture_output=True,
        text=True,
    )


CASES = [
    ("pass", {}, {"src/overlays/test/arc/00/a.c": "void f(s32 x);\n"}, None),
    (
        "duplicate prototype",
        {"include/a.h": "void f(void);\n"},
        {"src/overlays/test/arc/00/b.h": "void f(void);\n"},
        "duplicate declaration",
    ),
    (
        "header guard",
        {},
        {"include/new.h": "#ifndef WRONG\n#define WRONG\n#endif\n"},
        "header guard",
    ),
    (
        "raw address",
        {},
        {"src/overlays/test/arc/00/a.c": "u32 x = 0x801D933C;\n"},
        "raw address",
    ),
    (
        "register pin",
        {},
        {"src/overlays/test/arc/00/a.c": 'asm("$0");\n'},
        "register pin",
    ),
    (
        "decompiler local",
        {},
        {"src/overlays/test/arc/00/a.c": "s32 temp_a;\n"},
        "decompiler local",
    ),
    (
        "task offset",
        {},
        {"src/overlays/test/arc/00/a.c": "u8 *p = ((u8 *)g_Task);\n"},
        "task read by offset",
    ),
]


@pytest.mark.parametrize("name,base,change,message", CASES)
def test_source_rules_on_added_lines(
    tmp_path: Path,
    name: str,
    base: dict[str, str],
    change: dict[str, str],
    message: str | None,
) -> None:
    result = run_tree(tmp_path, base, change)
    output = result.stdout + result.stderr
    if message is None:
        assert result.returncode == 0, output
    else:
        assert result.returncode == 1, output
        assert message in output, output


RENAMED_BODY = (
    '#include "battle_03.h"\n'
    "MATCH void func_801D9C80(void) {\n"
    "    s16 var_s0 = 1;\n"
    "    FIELD(g_Task, 0x10) = var_s0;\n"
    "    Battle_DrawWindowTile(var_s0, 2, 8U, 1U);\n"
    "}\n"
)


def run_rename(tmp_path: Path, changed_body: str) -> subprocess.CompletedProcess[str]:
    return run_tree(
        tmp_path,
        {"src/overlays/test/arc/00/func_801D9C80.c": RENAMED_BODY},
        {"src/overlays/test/arc/00/b.c": changed_body},
        removed=("src/overlays/test/arc/00/func_801D9C80.c",),
    )


def test_renamed_file_with_one_word_change_passes(tmp_path: Path) -> None:
    body = RENAMED_BODY.replace("Battle_DrawWindowTile(", "Battle_DrawTile(")
    result = run_rename(tmp_path, body)
    output = result.stdout + result.stderr
    assert result.returncode == 0, output
    assert "decompiler local" not in output, output


def test_renamed_file_gaining_a_local_fails(tmp_path: Path) -> None:
    body = RENAMED_BODY.replace(
        "    Battle_DrawWindowTile(var_s0, 2, 8U, 1U);\n",
        "    s16 var_s1 = 2;\n    Battle_DrawWindowTile(var_s0, var_s1, 8U, 1U);\n",
    )
    result = run_rename(tmp_path, body)
    output = result.stdout + result.stderr
    assert result.returncode == 1, output
    assert "decompiler local" in output and "var_s1" in output, output
