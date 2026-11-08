from __future__ import annotations

import pytest

from check_markers import check_hand_units, check_text


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


DRAFT = "#ifdef NON_MATCHING\nHAND_ASM void f(void) {\n}\n#else\nINCLUDE_ASM(f);\n#endif\n"


def test_hand_asm_sits_under_the_draft_switch() -> None:
    assert problems(DRAFT) == []
    assert problems("HAND_ASM void f(void) {\n}\n") == [
        "HAND_ASM outside `#ifdef NON_MATCHING`"
    ]


def test_every_hand_file_needs_hand_asm_and_nothing_else_may_have_it() -> None:
    hand = ["asm/exe/x/hand/f.s"]
    assert check_hand_units(hand, {"a.c": DRAFT}) == []
    assert [v.problem for v in check_hand_units(hand, {"a.c": "INCLUDE_ASM(f);\n"})] == [
        "hand-written assembly without HAND_ASM"
    ]
    other = DRAFT.replace("f(", "g(")
    assert [v.problem for v in check_hand_units(hand, {"a.c": DRAFT + other})] == [
        "HAND_ASM on a function with no asm/*/hand/ file"
    ]
