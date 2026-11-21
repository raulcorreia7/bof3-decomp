from __future__ import annotations

from pathlib import Path

from permuter_import import function_name


def test_an_assembly_unit_gives_the_macro_argument(tmp_path: Path) -> None:
    source = tmp_path / "a.c"
    source.write_text("#if BOF3_USE_ASM\nMATCH INCLUDE_ASM(func_801642F4);\n#endif\n")
    assert function_name(source) == "func_801642F4"
