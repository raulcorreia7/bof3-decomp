"""worklist --jsonl keeps its columns."""

from __future__ import annotations

import json

import worklist


def test_worklist_jsonl_names_the_columns(monkeypatch, capsys):
    monkeypatch.setattr(
        worklist,
        "rank",
        lambda image: [worklist.Row("a@0x1", 4, "plain", "m2c draft", "hint")],
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
