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


def test_comments_hide_names_and_notes_count_whole_file() -> None:
    text = "/* FAKE: pin. */\nMATCH void F(void) {\n    /* D_801EF000 *(u8 *)p */\n    MATCH_FAKE_PIN(x);\n}\n"
    found = row(text)
    assert (found["names"], found["casts"], found["harmful"], found["notes"]) == (
        0,
        0,
        1,
        1,
    )


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


def test_a_statement_macro_body_is_not_a_paste() -> None:
    body = (
        "MATCH void Name(void) {\n    u8 i;\n    u8 j;\n\n    SHOW_PARTY(0, i, j);\n}\n"
    )
    files = {"src/o/a/1/x.c": body, "src/o/a/2/x.c": body}
    rows = quality.scan(files).values()
    assert sum(r["pasted"] + r["twins"] for r in rows) == 0


def test_a_header_body_is_not_a_paste() -> None:
    files = {
        "src/o/a/Name.h": BODY.format(name="Name"),
        "src/o/a/1/x.c": BODY.format(name="Name"),
        "src/o/a/2/x.c": '#include "o/a/Name.h"\n',
    }
    assert sum(r["pasted"] for r in quality.scan(files).values()) == 0


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


def test_queue_ranks_the_highest_score_first() -> None:
    low = dict.fromkeys((*quality.METRICS, "funcs"), 0) | {"casts": 1}
    high = dict.fromkeys((*quality.METRICS, "funcs"), 0) | {"pasted": 1}
    lines = quality.table({"low.c": low, "high.c": high}, 10, "file").splitlines()
    assert lines[1].endswith("high.c") and lines[2].endswith("low.c")


def test_a_body_moved_between_touched_files_nets_to_zero() -> None:
    old = {"a.c": {"casts": 2}, "b.h": {"casts": 0}}
    new = {"b.h": {"casts": 2}}
    assert quality.worse(old, new, {"a.c", "b.h"}, ("casts",)) == []
    new = {"b.h": {"casts": 3}}
    assert quality.worse(old, new, {"a.c", "b.h"}, ("casts",)) == ["b.h: casts 0 -> 3"]


def test_a_function_that_gains_placeholders_fails_the_names_ratchet() -> None:
    old = {"src/a/x.c": "MATCH void F(void) { a = D_801EF000; }\n"}
    new = {"src/a/x.c": "MATCH void F(void) { a = D_801EF000; b = unk_1C; }\n"}
    assert quality.ratchet(old, new, {"src/a/x.c"}) == ["F: names 1 -> 2"]
    assert quality.ratchet(new, old, {"src/a/x.c"}) == []


def test_one_address_name_in_two_images_is_two_functions() -> None:
    old = {
        "src/a/x.c": "MATCH void func_801EF27C(void) { a = D_801EF000; }\n",
        "src/b/x.c": "INCLUDE_ASM(func_801EF27C);\n",
    }
    new = {
        "src/a/x.c": old["src/a/x.c"],
        "src/b/x.c": "MATCH void func_801EF27C(void) { a = D_801EF000; b = unk_1C; }\n",
    }
    assert quality.ratchet(old, new, {"src/a/x.c", "src/b/x.c"}) == []


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
