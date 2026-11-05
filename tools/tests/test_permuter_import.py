from __future__ import annotations

from pathlib import Path

from permuter_import import ROOT, function_name, settings_toml


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


def test_the_settings_objdump_is_the_repo_binutils() -> None:
    text = settings_toml("cc", "as", "prelude.inc")
    assert (
        f'objdump_command = "{ROOT}/bin/internal/binutils/objdump -drz -m mips:4300"'
        in text
    )
