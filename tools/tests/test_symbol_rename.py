from __future__ import annotations

import subprocess
import tomllib
from pathlib import Path

import pytest

import symbol


@pytest.fixture
def repo(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> Path:
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    files = {
        "config/symbols.toml": '["exe/a"]\nOld = { addr = 0x80000000, type = "func" }\n',
        "config/exe/a/splat.yaml": "- [0x0, c, Old]\n",
        "src/a/Old.c": "MATCH void Old(void) {}\n",
        "include/a.h": "void Old(void);\n",
    }
    for name, text in files.items():
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    subprocess.run(["git", "-C", str(tmp_path), "add", "."], check=True)
    monkeypatch.setattr(symbol, "ROOT", tmp_path)
    monkeypatch.setattr(symbol, "SYMBOLS", tmp_path / "config/symbols.toml")
    return tmp_path


def snapshot(root: Path) -> tuple[dict[str, bytes], bytes]:
    files = {
        p.relative_to(root).as_posix(): p.read_bytes()
        for folder in ("src", "include", "config")
        for p in (root / folder).rglob("*")
        if p.is_file()
    }
    return files, (root / ".git/index").read_bytes()


@pytest.mark.parametrize("failure", ["destination", "index-lock"])
def test_preflight_failure_leaves_files_and_index_unchanged(
    repo: Path, failure: str
) -> None:
    if failure == "destination":
        (repo / "src/a/New.c").write_text("untracked destination\n")
    else:
        (repo / ".git/index.lock").write_text("another process\n")
    before = snapshot(repo)
    with pytest.raises((SystemExit, subprocess.CalledProcessError, OSError)):
        symbol.main(["rename", "Old", "New"])
    assert snapshot(repo) == before
    if failure == "index-lock":
        assert (repo / ".git/index.lock").read_text() == "another process\n"


def test_a_failed_second_move_rolls_back_files_paths_and_index(
    repo: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    second = repo / "src/b/Old.c"
    second.parent.mkdir()
    second.write_text("void Old(void);\n")
    symbol.git("add", "src/b/Old.c")
    before = snapshot(repo)
    run_git = symbol.git
    moves = 0

    def fail_second_move(*args: str, **kwargs: object) -> str:
        nonlocal moves
        if args[0] == "mv" and "-n" not in args and "--dry-run" not in args:
            moves += 1
            if moves == 2:
                run_git(*args, **kwargs)
                raise subprocess.CalledProcessError(
                    128, ["git", *args], stderr="injected move failure"
                )
        return run_git(*args, **kwargs)

    monkeypatch.setattr(symbol, "git", fail_second_move)
    with pytest.raises(
        (SystemExit, subprocess.CalledProcessError), match="injected move failure|128"
    ):
        symbol.main(["rename", "Old", "New"])
    assert moves == 2
    assert snapshot(repo) == before
    assert not (repo / ".git/index.lock").exists()


def test_an_untracked_old_reference_outside_scope_fails_without_changes(
    repo: Path,
) -> None:
    (repo / "include/left.h").write_text("void Old(void);\n")
    before = snapshot(repo)
    with pytest.raises(SystemExit, match="Old.*include/left.h"):
        symbol.main(["rename", "Old", "New"])
    assert snapshot(repo) == before


def test_success_and_case_only_rename_keep_the_output(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert symbol.main(["rename", "Old", "old"]) == 0
    assert capsys.readouterr().out == "renamed Old -> old in 4 files\n"
    assert (repo / "src/a/old.c").exists()
    assert not (repo / "src/a/Old.c").exists()
    assert all(b"Old" not in content for content in snapshot(repo)[0].values())
    assert "src/a/old.c" in symbol.git("ls-files")


def test_an_untracked_unit_is_rejected_before_any_edit(repo: Path) -> None:
    symbol.git("rm", "--cached", "--", "src/a/Old.c")
    before = snapshot(repo)
    with pytest.raises(SystemExit, match="Old.*src/a/Old.c"):
        symbol.main(["rename", "Old", "New"])
    assert snapshot(repo) == before


def test_a_write_failure_restores_existing_unstaged_edits(
    repo: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    path = repo / "include/a.h"
    path.write_text("/* local edit */\nvoid Old(void);\n")
    before = snapshot(repo)
    write = Path.write_text

    def fail_write(self: Path, contents: str, *args: object, **kwargs: object) -> int:
        if self == path:
            raise OSError("injected write failure")
        return write(self, contents, *args, **kwargs)

    monkeypatch.setattr(Path, "write_text", fail_write)
    with pytest.raises(SystemExit, match="injected write failure"):
        symbol.main(["rename", "Old", "New"])
    assert snapshot(repo) == before


def test_postflight_checks_the_written_files_and_rolls_back(
    repo: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    path = repo / "include/a.h"
    before = snapshot(repo)
    write = Path.write_text

    def leave_old_reference(
        self: Path, contents: str, *args: object, **kwargs: object
    ) -> int:
        if self == path:
            contents = "void Old(void);\n"
        return write(self, contents, *args, **kwargs)

    monkeypatch.setattr(Path, "write_text", leave_old_reference)
    with pytest.raises(SystemExit, match="Old.*include/a.h"):
        symbol.main(["rename", "Old", "New"])
    assert snapshot(repo) == before


def test_address_renames_keep_provenance_and_other_images(repo: Path) -> None:
    for name, content in snapshot(repo)[0].items():
        (repo / name).write_bytes(content.replace(b"Old", b"func_80000000"))
    (repo / "src/a/Old.c").rename(repo / "src/a/func_80000000.c")
    (repo / "config/symbols.toml").write_text('["exe/a"]\n')
    unrelated = repo / "src/other/func_80000000.c"
    unrelated.parent.mkdir()
    unrelated.write_text("MATCH void func_80000000(void) {}\n")
    symbol.git("add", ".")
    assert (
        symbol.main(
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
            ]
        )
        == 0
    )
    assert "/* func_80000000 */" in (repo / "src/a/New.c").read_text()
    assert "/* func_80000000 */" in (repo / "include/a.h").read_text()
    assert "func_80000000" in unrelated.read_text()


def test_renaming_an_address_name_drops_its_alias_row(repo: Path) -> None:
    for name, content in snapshot(repo)[0].items():
        (repo / name).write_bytes(content.replace(b"Old", b"func_80000000"))
    (repo / "src/a/Old.c").rename(repo / "src/a/func_80000000.c")
    (repo / "config/symbols.toml").write_text(
        '["exe/a"]\nfunc_80000000 = { addr = 0x80000000, type = "func", alias = true }\n'
    )
    symbol.git("add", ".")
    assert (
        symbol.main(
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
            ]
        )
        == 0
    )
    assert tomllib.loads((repo / "config/symbols.toml").read_text()) == {
        "exe/a": {
            "New": {
                "addr": 0x80000000,
                "type": "func",
                "source": "test purpose",
            }
        }
    }


def test_add_refuses_an_image_that_is_not_a_target(repo: Path) -> None:
    table = repo / "config/symbols.toml"
    before = table.read_bytes()
    assert symbol.main(["add", "exe/b", "New", "0x80000010", "--source", "x"]) == 2
    assert table.read_bytes() == before


def test_index_publication_failure_rolls_back_the_whole_rename(
    repo: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    before = snapshot(repo)
    replace = symbol.os.replace

    def fail_publication(source: Path, target: Path) -> None:
        if target == repo / ".git/index":
            raise OSError("injected index failure")
        replace(source, target)

    monkeypatch.setattr(symbol.os, "replace", fail_publication)
    with pytest.raises(SystemExit, match="injected index failure"):
        symbol.main(["rename", "Old", "New"])
    assert snapshot(repo) == before
    assert not (repo / ".git/index.lock").exists()


def test_success_preserves_a_subsequent_process_index_lock(
    repo: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    replace = symbol.os.replace
    lock = repo / ".git/index.lock"

    def publish_then_lock(source: Path, target: Path) -> None:
        replace(source, target)
        if target == repo / ".git/index":
            lock.write_text("another process\n")

    monkeypatch.setattr(symbol.os, "replace", publish_then_lock)
    assert symbol.main(["rename", "Old", "New"]) == 0
    assert lock.read_text() == "another process\n"
