"""A push compares the merge base, so a branch that is merely behind main still passes."""

from __future__ import annotations

import os
import shutil
import subprocess
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
STUB = "#!/bin/sh\nexit 0\n"
SUBSYSTEMS = (
    "# Subsystems\n\n"
    "<!-- quality:begin (tools/quality.py --markdown) -->\n"
    "<!-- quality:end -->\n"
)
TYPED = "typedef struct Unit { int x; } Unit;\nextern Unit *g_Thing;\n"
WEAK = "extern int g_Thing;\n"


def git(repo: Path, *args: str) -> None:
    subprocess.run(
        ["git", "-c", "user.name=t", "-c", "user.email=t@t", *args],
        cwd=repo,
        check=True,
        capture_output=True,
    )


def make_repo(tmp_path: Path, base: str) -> Path:
    """A repo with the real tools; HEAD is a branch that is behind main."""
    repo = tmp_path / "repo"
    (repo / "bin").mkdir(parents=True)
    shutil.copytree(
        TOOLS,
        repo / "tools",
        ignore=shutil.ignore_patterns("tests", "__pycache__"),
    )
    shutil.copytree(REPO / "bin" / "internal", repo / "bin" / "internal")
    for path in ("config", "src", "include", "docs", "build/meson"):
        (repo / path).mkdir(parents=True)
    (repo / "config/address_names.txt").write_text("")
    (repo / "config/symbols.toml").write_text("")
    (repo / "docs/subsystems.md").write_text(SUBSYSTEMS)
    (repo / "include/thing.h").write_text(base)
    stubs = tmp_path / "stubs"
    stubs.mkdir()
    for name in ("ninja", "meson"):
        (stubs / name).write_text(STUB)
        (stubs / name).chmod(0o755)
    git(repo, "init", "-q", "-b", "main")
    git(repo, "add", "-A")
    git(repo, "commit", "-qm", "base")
    git(repo, "checkout", "-qb", "work")
    return repo


def env(tmp_path: Path) -> dict[str, str]:
    return {
        **os.environ,
        "PATH": f"{tmp_path / 'stubs'}:{os.environ['PATH']}",
        "CLANG_FORMAT": "true",
        "RUFF": "true",
        "DPRINT": "true",
    }


def pre_push(repo: Path, tmp_path: Path) -> subprocess.CompletedProcess:
    return subprocess.run(
        ["sh", "tools/pre_push.sh", "main"],
        cwd=repo,
        env=env(tmp_path),
        capture_output=True,
        text=True,
        check=False,
    )


def typeloss(repo: Path, *revs: str) -> subprocess.CompletedProcess:
    return subprocess.run(
        ["python3", "tools/typeloss.py", *revs],
        cwd=repo,
        capture_output=True,
        text=True,
        check=False,
    )


def test_a_branch_behind_a_typed_main_passes(tmp_path: Path) -> None:
    repo = make_repo(tmp_path, WEAK)
    git(repo, "checkout", "-q", "main")
    (repo / "include/thing.h").write_text(TYPED)
    git(repo, "commit", "-qam", "type the extern")
    git(repo, "checkout", "-q", "work")

    # The tip comparison is the false failure the fix removes.
    assert typeloss(repo, "main", "HEAD").returncode == 1

    result = pre_push(repo, tmp_path)
    assert result.returncode == 0, result.stdout + result.stderr
    assert "ok    typeloss" in result.stdout
    assert (repo / "build/pre-push/typeloss.rc").read_text().strip() == "0"


def test_a_branch_that_really_drops_a_type_still_fails(tmp_path: Path) -> None:
    repo = make_repo(tmp_path, TYPED)
    (repo / "include/thing.h").write_text(
        "typedef struct Unit { int x; } Unit;\nextern int g_Thing;\n"
    )
    git(repo, "commit", "-qam", "drop the type")

    result = pre_push(repo, tmp_path)
    assert "FAIL  typeloss" in result.stdout
    assert (repo / "build/pre-push/typeloss.rc").read_text().strip() == "1"
