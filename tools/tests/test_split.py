"""split decides which rows of the graph are drafts and which files the graph depends on."""

from __future__ import annotations

from pathlib import Path

import pytest

import split
from bof3.core.paths import CONFIG


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


def test_graph_inputs_list_config_files_and_extra_sources(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    (tmp_path / CONFIG / "t").mkdir(parents=True)
    (tmp_path / CONFIG / "t/target.toml").write_text("", encoding="utf-8")
    (tmp_path / CONFIG / "link.toml").write_text("", encoding="utf-8")
    # None of these can change a row of the graph.
    for name in ("attempts.jsonl", "address_names.txt", "disc.toml"):
        (tmp_path / CONFIG / name).write_text("", encoding="utf-8")
    (tmp_path / "tools").mkdir()
    monkeypatch.setattr(split, "__file__", str(tmp_path / "tools/split.py"))
    result = split.graph_inputs(tmp_path, {"src/z.c"})
    assert result == sorted(
        [f"{CONFIG}/t/target.toml", f"{CONFIG}/link.toml", "tools/split.py", "src/z.c"]
    )


def test_ensure_payload_returns_an_existing_binary(tmp_path: Path) -> None:
    class Manifest:
        binary = "build/bin/x.bin"
        kind = "executable"
        disc_id = "X"

    (tmp_path / "build/bin").mkdir(parents=True)
    (tmp_path / "build/bin/x.bin").write_bytes(b"1")
    assert split.ensure_payload(tmp_path, Manifest()) == tmp_path / "build/bin/x.bin"  # type: ignore[arg-type]


def test_ensure_payload_copies_the_disc_file_for_an_executable(tmp_path: Path) -> None:
    class Manifest:
        binary = "build/bin/x.bin"
        kind = "executable"
        disc_id = "SLUS_004.22"

    (tmp_path / "build/disc").mkdir(parents=True)
    (tmp_path / "build/disc/SLUS_004.22").write_bytes(b"abc")
    binary = split.ensure_payload(tmp_path, Manifest())  # type: ignore[arg-type]
    assert binary.read_bytes() == b"abc"


def test_ensure_payload_reports_a_missing_retail_file(tmp_path: Path) -> None:
    class Manifest:
        binary = "build/bin/x.bin"
        kind = "executable"
        disc_id = "NOPE"

    with pytest.raises(RuntimeError, match="missing retail payload"):
        split.ensure_payload(tmp_path, Manifest())  # type: ignore[arg-type]
