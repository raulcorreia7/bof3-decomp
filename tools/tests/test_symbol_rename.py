from __future__ import annotations

import subprocess
import tomllib
from pathlib import Path

import pytest
from fixture import main, put_symbols

from bof3.adapters.git import git
from bof3.errors import SymbolError
from bof3.symbols.context import Context


@pytest.fixture
def repo(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> Path:
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    files = {
        "config/symbols/exe+a.toml": '["exe/a"]\nOld = { addr = 0x80000000, type = "func" }\n',
        "config/exe/a/splat.yaml": "- [0x0, c, Old]\n",
        "src/a/Old.c": "MATCH void Old(void) {}\n",
        "include/a.h": "void Old(void);\n",
    }
    for name, text in files.items():
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    subprocess.run(["git", "-C", str(tmp_path), "add", "."], check=True)
    return tmp_path


def snapshot(root: Path) -> tuple[dict[str, bytes], bytes]:
    files = {
        p.relative_to(root).as_posix(): p.read_bytes()
        for folder in ("src", "include", "config")
        for p in (root / folder).rglob("*")
        if p.is_file()
    }
    return files, (root / ".git/index").read_bytes()


def test_preflight_failure_leaves_files_and_index_unchanged(repo: Path) -> None:
    (repo / "src/a/New.c").write_text("untracked destination\n")
    before = snapshot(repo)
    with pytest.raises((SymbolError, subprocess.CalledProcessError, OSError)):
        main(repo, ["rename", "Old", "New"])
    assert snapshot(repo) == before


def test_a_failed_second_move_rolls_back_files_paths_and_index(
    repo: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    second = repo / "src/b/Old.c"
    second.parent.mkdir()
    second.write_text("void Old(void);\n")
    git("add", "src/b/Old.c", root=repo)
    before = snapshot(repo)
    run_git = Context.git
    moves = 0

    def fail_second_move(self: Context, *args: str, **kwargs: object) -> str:
        nonlocal moves
        if args[0] == "mv" and "-n" not in args and "--dry-run" not in args:
            moves += 1
            if moves == 2:
                run_git(self, *args, **kwargs)
                raise subprocess.CalledProcessError(
                    128, ["git", *args], stderr="injected move failure"
                )
        return run_git(self, *args, **kwargs)

    monkeypatch.setattr(Context, "git", fail_second_move)
    with pytest.raises(
        (SymbolError, subprocess.CalledProcessError), match="injected move failure|128"
    ):
        main(repo, ["rename", "Old", "New"])
    assert moves == 2
    assert snapshot(repo) == before
    assert not (repo / ".git/index.lock").exists()


def test_an_untracked_old_reference_outside_scope_fails_without_changes(
    repo: Path,
) -> None:
    (repo / "include/left.h").write_text("void Old(void);\n")
    before = snapshot(repo)
    with pytest.raises(SymbolError, match="Old.*include/left.h"):
        main(repo, ["rename", "Old", "New"])
    assert snapshot(repo) == before


def test_success_and_case_only_rename_keep_the_output(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert main(repo, ["rename", "Old", "old"]) == 0
    assert capsys.readouterr().out == "renamed Old -> old in 4 files\n"
    assert (repo / "src/a/old.c").exists()
    assert not (repo / "src/a/Old.c").exists()
    assert all(b"Old" not in content for content in snapshot(repo)[0].values())
    assert "src/a/old.c" in git("ls-files", root=repo)


def test_address_renames_keep_provenance_and_other_images(repo: Path) -> None:
    for name, content in snapshot(repo)[0].items():
        (repo / name).write_bytes(content.replace(b"Old", b"func_80000000"))
    (repo / "src/a/Old.c").rename(repo / "src/a/func_80000000.c")
    put_symbols(repo, '["exe/a"]\n')
    unrelated = repo / "src/other/func_80000000.c"
    unrelated.parent.mkdir()
    unrelated.write_text("MATCH void func_80000000(void) {}\n")
    git("add", ".", root=repo)
    assert (
        main(
            repo,
            [
                "rename",
                "func_80000000",
                "New",
                "--image",
                "exe/a",
                "--scope",
                "src/a",
                "include",
                "config",
                "--source",
                "test purpose",
            ],
        )
        == 0
    )
    assert "/* func_80000000 */" in (repo / "src/a/New.c").read_text()
    assert "/* func_80000000 */" in (repo / "include/a.h").read_text()
    assert "func_80000000" in unrelated.read_text()


def test_an_address_rename_keeps_the_row_type_and_size(repo: Path) -> None:
    for name, content in snapshot(repo)[0].items():
        (repo / name).write_bytes(content.replace(b"Old", b"D_80000000"))
    (repo / "src/a/Old.c").rename(repo / "src/a/D_80000000.c")
    put_symbols(
        repo,
        '["exe/a"]\nD_80000000 = { addr = 0x80000000, type = "u16", size = 0x10, source = "was" }\n',
    )
    git("add", ".", root=repo)
    argv = [
        "rename",
        "D_80000000",
        "New",
        "--image",
        "exe/a",
        "--scope",
        "src/a",
        "include",
        "config",
        "--source",
        "now",
    ]
    assert main(repo, argv) == 0
    (row,) = tomllib.loads((repo / "config/symbols/exe+a.toml").read_text())[
        "exe/a"
    ].items()
    assert row == (
        "New",
        {"addr": 0x80000000, "type": "u16", "size": 0x10, "source": "now"},
    )


LAYOUT = """sha1: 0
segments:
  - name: main
    type: code
    start: 0x0
    vram: 0x80000000
    align: 4
    subsegments:
"""


def set_files(root: Path, files: dict[str, str | None]) -> None:
    """Replace fixture files; ``None`` deletes one, and the result is staged."""
    for name, text in files.items():
        path = root / name
        if text is None:
            path.unlink(missing_ok=True)
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text)
    git("add", "-A", root=root)


def test_a_rename_renames_the_layout_rows_and_moves_the_unit(repo: Path) -> None:
    set_files(
        repo,
        {
            "config/exe/a/splat.yaml": LAYOUT
            + "      - [0x0, c, Old]\n      - [0x10, .rodata, Old]\n"
        },
    )
    assert main(repo, ["rename", "Old", "New"]) == 0
    assert (repo / "src/a/New.c").is_file()
    assert not (repo / "src/a/Old.c").exists()
    text = (repo / "config/exe/a/splat.yaml").read_text()
    assert "[0x0, c, New]" in text
    assert "[0x10, .rodata, New]" in text


def test_a_layout_row_outside_the_scope_is_refused(repo: Path) -> None:
    set_files(repo, {"config/exe/a/splat.yaml": LAYOUT + "      - [0x0, c, Old]\n"})
    before = snapshot(repo)
    with pytest.raises(SymbolError, match="names Old; add its folder to --scope"):
        main(repo, ["rename", "Old", "New", "--scope", "src/a", "include"])
    assert snapshot(repo) == before


def test_a_local_rename_keeps_the_other_image(repo: Path) -> None:
    (repo / "src/b").mkdir()
    (repo / "src/b/Old.c").write_text("MATCH void Old(void) {}\n")
    (repo / "config/exe/b").mkdir(parents=True)
    (repo / "config/exe/b/splat.yaml").write_text("- [0x0, c, Old]\n")
    put_symbols(
        repo,
        '["exe/a"]\nOld = { addr = 0x80000000, type = "func" }\n'
        '\n["exe/b"]\nOld = { addr = 0x80010000, type = "func" }\n',
    )
    git("add", "-A", root=repo)
    assert main(repo, ["rename", "Old", "New", "--image", "exe/a", "--local"]) == 0
    assert (repo / "src/a/New.c").is_file()
    assert not (repo / "src/a/Old.c").exists()
    assert (repo / "src/b/Old.c").read_text() == "MATCH void Old(void) {}\n"
    assert "[0x0, c, New]" in (repo / "config/exe/a/splat.yaml").read_text()
    assert "[0x0, c, Old]" in (repo / "config/exe/b/splat.yaml").read_text()
    assert set(
        tomllib.loads((repo / "config/symbols/exe+a.toml").read_text())["exe/a"]
    ) == {"New"}
    assert set(
        tomllib.loads((repo / "config/symbols/exe+b.toml").read_text())["exe/b"]
    ) == {"Old"}


def test_an_address_name_clashes_inside_its_image(repo: Path) -> None:
    set_files(
        repo,
        {
            "config/exe/a/splat.yaml": LAYOUT + "      - [0x0, c, Old]\n",
            "src/a/other.c": "void func_80000000(void);\n",
        },
    )
    before = snapshot(repo)
    with pytest.raises(SymbolError, match="already occurs"):
        main(repo, ["rename", "Old", "func_80000000", "--image", "exe/a"])
    assert snapshot(repo) == before
