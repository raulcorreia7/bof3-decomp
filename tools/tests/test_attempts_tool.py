"""`tools/attempts.py add` appends a row in the spelling of the last row."""

from __future__ import annotations

import json
from pathlib import Path

import attempts


def row(
    function: str, tried: str, first_diff: str = "", score: object = None, compact=False
) -> str:
    data = {
        "function": function,
        "tried": tried,
        "first_diff": first_diff,
        "score": score,
    }
    if compact:
        return json.dumps(data, separators=(",", ":"))
    return json.dumps(data)


def file(tmp_path: Path, *lines: str, name: str = "attempts.jsonl") -> Path:
    path = tmp_path / name
    path.write_text("".join(line + "\n" for line in lines), encoding="utf-8")
    return path


def rows(path: Path) -> list[dict]:
    return [json.loads(line) for line in path.read_text(encoding="utf-8").splitlines()]


def test_a_row_is_appended(tmp_path) -> None:
    path = file(tmp_path, row("b@0x00000002", "one"), row("a@0x00000001", "two"))

    assert attempts.add(path, "a@0x00000001", "late", "", 52.1) == 3
    assert [(r["function"], r["tried"]) for r in rows(path)][2] == (
        "a@0x00000001",
        "late",
    )


def test_the_row_keeps_the_spelling_of_the_last_row(tmp_path) -> None:
    compact = file(tmp_path, row("a@0x00000001", "one", compact=True), name="c.jsonl")
    attempts.add(compact, "a@0x00000001", "two", "", None)
    assert compact.read_text(encoding="utf-8").splitlines()[1] == row(
        "a@0x00000001", "two", compact=True
    )

    spaced = file(tmp_path, row("a@0x00000001", "one"), name="s.jsonl")
    attempts.add(spaced, "a@0x00000001", "two", "", None)
    assert spaced.read_text(encoding="utf-8").splitlines()[1] == row(
        "a@0x00000001", "two"
    )
