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
