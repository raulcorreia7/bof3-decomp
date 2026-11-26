from __future__ import annotations

from pathlib import Path

from fixture import put_symbols

import check_markers
from check_markers import (
    attempt_problems,
    check_hand_units,
    check_text,
)


def problems(text: str) -> list[str]:
    return [v.problem for v in check_text(text)]


def test_an_unmarked_definition_fails() -> None:
    assert problems("void f(void) {\n}\n") == [
        "no marker; a definition needs exactly one"
    ]


def test_the_marker_must_come_first_and_only_once() -> None:
    assert problems("static MATCH void f(void) {\n}\n") == [
        "the marker must be the first token of the definition"
    ]
    assert problems("MATCH MATCH void f(void) {\n}\n") == [
        "2 markers; a definition needs exactly one"
    ]


def test_braces_in_comments_strings_and_macros_do_not_count() -> None:
    text = (
        "#define BODY { if (x) { y(); } }\n"
        "/* void ghost(void) { */\n"
        "MATCH void f(void) {\n    g(\"}\", '{');\n}\n"
    )
    assert problems(text) == []


def test_a_draft_needs_its_ifdef_and_a_match_may_not_sit_in_it() -> None:
    draft = "#ifdef NON_MATCHING\nNON_MATCHING void f(void) {\n}\n#else\nINCLUDE_ASM(f);\n#endif\n"
    assert problems(draft) == []
    assert problems("NON_MATCHING void f(void) {\n}\n") == [
        "NON_MATCHING outside `#ifdef NON_MATCHING`"
    ]
    assert problems(draft.replace("NON_MATCHING void", "MATCH void")) == [
        "MATCH inside a draft switch"
    ]


DRAFT = (
    "#if HAND_ASM_MODEL\nHAND_ASM void f(void) {\n}\n#else\nINCLUDE_ASM(f);\n#endif\n"
)


def test_every_hand_file_needs_hand_asm_and_nothing_else_may_have_it() -> None:
    hand = ["asm/exe/x/hand/f.s"]
    assert check_hand_units(hand, {"a.c": DRAFT}) == []
    assert [
        v.problem for v in check_hand_units(hand, {"a.c": "INCLUDE_ASM(f);\n"})
    ] == ["hand-written assembly without HAND_ASM"]
    assert problems(DRAFT.replace("#if HAND_ASM_MODEL", "#ifdef NON_MATCHING")) == [
        "HAND_ASM outside `#if HAND_ASM_MODEL`"
    ]
    other = DRAFT.replace("f(", "g(")
    assert [v.problem for v in check_hand_units(hand, {"a.c": DRAFT + other})] == [
        "HAND_ASM on a function with no asm/*/hand/ file"
    ]


def test_a_hand_file_answers_to_the_symbol_it_exports(tmp_path) -> None:
    hand = tmp_path / "asm/exe/x/hand/func_80001000.s"
    hand.parent.mkdir(parents=True)
    hand.write_text(".globl f\nf:\n")
    assert check_hand_units([str(hand)], {"a.c": DRAFT}) == []
    assert [
        v.problem for v in check_hand_units([str(hand)], {"a.c": "INCLUDE_ASM(f);\n"})
    ] == ["hand-written assembly without HAND_ASM"]


def test_attempt_notes_are_rejected() -> None:
    assert problems("/* blocker */\nINCLUDE_ASM(f);\n") == [
        "comment above INCLUDE_ASM; record attempts in config/attempts.jsonl"
    ]
    assert problems("/* First difference: register. */\nMATCH void f(void) {}\n") == [
        "attempt note belongs in config/attempts.jsonl"
    ]
    assert problems("/* nonmatching unmeasured: draft. */\n") == [
        "attempt note belongs in config/attempts.jsonl"
    ]
    assert problems('MATCH void f(void) { char *s = "First difference:"; }\n') == []


def _tree(tmp_path, attempts: str):
    (tmp_path / "config/emi/bmagic/magic058/03").mkdir(parents=True)
    (tmp_path / "config/emi/bmagic/magic058/03/splat.yaml").write_text("")
    put_symbols(
        tmp_path,
        '["emi/bmagic/magic058/03"]\nNamed = { addr = 0x801EFDD4, type = "func" }\n',
    )
    (tmp_path / "config/attempts.jsonl").write_text(attempts)
    return tmp_path


def _land(monkeypatch, tmp_path, attempts: str, capsys, other: str = "") -> int:
    root = _tree(tmp_path, attempts)
    src = root / "src/overlays/bmagic/magic058/03/a.c"
    src.parent.mkdir(parents=True)
    src.write_text(
        DRAFT.replace("#if HAND_ASM_MODEL", "#ifdef NON_MATCHING")
        .replace("HAND_ASM", "NON_MATCHING")
        .replace("f(", "func_801EFDD4(")
    )
    sources = [str(src.relative_to(root))]
    if other:
        (root / "src/b.c").write_text(other)
        sources.append("src/b.c")
    added = [(sources[0], 1, "#ifdef NON_MATCHING")]
    monkeypatch.chdir(root)
    monkeypatch.setattr(check_markers, "ROOT", root)
    monkeypatch.setattr(check_markers, "added_lines", lambda ref: added)
    monkeypatch.setattr(check_markers, "tracked_sources", lambda: sources)
    monkeypatch.setattr(check_markers, "tracked_hand_files", lambda: [])
    return check_markers.main(["--diff", "REF"])


ATTEMPT = (
    '{"function": "emi/bmagic/magic058/03@0x801EFDD4", "tried": "t", '
    '"first_diff": "d", "score": null}\n'
)


def test_the_diff_gate_fails_an_unmarked_definition_in_any_file(
    monkeypatch, tmp_path, capsys
) -> None:
    assert _land(monkeypatch, tmp_path, ATTEMPT, capsys, "void g(void) {\n}\n") == 1
    assert "src/b.c:1: g: no marker" in capsys.readouterr().err


def test_the_diff_gate_passes_a_marked_definition_in_any_file(
    monkeypatch, tmp_path, capsys
) -> None:
    assert (
        _land(monkeypatch, tmp_path, ATTEMPT, capsys, "MATCH void g(void) {\n}\n") == 0
    )


def test_a_draft_without_an_attempts_object_fails(
    monkeypatch, tmp_path, capsys
) -> None:
    assert _land(monkeypatch, tmp_path, "", capsys) == 1
    assert "emi/bmagic/magic058/03@0x801EFDD4" in capsys.readouterr().err


def _attempt_rows(tmp_path, *rows: str) -> Path:
    (tmp_path / "config").mkdir()
    (tmp_path / "config/attempts.jsonl").write_text(
        "".join(row + "\n" for row in rows), encoding="utf-8"
    )
    return tmp_path


def test_an_attempt_row_with_other_keys_or_order_names_its_line(tmp_path) -> None:
    root = _attempt_rows(
        tmp_path,
        '{"function":"a@0x1","tried":"t","first_diff":"d","score":null}',
        '{"function":"b@0x2","tried":"t","result":"MATCH"}',
        '{"function":"c@0x3","tried":"t","score":null,"first_diff":""}',
    )
    path = root / "config/attempts.jsonl"
    assert attempt_problems(root) == [
        f"{path}:2: keys ['function', 'tried', 'result'] instead of "
        "['function', 'tried', 'first_diff', 'score']",
        f"{path}:3: keys ['function', 'tried', 'score', 'first_diff'] instead of "
        "['function', 'tried', 'first_diff', 'score']",
    ]
