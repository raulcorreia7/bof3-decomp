"""The tools that print rows for another program write JSON Lines with --jsonl."""

from __future__ import annotations

import json

import chunks
import classify
import dups
import m2c_sweep
import quality
import sigs
import symbol
import template_diff
import template_try
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


def test_sigs_jsonl_keeps_the_line_number_a_number(monkeypatch, capsys):
    problem = sigs.decls.Problem("argc_mismatch", "f", "src/a.c", 12, "2 against 1")
    monkeypatch.setattr(sigs, "load_tree", lambda: None)
    monkeypatch.setattr(sigs.decls, "problems", lambda tree: [problem])
    assert sigs.main(["scan", "--jsonl"]) == 0
    assert json.loads(capsys.readouterr().out) == {
        "kind": "argc_mismatch",
        "name": "f",
        "file": "src/a.c",
        "line": 12,
        "detail": "2 against 1",
    }


def test_quality_queue_rows_keep_the_table_order_and_numbers():
    rows = {
        "high.c": dict.fromkeys((*quality.METRICS, "funcs"), 0) | {"casts": 2},
        "low.c": dict.fromkeys((*quality.METRICS, "funcs"), 0) | {"casts": 1},
        "none.c": dict.fromkeys((*quality.METRICS, "funcs"), 0),
    }
    found = quality.queue_rows(rows, 10)
    assert [row["file"] for row in found] == ["high.c", "low.c"]
    assert found[0]["score"] == quality.score(rows["high.c"])
    assert isinstance(found[0]["casts"], int)
    assert list(found[0]) == ["file", "score", "funcs", *quality.METRICS]


def test_symbol_refs_jsonl_names_the_columns(monkeypatch, capsys):
    monkeypatch.setattr(
        symbol,
        "ref_rows",
        lambda dirs: [
            {"count": 7, "name": "func_80100000", "unit": "src/a/func_80100000.c"}
        ],
    )
    assert symbol.main(["refs", "--jsonl"]) == 0
    assert json.loads(capsys.readouterr().out) == {
        "count": 7,
        "name": "func_80100000",
        "unit": "src/a/func_80100000.c",
    }


def test_a_jsonl_rows_file_names_the_pair(tmp_path):
    path = tmp_path / "rows.jsonl"
    path.write_text(
        '{"target": "a@0x1", "template": "b@0x2"}\n',
        encoding="utf-8",
    )
    assert template_try.read_rows(path) == [("a@0x1", "b@0x2")]


def test_a_tsv_rows_file_still_names_the_pair(tmp_path):
    path = tmp_path / "rows.tsv"
    path.write_text("a@0x1\tb@0x2\textra\n", encoding="utf-8")
    assert template_try.read_rows(path) == [("a@0x1", "b@0x2")]


def test_diff_rows_name_the_three_kinds():
    rows = template_diff.align_rows(
        ["addiu a0,a0,1", "lw v0,0(a0)"],
        ["addiu a0,a0,2", "lw v0,0(a0)", "nop"],
    )
    assert [row["kind"] for row in rows] == ["same_opcode", "target_only"]
    assert rows[0]["template_offset"] == 0
    assert rows[0]["target_offset"] == 0
    assert rows[0]["target"] == "addiu a0,a0,2"
    assert rows[1]["template_offset"] is None
    assert rows[1]["target_offset"] == 8


def test_chunk_rows_are_jsonl(tmp_path):
    path = tmp_path / "chunks.jsonl"
    rows = [
        {
            "weight": 6,
            "insns": 3,
            "funcs": 3,
            "images": 2,
            "lifted": 1,
            "members": ["a:F+0x0[ASM]", "b:G+0x4[C]"],
        }
    ]
    chunks.write_rows(str(path), rows)
    assert [json.loads(line) for line in path.read_text().splitlines()] == rows


def test_classify_rows_counts_the_kinds():
    rows = [
        {
            "weight": 6,
            "insns": 3,
            "funcs": 2,
            "images": 2,
            "members": ["a:F+0x0[ASM]", "b:G+0x4[C]"],
        },
        {
            "weight": 3,
            "insns": 3,
            "funcs": 2,
            "images": 2,
            "members": ["a:H+0x0[ASM]", "b:I+0x4[C]"],
        },
    ]
    kinds = {
        ("a", "F"): "asm",
        ("b", "G"): "pasted",
        ("a", "H"): "asm",
        ("b", "I"): "shared",
    }
    kept = classify.classify_rows(
        rows, lambda image, name, status: kinds[(image, name)]
    )
    assert kept == [
        {
            "weight": 6,
            "insns": 3,
            "funcs": 2,
            "images": 2,
            "asm": 1,
            "pasted": 1,
            "shared": 0,
            "members": ["a:F+0x0[ASM]", "b:G+0x4[C]"],
        }
    ]


def test_results_jsonl_names_the_swept_functions(tmp_path):
    folder = tmp_path / "build/m2c_sweep"
    folder.mkdir(parents=True)
    (folder / "results.jsonl").write_text(
        '{"target": "a@0x1", "status": "BEST", "differing": 4, "variant": "default"}\n',
        encoding="utf-8",
    )
    assert m2c_sweep.read_results(tmp_path) == {"a@0x1"}
