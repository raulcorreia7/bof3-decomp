"""`tools/attempts.py` puts a row at its place and keeps each function's order."""

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


def test_a_row_for_a_known_function_goes_after_its_last_row(tmp_path) -> None:
    path = file(
        tmp_path,
        row("a@0x00000001", "one"),
        row("a@0x00000001", "two"),
        row("b@0x00000002", "three"),
    )

    assert attempts.add(path, "a@0x00000001", "late", "", None) == 3
    assert [r["tried"] for r in rows(path)] == ["one", "two", "late", "three"]


def test_a_new_function_goes_to_its_sorted_place(tmp_path) -> None:
    path = file(tmp_path, row("a@0x00000001", "one"), row("c@0x00000003", "three"))

    assert attempts.add(path, "b@0x00000002", "two", "", 52.1) == 2
    assert [(r["function"], r["score"]) for r in rows(path)] == [
        ("a@0x00000001", None),
        ("b@0x00000002", 52.1),
        ("c@0x00000003", None),
    ]


def test_a_function_that_sorts_last_appends(tmp_path) -> None:
    path = file(tmp_path, row("a@0x00000001", "one"))

    assert attempts.add(path, "z@0x0000000A", "late", "", None) == 2
    assert [r["function"] for r in rows(path)] == ["a@0x00000001", "z@0x0000000A"]


def test_the_row_keeps_the_spelling_of_the_row_it_follows(tmp_path) -> None:
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


def test_score_keeps_a_number_null_and_text() -> None:
    assert attempts.score("84.24") == 84.24
    assert attempts.score("134") == 134
    assert attempts.score("null") is None
    assert attempts.score("6 opcode hunks") == "6 opcode hunks"


def test_sort_keeps_each_function_rows_in_their_order(tmp_path) -> None:
    path = file(
        tmp_path,
        row("b@0x00000002", "one"),
        row("a@0x00000001", "two"),
        row("b@0x00000002", "three"),
    )

    attempts.sort(path)
    assert [(r["function"], r["tried"]) for r in rows(path)] == [
        ("a@0x00000001", "two"),
        ("b@0x00000002", "one"),
        ("b@0x00000002", "three"),
    ]


def test_sort_drops_a_row_that_repeats_an_earlier_one(tmp_path) -> None:
    path = file(
        tmp_path,
        row("b@0x00000002", "one"),
        row("a@0x00000001", "two"),
        row("b@0x00000002", "one", compact=True),
        row("b@0x00000002", "three"),
    )

    attempts.sort(path)
    assert [(r["function"], r["tried"]) for r in rows(path)] == [
        ("a@0x00000001", "two"),
        ("b@0x00000002", "one"),
        ("b@0x00000002", "three"),
    ]


def test_a_function_that_is_not_a_target_is_refused(tmp_path) -> None:
    path = file(tmp_path, row("a@0x00000001", "one"))
    args = ["add", "--function", "nope", "--tried", "x", "--path", str(path)]
    assert attempts.main(args) == 2
    assert len(rows(path)) == 1


def test_main_adds_the_row_it_is_given(tmp_path) -> None:
    path = file(tmp_path, row("b@0x00000002", "one"))
    args = [
        "add",
        "--function",
        "a@0x00000001",
        "--tried",
        "t",
        "--first-diff",
        "d",
        "--score",
        "7",
        "--path",
        str(path),
    ]

    assert attempts.main(args) == 0
    assert rows(path) == [
        {"function": "a@0x00000001", "tried": "t", "first_diff": "d", "score": 7},
        {"function": "b@0x00000002", "tried": "one", "first_diff": "", "score": None},
    ]
