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


EXE = "exe/slus_004_22"
GAME = "emi/etc/game/00"
ENGINE_TABLES = (
    f'["{EXE}"]\nSYS_Renamed = {{ addr = 0x8014B9AC }}\n'
    f'["{GAME}"]\nGame_Named = {{ addr = 0x80196000 }}\n'
)
BOTH = (
    "MATCH void func_8014B9AC(void) {\n}\n"
    "MATCH void Game_Named(void) {\n}\n"
    "MATCH void func_80197000(void) {\n}\n"
)


def engine_repo(tmp_path: Path) -> tuple[Path, str]:
    """A module folder shared by both engine images, each with its own address range."""
    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    put_symbols(tmp_path, ENGINE_TABLES)
    for image, low, high in (
        (EXE, 0x80096800, 0x8018B1DC),
        (GAME, 0x80195800, 0x801C71C4),
    ):
        splat = tmp_path / "config" / image / "splat.yaml"
        splat.parent.mkdir(parents=True)
        splat.write_text(f"segments:\n    vram: {low:#x}\n    vram: {high:#x}\n")
    return tmp_path, engine_commit(tmp_path, BOTH)


def engine_commit(root: Path, source: str, message: str = "x") -> str:
    (root / "src/engine/sys").mkdir(parents=True, exist_ok=True)
    (root / "src/engine/sys/f.c").write_text(source)
    git = ["git", "-c", "user.name=t", "-c", "user.email=t@t"]
    subprocess.run([*git, "add", "-A"], cwd=root, check=True)
    subprocess.run([*git, "commit", "-q", "-m", message], cwd=root, check=True)
    return subprocess.run(
        ["git", "rev-parse", "HEAD"],
        cwd=root,
        capture_output=True,
        text=True,
        check=True,
    ).stdout.strip()


def test_an_executable_function_renamed_away_from_its_address_name_loses_nothing(
    tmp_path: Path,
) -> None:
    root, base = engine_repo(tmp_path)
    head = engine_commit(root, BOTH.replace("func_8014B9AC", "SYS_Renamed"))
    assert check_matches.lost(root, base, head) == []


def test_a_downgrade_in_the_executable_is_lost(tmp_path: Path) -> None:
    root, base = engine_repo(tmp_path)
    head = engine_commit(
        root,
        BOTH.replace(
            "MATCH void func_8014B9AC(void) {\n}\n",
            'INCLUDE_ASM("x", func_8014B9AC);\n',
        ),
    )
    assert check_matches.lost(root, base, head) == [f"{EXE}@0x8014B9AC func_8014B9AC"]


def test_a_downgrade_in_the_game_image_is_lost(tmp_path: Path) -> None:
    root, base = engine_repo(tmp_path)
    for name, addr in (("func_80197000", 0x80197000), ("Game_Named", 0x80196000)):
        head = engine_commit(
            root,
            BOTH.replace(
                f"MATCH void {name}(void) {{\n}}\n", f'INCLUDE_ASM("x", {name});\n'
            ),
        )
        assert check_matches.lost(root, base, head) == [f"{GAME}@0x{addr:08X} {name}"]
