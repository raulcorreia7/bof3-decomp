"""split decides which rows of the graph are drafts and which files the graph depends on."""

from __future__ import annotations

from pathlib import Path

import split


def test_draft_rows_name_only_sources_with_a_draft_function(tmp_path: Path) -> None:
    (tmp_path / "src/a").mkdir(parents=True)
    (tmp_path / "src/a/draft.c").write_text(
        "NON_MATCHING void f(void) {}\n", encoding="utf-8"
    )
    (tmp_path / "src/a/plain.c").write_text(
        "void g(void) {}\n// NON_MATCHING in a comment\n", encoding="utf-8"
    )
    rows = [
        "c\tn1\tsrc/a/draft.c\tasm/a",
        "c\tn2\tsrc/a/plain.c\tasm/a",
        "s\tn3\tasm/x.s",
        "b\tn4\tbin/x.bin",
    ]
    result = split.draft_rows(tmp_path, rows)
    assert len(result) == 1
    d, name, source, asm_dir = result[0].split("\t")
    assert (d, source, asm_dir) == ("d", "src/a/draft.c", "asm/a")
    assert name != "n1" and name.endswith(".o")
