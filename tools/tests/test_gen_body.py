from __future__ import annotations

from pathlib import Path

import pytest

import gen_body

HEADER = """
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


def test_a_handwritten_instruction_comment_is_not_part_of_its_operand() -> None:
    text = "/* E4328 8017A328 00011A24 */  addiu      $k0, $zero, 0x100 /* handwritten instruction */\n"
    assert gen_body.instructions(text) == ["addiu $k0, $zero, 0x100"]
