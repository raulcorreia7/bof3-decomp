from __future__ import annotations

import subprocess
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
SCRIPT = ROOT / "tools/check_tree.sh"
ENUM = ROOT / "tools/check_enum_members.py"


def run_tree(
    repo: Path, base_files: dict[str, str], change_files: dict[str, str]
) -> subprocess.CompletedProcess[str]:
    (repo / "tools").mkdir()
    (repo / "tools/check_tree.sh").write_text(SCRIPT.read_text())
    (repo / "tools/check_enum_members.py").write_text(ENUM.read_text())

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
    for name, text in change_files.items():
        path = repo / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    git("add", ".")
    git("commit", "-qm", "change")
    return subprocess.run(
        ["sh", "tools/check_tree.sh", "HEAD~1"],
        cwd=repo,
        capture_output=True,
        text=True,
    )


CASES = [
    ("pass", {}, {"src/a.c": "void f(s32 x);\n"}, None),
    (
        "duplicate prototype",
        {"include/a.h": "void f(void);\n"},
        {"src/b.h": "void f(void);\n"},
        "duplicate declaration",
    ),
    (
        "header guard",
        {},
        {"include/new.h": "#ifndef WRONG\n#define WRONG\n#endif\n"},
        "header guard",
    ),
    ("raw address", {}, {"src/a.c": "u32 x = 0x801D933C;\n"}, "raw address"),
    ("register pin", {}, {"src/a.c": 'asm("$0");\n'}, "register pin"),
    ("decompiler local", {}, {"src/a.c": "s32 temp_a;\n"}, "decompiler local"),
    (
        "task offset",
        {},
        {"src/a.c": "u8 *p = ((u8 *)g_Task);\n"},
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
