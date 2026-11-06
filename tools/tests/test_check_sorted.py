"""check_sorted fails on an enum or a run of #define constants that is not ascending by value."""

from __future__ import annotations

import check_sorted


def test_sorted_enum_and_defines_pass() -> None:
    text = "enum A { A_ONE = 1, A_ALIAS = 1, A_TWO,\n A_FOUR = 4 };\n#define X 1\n#define Y 0x10\n"
    assert check_sorted.check_text(text) == []


def test_descending_enum_member_is_reported_with_its_line() -> None:
    text = "typedef enum A {\n    A_TWO = 2,\n    A_ONE = 1,\n} A;\n"
    assert check_sorted.check_text(text, "a.h") == ["a.h:3: enum member A_ONE sorts before A_TWO"]


def test_shifted_flags_and_define_runs_are_compared_by_value() -> None:
    assert check_sorted.check_text("enum F { F_B = 1 << 1, F_A = 1 << 0 };\n")
    assert check_sorted.check_text("#define B 2\n#define A 1\n")


def test_comment_or_blank_line_starts_a_new_define_run() -> None:
    assert check_sorted.check_text("#define B 2\n\n#define A 1\n") == []


def test_unevaluable_values_are_skipped() -> None:
    assert check_sorted.check_text("enum E { E_B = sizeof(int), E_A = 0 };\n") == []
