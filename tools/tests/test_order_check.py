"""Ordering checks and the moves --fix is allowed to make."""

from __future__ import annotations

from order_check import (
    check_asserts,
    check_data_file,
    check_enums,
    check_externs,
    check_prototypes,
    check_symbols,
)


def apply(text: str, check) -> tuple[str, list]:
    lines = text.splitlines(keepends=True)
    hits = check("a.h", lines)
    out: list[str] = []
    pos = 0
    for edit in sorted((h for h in hits if h.fixable), key=lambda h: h.start):
        out.extend(lines[pos : edit.start])
        out.extend(edit.new)
        pos = edit.end
    out.extend(lines[pos:])
    return "".join(out), hits


def test_assert_offsets_precede_size() -> None:
    text = (
        "typedef struct S { u8 a; u8 b; } S;\n"
        "ASSERT_SIZE(S, 0x02);\n"
        "ASSERT_OFFSET(S, b, 0x01);\n"
        "ASSERT_OFFSET(S, a, 0x00);\n"
    )
    fixed, hits = apply(text, check_asserts)
    assert len(hits) == 1 and hits[0].fixable
    assert fixed.endswith(
        "ASSERT_OFFSET(S, a, 0x00);\nASSERT_OFFSET(S, b, 0x01);\nASSERT_SIZE(S, 0x02);\n"
    )
    assert apply(fixed, check_asserts)[1] == []


def test_assert_offset_expression_is_manual() -> None:
    text = "ASSERT_OFFSET(S, b, BASE + 0x04);\nASSERT_OFFSET(S, a, 0x00);\n"
    fixed, hits = apply(text, check_asserts)
    assert fixed == text
    assert len(hits) == 1 and not hits[0].fixable


def test_prototypes_sort_with_their_address_comments() -> None:
    text = (
        "/* func_801F2C04 */\nvoid Area_A(void);\n"
        "void func_801F2C30(void);\n"
        "/* func_801F2C14 */\nvoid Area_B(void);\n"
    )
    fixed, hits = apply(text, check_prototypes)
    assert len(hits) == 1 and hits[0].fixable
    assert fixed == (
        "/* func_801F2C04 */\nvoid Area_A(void);\n"
        "/* func_801F2C14 */\nvoid Area_B(void);\n"
        "void func_801F2C30(void);\n"
    )
    assert apply(fixed, check_prototypes)[1] == []


def test_unkeyed_prototype_anchors_the_runs() -> None:
    text = (
        "void func_801F2C30(void);\n"
        "void func_801F2C14(void);\n"
        "void Named(void);\n"
        "void func_801F2C40(void);\n"
        "void func_801F2C04(void);\n"
    )
    fixed, hits = apply(text, check_prototypes)
    assert len(hits) == 1 and hits[0].fixable
    assert fixed == (
        "void func_801F2C14(void);\n"
        "void func_801F2C30(void);\n"
        "void Named(void);\n"
        "void func_801F2C04(void);\n"
        "void func_801F2C40(void);\n"
    )
    assert apply(fixed, check_prototypes)[1] == []


def test_externs_sort_with_descriptive_comments() -> None:
    text = (
        "extern u8 D_801F2C30[];\n"
        "/* The staged y coordinate. */\n"
        "extern s16 D_801F2C14;\n"
    )
    fixed, hits = apply(text, check_externs)
    assert len(hits) == 1 and hits[0].fixable
    assert fixed == (
        "/* The staged y coordinate. */\n"
        "extern s16 D_801F2C14;\n"
        "extern u8 D_801F2C30[];\n"
    )
    assert apply(fixed, check_externs)[1] == []


def test_id_flag_enum_values_sort() -> None:
    text = (
        "typedef enum ItemIds {\n    ITEM_ID_B = 2,\n    ITEM_ID_A = 1,\n} ItemIds;\n"
    )
    fixed, hits = apply(text, check_enums)
    assert len(hits) == 1 and hits[0].fixable
    assert "ITEM_ID_A = 1," in fixed
    assert fixed.index("ITEM_ID_A") < fixed.index("ITEM_ID_B")
    assert apply(fixed, check_enums)[1] == []


def test_implicit_enum_values_are_manual() -> None:
    text = "enum Steps {\n    STEP_B,\n    STEP_A,\n};\n"
    fixed, hits = apply(text, check_enums)
    assert fixed == text and hits == []


def test_symbols_rows_sort_per_table_with_comments() -> None:
    text = (
        '["emi/a"]\n'
        'B = { addr = 0x801F2C30, type = "func" }\n'
        "# A's source.\n"
        'A = { addr = 0x801F2C04, type = "func" }\n'
        '["emi/b"]\n'
        "Z = { addr = 0x801D0C04 }\n"
        "Y = { addr = 0x801D0C00 }\n"
    )
    fixed, hits = apply(text, check_symbols)
    assert len(hits) == 2 and all(h.fixable for h in hits)
    assert fixed == (
        '["emi/a"]\n'
        "# A's source.\n"
        'A = { addr = 0x801F2C04, type = "func" }\n'
        'B = { addr = 0x801F2C30, type = "func" }\n'
        '["emi/b"]\n'
        "Y = { addr = 0x801D0C00 }\n"
        "Z = { addr = 0x801D0C04 }\n"
    )
    assert apply(fixed, check_symbols)[1] == []


def test_data_files_report_only() -> None:
    text = "u8 D_801F2C30[] = {1};\nMATCH void func_801F2C04(void) {}\n"
    fixed, hits = apply(text, check_data_file)
    assert fixed == text
    assert len(hits) == 1 and not hits[0].fixable
    assert "data/functions" in hits[0].render()
