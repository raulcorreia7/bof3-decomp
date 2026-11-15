import pytest

import draft_swap

SOURCE = """\
#include "battle_03.h"

/* func_801DAAE4 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_BuildTurnOrder(void) {
    return;
}
#else
INCLUDE_ASM(Battle_BuildTurnOrder);
#endif

#ifdef NON_MATCHING
NON_MATCHING void Battle_Other(void) {
    return;
}
#else
INCLUDE_ASM(Battle_Other);
#endif
"""

BODY = "NON_MATCHING void Battle_BuildTurnOrder(void) {\n    return 1;\n}\n"


def test_the_new_body_replaces_the_block_and_leaves_the_rest() -> None:
    text, old = draft_swap.swap(SOURCE, "Battle_BuildTurnOrder", BODY)
    assert text == SOURCE.replace(
        "NON_MATCHING void Battle_BuildTurnOrder(void) {\n    return;\n}", BODY.strip()
    )
    assert old == "NON_MATCHING void Battle_BuildTurnOrder(void) {\n    return;\n}"


def test_a_bare_include_asm_gets_the_block_around_it() -> None:
    text, old = draft_swap.swap("INCLUDE_ASM(Battle_Foo);\n", "Battle_Foo", BODY)
    assert (
        text == f"#ifdef NON_MATCHING\n{BODY}#else\nINCLUDE_ASM(Battle_Foo);\n#endif\n"
    )
    assert old is None


def test_a_function_without_an_include_asm_is_refused() -> None:
    with pytest.raises(SystemExit, match="has no INCLUDE_ASM"):
        draft_swap.swap("MATCH void Battle_Foo(void) {\n}\n", "Battle_Foo", BODY)
