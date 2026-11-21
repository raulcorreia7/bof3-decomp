from __future__ import annotations

from check_enum_members import find_members

KIND = "typedef enum Kind { K_A, K_B } Kind;\n"


def test_a_typedef_enum_member_fails() -> None:
    text = KIND + "typedef struct S {\n    s32 a;\n    Kind kind;\n} S;\n"
    assert find_members({"a.h": text}) == [("a.h", 4)]
