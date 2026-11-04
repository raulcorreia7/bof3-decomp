"""m2c_sweep turns m2c output into bodies and keeps the results file sorted."""

from __future__ import annotations

from pathlib import Path

import m2c_sweep

DRAFT = """extern u8 D_801EC2E4;
? func_80196718(PartyBattler *);                    /* extern */
s8 func_8019651C(PartyBattler *, s32);     /* extern */

void func_801EEEDC(void) {
    if (D_801EC2E4 == 0) {
        func_8019651C(0, 1);
    }
}
"""


def test_to_body_prefixes_match_and_turns_declarations_into_decl_lines() -> None:
    body = m2c_sweep.to_body(DRAFT, "func_801EEEDC")
    assert body is not None
    lines = body.splitlines()
    assert lines[:2] == [
        "@decl extern u8 D_801EC2E4;",
        "@decl s8 func_8019651C(PartyBattler *, s32);",
    ]
    assert "MATCH void func_801EEEDC(void) {" in lines


def test_to_body_drops_a_draft_with_an_unknown_type_or_no_definition() -> None:
    assert m2c_sweep.to_body("void other(void) {\n}\n", "func_1") is None
    unknown = "void func_1(void) {\n    ? x;\n}\n"
    assert m2c_sweep.to_body(unknown, "func_1") is None
    assert m2c_sweep.to_body("void func_1(void) {\n    x = a ? b : c;\n}\n", "func_1")


def test_residual_lists_the_unmatched_fewest_differing_first(tmp_path: Path) -> None:
    results = tmp_path / m2c_sweep.RESULTS
    results.parent.mkdir(parents=True)
    results.write_text(
        "a@0x1\t12\tdefault\nb@0x2\tEXACT\tdefault\nc@0x3\t3\tno-andor\nd@0x4\t\t\n",
        encoding="utf-8",
    )
    out = tmp_path / "residual.tsv"
    assert m2c_sweep.residual(tmp_path, out) == 3
    assert out.read_text().splitlines() == [
        "function\tbest_diff",
        "c@0x3\t3",
        "a@0x1\t12",
        "d@0x4\tnone",
    ]


CONTEXT = """extern u8* g_SpadWork;
typedef struct PartyBattler { u8 flags_00; } PartyBattler;
"""


def test_spad_type_takes_the_context_cast_then_the_image_family() -> None:
    cast = (
        CONTEXT
        + "void f(void) { ((Actor*)g_SpadWork)->x = 0; ((Actor*)g_SpadWork)->y = 0; }\n"
    )
    cast += "typedef struct Actor { int x; } Actor;\n"
    assert m2c_sweep.spad_type(cast, "emi/world01/area001/13") == "Actor"
    assert m2c_sweep.spad_type(CONTEXT, "emi/bmagic/magic001/00") == "PartyBattler"
    assert m2c_sweep.spad_type(CONTEXT, "emi/scenario/scena01/00") is None
    assert (
        m2c_sweep.spad_type("extern u8* g_SpadWork;\n", "emi/bmagic/magic001/00")
        is None
    )


def test_typed_cell_and_asm_name_the_cell_symbol() -> None:
    text = m2c_sweep.typed_cell(CONTEXT, "emi/bmagic/magic001/00")
    assert text.rstrip().endswith("extern PartyBattler *g_SpadView;")
    assert m2c_sweep.typed_cell(CONTEXT, "emi/scenario/x") == CONTEXT
    asm = "lui $a0, (0x1F800044 >> 16)\nlw $a0, (0x1F800044 & 0xFFFF)($a0)\n"
    assert m2c_sweep.typed_asm(asm) == (
        "lui $a0, %hi(g_SpadView)\nlw $a0, %lo(g_SpadView)($a0)\n"
    )


def test_wrap_cell_spells_the_view_unless_the_unit_defines_it(tmp_path: Path) -> None:
    func = m2c_sweep.Func("i", "f", 0, 0, (), "", "ASM", "src/u.c")
    (tmp_path / "src").mkdir()
    (tmp_path / "src/u.c").write_text('#include "u.h"\n', encoding="utf-8")
    (tmp_path / "src/u.h").write_text("int x;\n", encoding="utf-8")
    body = "@decl int a;\nMATCH void f(void) {\n    g_SpadView->flags_00 = 0;\n}\n"
    out = m2c_sweep.wrap_cell(body, "PartyBattler", tmp_path, func)
    assert "((PartyBattler *)g_SpadWork)->flags_00 = 0;" in out
    (tmp_path / "src/u.h").write_text(
        "#define g_SpadWork ((T*)g_SpadWork)\n", encoding="utf-8"
    )
    out = m2c_sweep.wrap_cell(body, "PartyBattler", tmp_path, func)
    assert "    g_SpadWork->flags_00 = 0;" in out
