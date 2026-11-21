from __future__ import annotations

from pathlib import Path

import pytest

import gen_body

HEADER = """
typedef struct Header {
    u8 flags;
    u8 mode;
    u8 step;
} Header;

typedef union Coord {
    s32 fixed;

    struct {
        u16 fraction;
        s16 integer;
    } part;
} Coord;

typedef struct Vec {
    Coord x;
    Coord y;
} Vec;

typedef Vec Pos;

typedef struct Work {
    Header header;   /* 0x00 */
    u8     unk_03;   /* 0x03 */
    u8*    script;   /* 0x04 */
    Pos    pos;      /* 0x08 */
    Mystery other;   /* 0x14 */
    u16    unk_18;   /* 0x18 */
} Work;

typedef struct State {
    s32 first;
    struct {
        u8 a;
        u8 b;
    } pair;
} State;

extern State g_State;
"""


@pytest.fixture
def tree(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> gen_body.Tree:
    (tmp_path / "work.h").write_text(HEADER, encoding="utf-8")
    monkeypatch.setattr(gen_body, "_HEADERS", ["work.h"])
    return gen_body.Tree(tmp_path)


class Container:
    """The names table, with every word of g_State inside the record."""

    def container(self, image: str, addr: int):
        return (0x80100000, 8, "g_State") if 0x80100000 <= addr < 0x80100008 else None


def test_a_word_of_a_record_is_written_as_its_member(tree: gen_body.Tree) -> None:
    ctx = {
        "names": Container(),
        "image": "emi/x/y",
        "files": ["work.h"],
        "tree": tree,
    }
    assert gen_body.global_text("D_80100004", ctx, 1) == "g_State.pair.a"
    assert gen_body.global_text("D_80100005", ctx, 1) == "g_State.pair.b"
    assert gen_body.global_text("D_80100000", ctx, 4) == "g_State.first"
    # No member of that width sits there: the word keeps its own name.
    assert gen_body.global_text("D_80100004", ctx, 2) == "D_80100004"
