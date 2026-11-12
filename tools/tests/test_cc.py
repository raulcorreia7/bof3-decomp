from __future__ import annotations

from pathlib import Path

from bof3.resolve import load_target_manifests
from bof3.resolve.ids import asm_dir

ROOT = Path(__file__).resolve().parents[2]


def test_every_image_folder_follows_from_its_source_folder() -> None:
    for target, manifest in load_target_manifests(ROOT).items():
        source = ROOT / manifest.source_dir / "func_80000000.c"
        assert asm_dir(source, ROOT) == f"asm/{target}"


def test_a_source_outside_src_has_no_asm_dir() -> None:
    assert asm_dir(ROOT / "emit/empty.c", ROOT) is None


def test_authored_assembly_selects_the_hand_folder(tmp_path: Path) -> None:
    hand = tmp_path / "asm/exe/slus_004_22/hand"
    hand.mkdir(parents=True)
    (hand / "a.s").write_text("")
    assert (
        asm_dir(tmp_path / "src/engine/slus/a.c", tmp_path)
        == "asm/exe/slus_004_22/hand"
    )
    assert asm_dir(tmp_path / "src/engine/slus/b.c", tmp_path) == "asm/exe/slus_004_22"
