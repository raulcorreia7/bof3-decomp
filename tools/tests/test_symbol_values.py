from __future__ import annotations

import json
import subprocess
from pathlib import Path
from types import SimpleNamespace

import pytest

import symbol

FILES = {
    "include/types.h": (
        "typedef unsigned char u8;\n"
        "typedef signed char s8;\n"
        "typedef unsigned short u16;\n"
        "typedef signed short s16;\n"
        "typedef unsigned int u32;\n"
        "typedef signed int s32;\n"
        "typedef int bool;\n"
        "#define true 1\n"
        "#define false 0\n"
        "#define BYTE_MASK 0xFF\n"
    ),
    "include/common/fixed.h": (
        "typedef unsigned short u16;\n"
        "typedef signed short s16;\n"
        "typedef signed int s32;\n"
        "typedef union Coord {\n"
        "    s32 fixed;\n"
        "    struct {\n"
        "        u16 fraction;\n"
        "        s16 integer;\n"
        "    } part;\n"
        "} Coord;\n"
    ),
    "include/game/thing.h": (
        '#include "types.h"\n'
        '#include "common/fixed.h"\n'
        "typedef enum ThingMode {\n"
        "    THING_MODE_IDLE = 0,\n"
        "    THING_MODE_RUN = 2,\n"
        "} ThingMode;\n"
        "typedef enum ThingFlags {\n"
        "    THING_FLAG_A = 1 << 0,\n"
        "} ThingFlags;\n"
        "typedef enum ItemId {\n"
        "    ITEM_HERB = 0x3A,\n"
        "    ITEM_OTHER = 0x3B,\n"
        "} ItemId;\n"
        "typedef enum SndId {\n"
        "    SND_A = 5,\n"
        "    SND_B = 6,\n"
        "} SndId;\n"
        "typedef struct Head {\n"
        "    u8 mode; /* ThingMode */\n"
        "    u8 step;\n"
        "} Head;\n"
        "typedef struct Thing {\n"
        "    Head head;\n"
        "    u8 timer; /* frame counter */\n"
        "    u16 item_id;\n"
        "    u8 flags; /* ThingFlags */\n"
        "    Coord pos;\n"
        "} Thing;\n"
        "extern Thing g_Things[];\n"
        "void SND_Play(SndId cue_id);\n"
        "void Item_Add(u16 item_id);\n"
    ),
    "src/a/a.h": '#include "game/thing.h"\n',
    "src/a/use.c": (
        '#include "a.h"\n'
        "\n"
        "MATCH void Use(void) {\n"
        "    u8 count;\n"
        "    s16 x;\n"
        "    Thing* thing;\n"
        "\n"
        "    thing = &g_Things[0];\n"
        "    thing->head.mode = 2;\n"
        "    thing->timer = 0x21U;\n"
        "    count = 0x10;\n"
        "    x = 0x20;\n"
        "    if ((count & 1) == 0) {\n"
        "        count += 0x1;\n"
        "    }\n"
        "    SND_Play(5);\n"
        "    Item_Add(0x3A);\n"
        "    switch (thing->head.mode) {\n"
        "    case 2:\n"
        "        count = 0;\n"
        "        break;\n"
        "    }\n"
        "    thing->flags |= 0x80;\n"
        "    count = FIELD(u8, thing, 4);\n"
        "}\n"
        "\n"
        "NON_MATCHING void Draft(void) {\n"
        "    Thing* thing;\n"
        "    thing->timer = 0x99;\n"
        "}\n"
    ),
}


@pytest.fixture
def repo(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> Path:
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    for name, text in FILES.items():
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    subprocess.run(["git", "-C", str(tmp_path), "add", "."], check=True)
    subprocess.run(
        ["git", "-C", str(tmp_path), "commit", "-qm", "init"],
        check=True,
        env={
            "GIT_AUTHOR_NAME": "t",
            "GIT_AUTHOR_EMAIL": "t@t",
            "GIT_COMMITTER_NAME": "t",
            "GIT_COMMITTER_EMAIL": "t@t",
            "PATH": "/usr/bin:/bin",
        },
    )
    monkeypatch.setattr(symbol, "ROOT", tmp_path)
    monkeypatch.setattr(symbol, "_VALUE_SHARED", {})
    monkeypatch.setattr(symbol, "_VALUE_INDEX", {})
    monkeypatch.setattr(symbol, "_VALUE_VIEWS", [])
    monkeypatch.setattr(
        symbol,
        "_layer_manifests",
        lambda: {"exe/a": SimpleNamespace(source_dir="src/a")},
    )
    return tmp_path


def rows(capsys: pytest.CaptureFixture[str]) -> list[dict]:
    return [json.loads(line) for line in capsys.readouterr().out.splitlines()]


def test_prefix_is_the_shared_tag_of_the_names() -> None:
    assert symbol._value_prefix(["THING_MODE_RUN", "THING_MODE_IDLE"]) == "THING_MODE_"
    assert symbol._value_prefix(["ONE"]) == ""


def test_records_keep_members_and_comments(repo: Path) -> None:
    records, typedefs = symbol._value_records()
    assert records["Thing"]["timer"] == ("u8", "frame counter")
    assert records["Head"]["mode"] == ("u8", "ThingMode")
    assert typedefs["u8"] == "unsigned char"


def test_type_walks_pointers_records_and_anonymous_unions(repo: Path) -> None:
    records, typedefs = symbol._value_records()
    symbol._VALUE_SHARED.update(
        {
            "records": records,
            "typedefs": typedefs,
            "globals": {"g_Things": "Thing[]"},
            "prototypes": {},
            "returns": {},
            "member_map": {},
        }
    )
    index = symbol._value_index("exe/a")
    scope = {"thing": "Thing*"}
    assert symbol._value_type("thing->head.mode", index, scope) == "u8"
    assert symbol._value_type("thing->pos.part.integer", index, scope) == "s16"
    assert symbol._value_type("g_Things[2].timer", index, scope) == "u8"


def test_scan_classifies_matched_bodies_only(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert symbol.main(["values", "--scan", "--jsonl"]) == 0
    found = rows(capsys)
    by_literal = {(row["literal"], row["constant"], row["form"]) for row in found}
    assert ("2", "THING_MODE_RUN", "") in by_literal
    assert ("0x21U", "", "33U") in by_literal
    assert ("0x10", "", "16") in by_literal
    assert ("0x20", "", "32") in by_literal
    assert ("1", "", "0x1") in by_literal
    assert ("5", "SND_A", "") in by_literal
    assert ("0x3A", "ITEM_HERB", "") in by_literal
    assert ("4", "", "0x4") in by_literal
    assert all(row["literal"] != "0x99" for row in found)
    roles = {row["literal"]: row["role"] for row in found}
    assert roles["0x21U"] == "count"
    assert roles["0x20"] == "coordinate"
    assert roles["4"] == "offset"
    assert roles["0x3A"] == "id"


def test_scan_reports_the_family_without_a_constant(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert symbol.main(["values", "--scan", "--jsonl"]) == 0
    found = [row for row in rows(capsys) if row["literal"] == "0x80"]
    assert found == [
        {
            "file": "src/a/use.c",
            "line": 23,
            "literal": "0x80",
            "role": "flags",
            "family": "ThingFlags",
            "constant": "",
            "form": "",
            "confidence": "typed",
        }
    ]


def test_fixed_point_value_has_no_one_name() -> None:
    index = {"families": {}, "names": {"ONE", "COORD_HALF"}}
    signal = symbol.ValueSignal("fixed", "", "typed", "16.16", "s32")
    assert symbol._value_role_constant(index, signal, 0x10000) == ("", "")
