"""sweep_edits leaves the source byte-for-byte as it was, even on a failed compile or an interrupt."""

from __future__ import annotations

from pathlib import Path

import pytest

import sweep_edits

DRAFT = (
    "#ifdef NON_MATCHING\n"
    "NON_MATCHING s32 func_80100000(s32 count) {\n"
    "    s32 i;\n"
    "    s32 total;\n"
    "\n"
    "    total = 0;\n"
    "    for (i = 0; i < count; i += 1) {\n"
    "        total = total + i;\n"
    "    }\n"
    "    return total;\n"
    "}\n"
    "#else\n"
    "INCLUDE_ASM(func_80100000);\n"
    "#endif\n"
)


def test_the_source_is_untouched_after_a_failed_compile_and_an_interrupt(
    tmp_path: Path,
) -> None:
    source = tmp_path / "src" / "func_80100000.c"
    source.parent.mkdir()
    source.write_bytes(DRAFT.encode())
    scratch = tmp_path / "scratch"
    scratch.mkdir()
    calls = []

    def judge(ref: str, path: Path) -> int | None:
        assert path.parent.parent == scratch
        calls.append(path.read_text())
        if len(calls) == 1:
            return 5
        if len(calls) == 2:
            return None
        raise KeyboardInterrupt

    with pytest.raises(KeyboardInterrupt):
        sweep_edits.sweep(
            "t@0x80100000", "func_80100000", source, False, judge, scratch
        )

    assert len(calls) == 3 and calls[1] != DRAFT
    assert source.read_bytes() == DRAFT.encode()
    assert not list(scratch.iterdir())
