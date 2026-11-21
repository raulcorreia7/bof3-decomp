"""Read and write ``config/attempts.jsonl``."""

from __future__ import annotations

from pathlib import Path

from bof3.attempts import parse_lines

PATH = "config/attempts.jsonl"


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8") if path.exists() else ""


def read_lines(path: Path) -> list[str]:
    return parse_lines(read_text(path))


def write_lines(path: Path, lines: list[str]) -> None:
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")
