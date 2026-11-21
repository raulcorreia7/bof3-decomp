from __future__ import annotations

from pathlib import Path

from permuter_import import function_name


def test_a_matched_definition_gives_its_name(tmp_path: Path) -> None:
    source = tmp_path / "a.c"
    source.write_text("MATCH void Scene_Clear(void) {\n}\n")
    assert function_name(source) == "Scene_Clear"


def test_an_assembly_unit_gives_the_macro_argument(tmp_path: Path) -> None:
    source = tmp_path / "a.c"
    source.write_text("#if BOF3_USE_ASM\nMATCH INCLUDE_ASM(func_801642F4);\n#endif\n")
    assert function_name(source) == "func_801642F4"


def test_a_draft_wins_over_a_matched_definition(tmp_path: Path) -> None:
    source = tmp_path / "a.c"
    source.write_text("MATCH void a(void) {\n}\nNON_MATCHING void b(void) {\n}\n")
    assert function_name(source) == "b"
