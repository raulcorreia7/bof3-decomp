"""Read and write the attempts rows: ``config/attempts.jsonl`` and ``config/attempts/*.jsonl``."""

from __future__ import annotations

from pathlib import Path

from bof3.attempts import parse_lines

PATH = "config/attempts.jsonl"
DIR = "config/attempts"  # one file per branch, so two pull requests never append to the same file


def files(path: Path) -> list[Path]:
    """`path`, then the per-branch files beside the main table."""
    extra = (
        sorted((path.parent / "attempts").glob("*.jsonl"))
        if path.name == "attempts.jsonl"
        else []
    )
    return [path, *extra]


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8") if path.exists() else ""


def read_lines(path: Path) -> list[str]:
    return [line for file in files(path) for line in parse_lines(read_text(file))]


def write_lines(path: Path, lines: list[str]) -> None:
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
