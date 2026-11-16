"""try_variants swaps a variant into the definition the build compiles."""

from __future__ import annotations

import try_variants

DRAFT = (
    "#ifdef NON_MATCHING\n"
    "NON_MATCHING void func_80100000(void) {\n"
    "    old();\n"
    "}\n"
    "#else\n"
    "INCLUDE_ASM(func_80100000);\n"
    "#endif\n"
)


def _apply(source: str, name: str, text: str) -> str:
    start, end = try_variants.function_span(source, name)
    return source[:start] + text + source[end:]


def test_a_variant_replaces_the_draft_not_the_include_asm_line() -> None:
    result = _apply(
        DRAFT, "func_80100000", "NON_MATCHING void func_80100000(void) {}\n"
    )
    assert "old();" not in result
    assert "INCLUDE_ASM(func_80100000);" in result


def test_a_variant_replaces_the_include_asm_line_without_a_definition() -> None:
    result = _apply(
        "INCLUDE_ASM(func_80100000);\n", "func_80100000", "void f(void) {}\n"
    )
    assert result == "void f(void) {}\n"
