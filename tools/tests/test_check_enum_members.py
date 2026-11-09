from __future__ import annotations

from check_enum_members import find_members

KIND = "typedef enum Kind { K_A, K_B } Kind;\n"


def test_a_typedef_enum_member_fails() -> None:
    text = KIND + "typedef struct S {\n    s32 a;\n    Kind kind;\n} S;\n"
    assert find_members({"a.h": text}) == [("a.h", 4)]


def test_a_tagged_enum_member_in_a_nested_union_fails() -> None:
    text = KIND + "struct S {\n    union {\n        enum Kind k;\n    } in;\n};\n"
    assert find_members({"a.h": text}) == [("a.h", 4)]


def test_integers_comments_and_plain_enums_pass() -> None:
    text = KIND + "struct S {\n    u8 kind; /* Kind kind; */\n};\nKind g_Kind;\n"
    assert find_members({"a.h": text}) == []
