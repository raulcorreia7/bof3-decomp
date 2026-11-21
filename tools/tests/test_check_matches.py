from __future__ import annotations

import subprocess
from pathlib import Path

from fixture import put_symbols

import check_matches

TABLE = '["exe/slus_004_22"]\nOld_Name = { addr = 0x80010000 }\nNew_Name = { addr = 0x80010000 }\n'


def commit(root: Path, source: str, message: str = "x") -> str:
    (root / "src/engine/slus").mkdir(parents=True, exist_ok=True)
    (root / "src/engine/slus/f.c").write_text(source)
    git = ["git", "-c", "user.name=t", "-c", "user.email=t@t"]
    subprocess.run([*git, "add", "-A"], cwd=root, check=True)
    subprocess.run(
        [*git, "commit", "-q", "--allow-empty", "-m", message], cwd=root, check=True
    )
    return subprocess.run(
        ["git", "rev-parse", "HEAD"],
        cwd=root,
        capture_output=True,
        text=True,
        check=True,
    ).stdout.strip()


def repo(tmp_path: Path) -> tuple[Path, str]:
    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    put_symbols(tmp_path, TABLE)
    return tmp_path, commit(tmp_path, "MATCH void Old_Name(void) {\n}\n")


def test_a_match_replaced_by_include_asm_is_lost(tmp_path: Path) -> None:
    root, base = repo(tmp_path)
    head = commit(root, 'INCLUDE_ASM("x", Old_Name);\n')
    assert check_matches.lost(root, base, head) == [
        "exe/slus_004_22@0x80010000 Old_Name"
    ]
    head = commit(
        root,
        'INCLUDE_ASM("x", Old_Name);\n',
        "Match-Removed: exe/slus_004_22@0x80010000 gone",
    )
    assert check_matches.lost(root, base, head) == []


def test_a_rename_at_the_same_address_is_kept(tmp_path: Path) -> None:
    root, base = repo(tmp_path)
    head = commit(root, "MATCH void New_Name(void) {\n}\n")
    assert check_matches.lost(root, base, head) == []
