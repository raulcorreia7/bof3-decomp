from __future__ import annotations

from psxdecomp.dmpsx import rewrite_text


def test_a_placeholder_in_text_is_rewritten():
    updated, count = rewrite_text(".text\n\t.word\t0x7F\n")

    assert count == 1
    assert updated == ".text\n\t.word\t0x4A180001\n"
