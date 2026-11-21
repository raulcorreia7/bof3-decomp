from pathlib import Path

from fixture import put_symbols

from bof3.toolchain.splat import splat_input_digest

SPLAT = "sha1: 00\nsymbol_owners:\n  - exe/other\nsegments: []\n"


def repo(tmp_path: Path, a: str, b: str) -> Path:
    """Two targets whose ``symbol_owners`` leave out their own rows."""
    for target in ("a", "b", "other"):
        (tmp_path / "config/exe" / target).mkdir(parents=True, exist_ok=True)
        (tmp_path / "config/exe" / target / "splat.yaml").write_text(SPLAT)
    put_symbols(tmp_path, f'["exe/a"]\n{a}\n["exe/b"]\n{b}\n["exe/other"]\n')
    return tmp_path


def digests(root: Path) -> tuple[str, str]:
    return (
        splat_input_digest(root, "exe/a"),
        splat_input_digest(root, "exe/b"),
    )


def test_renaming_a_row_changes_only_its_target_digest(tmp_path: Path) -> None:
    row = 'F = {{ addr = 0x10, type = "func", source = "{}" }}\n'
    before = digests(repo(tmp_path, row.format("x"), row.format("x")))
    after = digests(
        repo(tmp_path, row.format("x").replace("F =", "G ="), row.format("x"))
    )
    assert after[0] != before[0]
    assert after[1] == before[1]


def test_editing_evidence_keeps_the_digest(tmp_path: Path) -> None:
    row = 'F = {{ addr = 0x10, type = "func", source = "{}" }}\n'
    before = digests(repo(tmp_path, row.format("x"), ""))
    after = digests(repo(tmp_path, row.format("y"), ""))
    assert after == before


def test_a_layout_comment_keeps_the_digest(tmp_path: Path) -> None:
    root = repo(tmp_path, "", "")
    before = splat_input_digest(root, "exe/a")
    manifest = root / "config/exe/a/splat.yaml"
    manifest.write_text("# a note\n" + SPLAT)
    assert splat_input_digest(root, "exe/a") == before


def test_a_layout_segment_changes_the_digest(tmp_path: Path) -> None:
    root = repo(tmp_path, "", "")
    before = splat_input_digest(root, "exe/a")
    manifest = root / "config/exe/a/splat.yaml"
    manifest.write_text(SPLAT.replace("segments: []", "segments: [[0, bin, x]]"))
    assert splat_input_digest(root, "exe/a") != before
