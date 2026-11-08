from __future__ import annotations

import shutil
from pathlib import Path

import pytest

from check_kept import (
    Entities,
    Snapshot,
    compare,
    defines_in,
    is_weak,
    parse_layouts,
    run_clang,
)

LAYOUT = """
*** Dumping AST Record Layout
         0 | struct Actor
         0 |   u8 flags
         2 |   s16 hp
         4 |   struct Vec pos
         4 |     s16 x
         6 |     s16 y
         8 |   struct Work * work
           | [sizeof=12, align=4]
"""


def snapshot(
    entities: Entities, uses: dict[str, set[str]], defines=None, names=None, rows=None
):
    return Snapshot(entities, uses, defines or {}, names or {}, rows or {})


def test_layouts_keep_nested_members_with_absolute_offsets() -> None:
    layouts, sizes = parse_layouts(LAYOUT)
    members = [(m.offset, m.path, m.ctype, m.size) for m in layouts["struct Actor"]]
    assert members == [
        (0, "flags", "u8", 2),
        (2, "hp", "s16", 2),
        (4, "pos", "struct Vec", 4),
        (4, "pos.x", "s16", 2),
        (6, "pos.y", "s16", 2),
        (8, "work", "struct Work *", 4),
    ]
    assert sizes["struct Actor"] == 12


def test_weak_types_are_integers_and_their_arrays() -> None:
    assert is_weak("u8[4]") and is_weak("unsigned int")
    assert not is_weak("struct Work *") and not is_weak("Actor") and not is_weak("u8 *")


def test_guards_are_not_defines_and_values_are_normalized() -> None:
    text = "#ifndef A_H\n#define A_H\n#define COUNT 0x10 /* ten */\n#define TWICE(x) \\\n    ((x) * 2)\n"
    assert defines_in(text) == {"COUNT": "16", "TWICE": "(x)((x)*2)"}


def records(layout: str) -> Entities:
    found = Entities()
    found.records["Actor"].append(parse_layouts(layout)[0]["struct Actor"])
    return found


def test_a_renamed_member_passes_and_an_unknown_or_raw_one_fails() -> None:
    before = records(LAYOUT)
    renamed = records(LAYOUT.replace("s16 hp", "s16 health"))
    unknown = records(LAYOUT.replace("s16 hp", "s16 unk_02"))
    raw = records(LAYOUT.replace("struct Work * work", "u32 work"))
    uses = {"a.h": {"Actor"}}
    assert compare(snapshot(before, uses), snapshot(renamed, uses), set()) == []
    assert compare(snapshot(before, uses), snapshot(unknown, uses), set()) == [
        "member Actor.hp at +0x2: became unk_02"
    ]
    assert compare(snapshot(before, uses), snapshot(raw, uses), set()) == [
        "member Actor.work at +0x8: struct Work * became u32"
    ]


def test_a_function_renamed_at_its_address_passes_and_one_set_back_to_func_fails() -> (
    None
):
    old = Entities(functions={"Battle_Run": "a.c"})
    place = {"Battle_Run": {("battle", 0x801D0000)}}
    before = snapshot(old, {"a.c": {"Battle_Run"}}, names=place)
    renamed = snapshot(
        Entities(),
        {"a.c": {"Battle_RunTurn"}},
        rows={("battle", 0x801D0000): "Battle_RunTurn"},
    )
    reverted = snapshot(
        Entities(),
        {"a.c": {"func_801D0000"}},
        rows={("battle", 0x801D0000): "func_801D0000"},
    )
    assert compare(before, renamed, set()) == []
    assert compare(before, reverted, set()) == [
        "function Battle_Run has only a default name now"
    ]


def test_a_define_passes_when_its_users_use_one_of_the_same_value() -> None:
    old = Entities(defines={"PARTY_RECORD_COUNT": "8"})
    before = snapshot(
        old, {"a.h": {"PARTY_RECORD_COUNT"}, "b.c": {"PARTY_RECORD_COUNT"}}
    )
    merged = snapshot(
        Entities(),
        {"a.h": set(), "b.c": {"CHARACTER_COUNT"}},
        defines={"CHARACTER_COUNT": "8"},
    )
    inlined = snapshot(Entities(), {"a.h": set(), "b.c": set()})
    assert compare(before, merged, set()) == []
    assert compare(before, inlined, set()) == ["#define PARTY_RECORD_COUNT is gone"]
    assert compare(before, inlined, {"PARTY_RECORD_COUNT"}) == []


def test_enumerator_values_never_change() -> None:
    before = snapshot(
        Entities(enums={"STATE_IDLE": ("State", 0)}), {"a.h": {"STATE_IDLE"}}
    )
    after = snapshot(
        Entities(enums={"STATE_IDLE": ("State", 1)}), {"a.h": {"STATE_IDLE"}}
    )
    assert compare(before, after, set()) == [
        "enumerator STATE_IDLE changed value 0 -> 1"
    ]


@pytest.mark.skipif(not shutil.which("clang"), reason="needs clang")
def test_clang_reads_records_typedefs_enums_and_inlines(tmp_path: Path) -> None:
    (tmp_path / "include").mkdir()
    (tmp_path / "include" / "a.h").write_text(
        "typedef struct { short x; struct { char a; } inner; } Vec;\n"
        "enum Mode { MODE_IDLE, MODE_RUN = 4, MODE_STOP };\n"
        "static inline int Vec_Twice(int v) { return v * 2; }\n"
        "extern Vec g_Origin;\n"
    )
    found = run_clang(tmp_path, "include/a.h", {"include/a.h"})
    assert [m.path for m in found.records["Vec"][0]] == ["x", "inner", "inner.a"]
    assert found.enums == {
        "MODE_IDLE": ("Mode", 0),
        "MODE_RUN": ("Mode", 4),
        "MODE_STOP": ("Mode", 5),
    }
    assert set(found.inlines) == {"Vec_Twice"}
    assert set(found.globals) == {"g_Origin"}
