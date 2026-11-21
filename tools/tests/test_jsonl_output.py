"""The tools that print rows for another program write JSON Lines with --jsonl."""

from __future__ import annotations

import json

import dups
import worklist


def test_worklist_jsonl_names_the_columns(monkeypatch, capsys):
    monkeypatch.setattr(
        worklist,
        "rank",
        lambda image, route: [worklist.Row("a@0x1", 4, "plain", "m2c draft", "hint")],
    )
    assert worklist.main(["--jsonl"]) == 0
    row = json.loads(capsys.readouterr().out)
    assert row == {
        "function": "a@0x1",
        "words": 4,
        "route": "plain",
        "how": "m2c draft",
        "hint": "hint",
    }
    assert list(row) == ["function", "words", "route", "how", "hint"]


def test_dups_jsonl_writes_numbers_and_the_table_stays(capsys):
    header = ["#target", "template", "similarity", "diff_count"]
    rows = [
        {
            "target": "a@0x1",
            "template": "b@0x2",
            "similarity": 0.91234,
            "diff_count": 0,
        }
    ]
    dups.emit(header, rows, jsonl=True)
    assert json.loads(capsys.readouterr().out) == {
        "target": "a@0x1",
        "template": "b@0x2",
        "similarity": 0.91234,
        "diff_count": 0,
    }
    dups.emit(header, rows, formats={"similarity": lambda value: f"{value:.3f}"})
    assert capsys.readouterr().out.splitlines() == [
        "#target\ttemplate\tsimilarity\tdiff_count",
        "a@0x1\tb@0x2\t0.912\t0",
    ]
