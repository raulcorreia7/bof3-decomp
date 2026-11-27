"""quality counts readability debt per file and gates the files a change touches."""

from __future__ import annotations

import quality

BODY = "MATCH void {name}(void) {{\n    a = 1;\n    b = 2;\n}}\n"


def row(text: str, path: str = "src/a/x.c") -> dict[str, int]:
    return quality.scan({path: text})[path]


def test_address_names_placeholders_and_raw_casts_are_counted_in_bodies() -> None:
    text = (
        "MATCH void func_801EEC10(void) {\n"
        "    *(u8 *)D_801EF000 = unk_1C;\n"
        "    x = ((u8*)p)[1];\n"
        "    y = (u16 *)p + 0x10;\n"
        "    z = p->flag;\n"
        "}\n"
        "MATCH void Named(void) { x = 1; }\n"
        "INCLUDE_ASM(func_801EEC20);\n"
    )
    found = row(text)
    assert (found["funcs"], found["addr"]) == (2, 1)
    assert found["names"] == 2
    assert found["casts"] == 3


def test_a_bare_do_while_zero_block_counts_and_a_loop_or_macro_use_does_not() -> None:
    text = (
        "MATCH void A(void) {\n"
        "    do {\n        x = 1;\n    } while (0);\n"
        "    do { y = 2; } while (i < n);\n"
        "    NAMED_BLOCK(x);\n"
        "}\n"
    )
    assert row(text)["blocks"] == 1
    assert (
        row(
            "MATCH void B(void) { FAKE_ORDER_LOCK(x = 1); FAKE_ORDER_LOCK_BEGIN x = 2; FAKE_ORDER_LOCK_END; }"
        )["blocks"]
        == 2
    )


def test_a_nest_counts_its_depth_and_a_steering_block_is_harmful() -> None:
    nest = "do {\n do {\n do {\n do { x = 1; } while (0);\n } while (0);\n } while (0);\n } while (0);\n"
    found = row(f"MATCH void A(void) {{\n do {{\n {nest} }} while (i < n);\n}}\n")
    assert (found["blocks"], found["harmful"]) == (4, 4)
    noted = "/* FAKE: the loop weight lifts x over y in the allocator. */\n do { x = 1; } while (0);\n"
    assert row(f"MATCH void B(void) {{\n {noted}}}\n")["harmful"] == 1
    plain = "/* FAKE: statement boundary keeps the retail store order. */\n do { x = 1; } while (0);\n"
    assert row(f"MATCH void C(void) {{\n {plain}}}\n")["harmful"] == 0
    old = {"x.c": quality.scan({"x.c": f"MATCH void A(void) {{\n{nest}}}\n"})["x.c"]}
    same = {
        "x.c": quality.scan({"x.c": f"MATCH void A(void) {{\n{nest} y = 2;\n}}\n"})[
            "x.c"
        ]
    }
    added = {
        "x.c": quality.scan(
            {
                "x.c": f"MATCH void A(void) {{\n{nest} do {{ do {{ y = 2; }} while (0); }} while (0);\n}}\n"
            }
        )["x.c"]
    }
    assert quality.worse(old, same, {"x.c"}) == []
    assert quality.worse(old, added, {"x.c"}) == ["x.c: harmful 4 -> 6"]


def test_pasted_needs_two_images_and_a_shared_name() -> None:
    files = {
        "src/o/a/1/x.c": BODY.format(name="func_801EEE3C"),
        "src/o/a/2/x.c": BODY.format(name="func_801EEE3C"),
        "src/o/a/3/x.c": BODY.format(name="func_801EEE40"),
        "src/o/a/4/x.c": "MATCH void F(void) { a = 1; }\n",
        "src/o/a/5/x.c": "MATCH void F(void) { a = 1; }\n",
    }
    rows = quality.scan(files)
    assert [rows[p]["pasted"] for p in sorted(rows)] == [1, 1, 0, 0, 0]
    assert [rows[p]["twins"] for p in sorted(rows)] == [0, 0, 1, 0, 0]


def test_worse_flags_only_touched_files_and_gated_metrics() -> None:
    old = {"a.c": {"casts": 1, "names": 0, "pasted": 0, "harmful": 0}}
    new = {
        "a.c": {"casts": 2, "names": 5, "pasted": 0, "harmful": 0},
        "b.c": {"casts": 9, "names": 0, "pasted": 0, "harmful": 0},
        "c.c": {"casts": 0, "names": 0, "pasted": 1, "harmful": 0},
    }
    assert quality.worse(old, new, {"a.c"}) == ["a.c: casts 1 -> 2"]
    assert quality.worse(old, new, {"c.c"}) == ["c.c: pasted 0 -> 1"]
    assert quality.worse(old, new, {"a.c", "b.c"}, ("names",)) == ["a.c: names 0 -> 5"]
    assert quality.worse(old, old, {"a.c"}) == []


def test_a_function_that_gains_placeholders_fails_the_names_ratchet() -> None:
    old = {"src/a/x.c": "MATCH void F(void) { a = D_801EF000; }\n"}
    new = {"src/a/x.c": "MATCH void F(void) { a = D_801EF000; b = unk_1C; }\n"}
    assert quality.ratchet(old, new, {"src/a/x.c"}) == ["F: names 1 -> 2"]
    assert quality.ratchet(new, old, {"src/a/x.c"}) == []


def test_a_moved_body_that_gains_placeholders_fails_the_names_ratchet() -> None:
    old = {"src/a/x.c": "MATCH void F(void) { a = D_801EF000; }\n", "src/a/F.h": ""}
    new = {
        "src/a/x.c": "",
        "src/a/F.h": "MATCH void F(void) { a = D_801EF000; b = unk_1C; }\n",
    }
    assert quality.ratchet(old, new, {"src/a/x.c", "src/a/F.h"}) == ["F: names 1 -> 2"]


def test_a_new_match_is_exempt_from_addr_and_names() -> None:
    old = {"src/a/x.c": "MATCH void F(void) { a = 1; }\nINCLUDE_ASM(func_801EEC20);\n"}
    new = {
        "src/a/x.c": "MATCH void F(void) { a = 1; }\n"
        "MATCH void func_801EEC20(void) { b = D_801EF000; c = 2; }\n"
    }
    assert quality.ratchet(old, new, {"src/a/x.c"}) == []


def test_a_named_body_renamed_back_to_an_address_fails_the_addr_ratchet() -> None:
    old = {"src/a/x.c": "MATCH void Actor_Wake(void) { a = 1; b = 2; }\n"}
    new = {"src/a/x.c": "MATCH void func_801EEC20(void) { a = 1; b = 2; }\n"}
    assert quality.ratchet(old, new, {"src/a/x.c"}) == [
        "func_801EEC20: addr named -> func_<ADDR>"
    ]
    assert quality.ratchet(old, new, set()) == []


def test_a_draft_body_does_not_count() -> None:
    draft = (
        "#ifdef NON_MATCHING\n"
        "NON_MATCHING void func_801EEC10(void) {\n"
        "    *(u8 *)D_801EF000 = unk_1C;\n"
        "}\n"
        "#else\nINCLUDE_ASM(func_801EEC10);\n#endif\n"
    )
    found = row(draft)
    assert (found["funcs"], found["addr"], found["names"], found["casts"]) == (
        0,
        0,
        0,
        0,
    )
