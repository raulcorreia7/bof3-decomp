from __future__ import annotations

from pathlib import Path

import pytest

import check_markers
from check_markers import (
    attempt_problems,
    check_hand_units,
    check_text,
    draft_ref,
    has_hand_asm,
)


def problems(text: str) -> list[str]:
    return [v.problem for v in check_text(text)]


def test_a_marked_definition_passes() -> None:
    assert problems("MATCH void f(void) {\n}\n") == []


def test_an_unmarked_definition_fails() -> None:
    assert problems("void f(void) {\n}\n") == [
        "no marker; a definition needs exactly one"
    ]


def test_a_wrapped_signature_is_one_definition() -> None:
    wrapped = "{marker}s32 f(s32 first,\n       s32 second) {{\n    return first;\n}}\n"
    assert problems(wrapped.format(marker="MATCH ")) == []
    assert problems(wrapped.format(marker="")) == [
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


def test_initializers_and_types_are_not_definitions() -> None:
    text = (
        "typedef struct { int a; } Pair;\n"
        "static Callback table[] = { f, g };\n"
        "enum { A, B };\n"
        "extern void p(void), q(void);\n"
    )
    assert problems(text) == []


def test_a_static_inline_header_helper_is_exempt() -> None:
    assert problems("static inline void helper(void) {\n}\n") == []


def test_a_draft_needs_its_ifdef_and_a_match_may_not_sit_in_it() -> None:
    draft = "#ifdef NON_MATCHING\nNON_MATCHING void f(void) {\n}\n#else\nINCLUDE_ASM(f);\n#endif\n"
    assert problems(draft) == []
    assert problems("NON_MATCHING void f(void) {\n}\n") == [
        "NON_MATCHING outside `#ifdef NON_MATCHING`"
    ]
    assert problems(draft.replace("NON_MATCHING void", "MATCH void")) == [
        "MATCH inside `#ifdef NON_MATCHING`"
    ]


def test_each_branch_of_an_if_is_checked() -> None:
    text = "#if A\nMATCH void f(void) {\n}\n#else\nvoid f(void) {\n}\n#endif\n"
    assert problems(text) == ["no marker; a definition needs exactly one"]


def test_a_marker_on_an_include_asm_line_fails() -> None:
    assert problems("MATCH INCLUDE_ASM(f);\n") == [
        "marker on something that is not a function definition"
    ]
    assert problems("INCLUDE_ASM(f);\n") == []


def test_an_old_style_definition_is_one_definition() -> None:
    kr = "{marker}s32 f(a, b)\nu8 a;\ns32 b;\n{{\n    return b;\n}}\n"
    assert problems(kr.format(marker="MATCH ")) == []
    assert problems(kr.format(marker="")) == [
        "no marker; a definition needs exactly one"
    ]


@pytest.mark.parametrize("line", [3, 5])
def test_the_report_names_the_line_of_the_definition(line: int) -> None:
    text = "\n" * (line - 1) + "void f(void) {\n}\n"
    assert [v.line for v in check_text(text)] == [line]


DRAFT = (
    "#ifdef NON_MATCHING\nHAND_ASM void f(void) {\n}\n#else\nINCLUDE_ASM(f);\n#endif\n"
)


def test_hand_asm_sits_under_the_draft_switch() -> None:
    assert problems(DRAFT) == []
    assert problems("HAND_ASM void f(void) {\n}\n") == [
        "HAND_ASM outside `#ifdef NON_MATCHING`"
    ]


def test_every_hand_file_needs_hand_asm_and_nothing_else_may_have_it() -> None:
    hand = ["asm/exe/x/hand/f.s"]
    assert check_hand_units(hand, {"a.c": DRAFT}) == []
    assert [
        v.problem for v in check_hand_units(hand, {"a.c": "INCLUDE_ASM(f);\n"})
    ] == ["hand-written assembly without HAND_ASM"]
    other = DRAFT.replace("f(", "g(")
    assert [v.problem for v in check_hand_units(hand, {"a.c": DRAFT + other})] == [
        "HAND_ASM on a function with no asm/*/hand/ file"
    ]


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


def test_a_hand_asm_file_may_land_its_switch(tmp_path) -> None:
    hand, draft = tmp_path / "h.c", tmp_path / "d.c"
    hand.write_text(DRAFT)
    draft.write_text(DRAFT.replace("HAND_ASM", "NON_MATCHING"))
    assert has_hand_asm(str(hand))
    assert not has_hand_asm(str(draft))


def _tree(tmp_path, attempts: str):
    (tmp_path / "config/emi/bmagic/magic058/03").mkdir(parents=True)
    (tmp_path / "config/emi/bmagic/magic058/03/splat.yaml").write_text("")
    (tmp_path / "config/symbols.toml").write_text(
        '["emi/bmagic/magic058/03"]\nNamed = { addr = 0x801EFDD4, type = "func" }\n'
    )
    (tmp_path / "config/attempts.jsonl").write_text(attempts)
    return tmp_path


def test_a_draft_names_its_function_by_image_and_address(tmp_path) -> None:
    root = _tree(tmp_path, "")
    path = "src/overlays/bmagic/magic058/03/a.c"
    want = "emi/bmagic/magic058/03@0x801EFDD4"
    assert draft_ref(path, "NON_MATCHING s32 func_801efdd4(void) {\n", root) == want
    assert draft_ref(path, "NON_MATCHING s32 Named(void) {\n", root) == want
    assert draft_ref(path, "NON_MATCHING s32 Other(void) {\n", root) is None


def _land(monkeypatch, tmp_path, attempts: str, capsys) -> int:
    root = _tree(tmp_path, attempts)
    src = root / "src/overlays/bmagic/magic058/03/a.c"
    src.parent.mkdir(parents=True)
    src.write_text(
        DRAFT.replace("HAND_ASM", "NON_MATCHING").replace("f(", "func_801EFDD4(")
    )
    added = [(str(src.relative_to(root)), 1, "#ifdef NON_MATCHING")]
    monkeypatch.chdir(root)
    monkeypatch.setattr(check_markers, "ROOT", root)
    monkeypatch.setattr(check_markers, "added_lines", lambda ref: added)
    return check_markers.main(["--diff", "REF"])


def test_a_draft_lands_with_an_attempts_object(monkeypatch, tmp_path, capsys) -> None:
    row = '{"function": "emi/bmagic/magic058/03@0x801EFDD4", "tried": "t", "first_diff": "d", "score": null}\n'
    assert _land(monkeypatch, tmp_path, row, capsys) == 0


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


def test_attempt_rows_any_spacing_pass(tmp_path) -> None:
    root = _attempt_rows(
        tmp_path,
        '{"function":"a@0x1","tried":"t","first_diff":"d","score":null}',
        '{"function": "b@0x2", "tried": "t", "first_diff": "", "score": "2 rows"}',
        '{"function":  "c@0x3",  "tried": "t", "first_diff": "", "score": null}',
    )
    assert attempt_problems(root) == []


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


def test_a_row_out_of_function_order_names_the_first_line(tmp_path) -> None:
    root = _attempt_rows(
        tmp_path,
        '{"function":"a@0x1","tried":"t","first_diff":"d","score":null}',
        '{"function":"c@0x3","tried":"t","first_diff":"","score":null}',
        '{"function":"b@0x2","tried":"t","first_diff":"","score":null}',
        '{"function":"a@0x1","tried":"u","first_diff":"","score":null}',
    )
    path = root / "config/attempts.jsonl"
    assert attempt_problems(root) == [
        f"{path}:3: b@0x2 sorts before c@0x3; keep the rows in function order "
        "with tools/attempts.py sort"
    ]


def test_a_malformed_attempts_row_fails_the_diff_check(
    monkeypatch, tmp_path, capsys
) -> None:
    row = '{"function": "emi/bmagic/magic058/03@0x801EFDD4", "tried": "t", "result": "MATCH"}\n'
    assert _land(monkeypatch, tmp_path, row, capsys) == 1
    assert ":1: keys ['function', 'tried', 'result']" in capsys.readouterr().err
