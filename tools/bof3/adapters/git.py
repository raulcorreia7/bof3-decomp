"""Ask Git about a revision range; every tool's Git call goes through here."""

from __future__ import annotations

import subprocess
from pathlib import Path


def _run(args: tuple[str, ...], root: Path | None, check: bool, text: bool = True):
    return subprocess.run(
        ["git", *args], cwd=root, capture_output=True, text=text, check=check
    )


def git(*args: str, root: Path | None = None, check: bool = True) -> str:
    """Return the standard output of ``git args``; with ``check`` off a failed command gives ``""``."""
    return _run(args, root, check).stdout


def ok(*args: str, root: Path | None = None) -> bool:
    """Return whether ``git args`` exits 0."""
    return _run(args, root, False, text=False).returncode == 0


def merge_base(
    ref: str,
    head: str = "HEAD",
    *,
    root: Path | None = None,
    fallback: str | None = None,
) -> str:
    """Return the commit ``head`` branched from ``ref`` at; ``fallback`` replaces a failure."""
    if fallback is None:
        return git("merge-base", ref, head, root=root).strip()
    return git("merge-base", ref, head, root=root, check=False).strip() or fallback


def changed_files(*args: str, root: Path | None = None) -> list[str]:
    """Return the paths ``git diff --name-only args`` lists."""
    return git("diff", "--name-only", *args, root=root, check=False).split()


def ls_files(*paths: str, root: Path | None = None) -> list[str]:
    """Return the tracked files under ``paths``."""
    return git("ls-files", *paths, root=root).split()
