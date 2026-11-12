from __future__ import annotations

from pathlib import Path

from check_sources import images, layout_names, orphans

IMAGES = {
    "overlays/plchar/plp278/00": (
        "config/emi/plchar/plp278/00/splat.yaml",
        {"C", "D_801CE400"},
    )
}


def test_a_named_source_passes() -> None:
    assert orphans(["src/overlays/plchar/plp278/00/C.c"], IMAGES) == []


def test_a_source_no_row_names_is_reported_with_its_layout() -> None:
    found = orphans(["src/overlays/plchar/plp278/00/func_801CFAA8.c"], IMAGES)
    assert found == [
        (
            "src/overlays/plchar/plp278/00/func_801CFAA8.c",
            "config/emi/plchar/plp278/00/splat.yaml",
        )
    ]


def test_a_source_outside_an_image_is_reported() -> None:
    found = orphans(["src/shared/thing.c"], IMAGES)
    assert found == [("src/shared/thing.c", "src/shared")]


def test_rows_name_sources_by_symbol_and_by_number() -> None:
    document = {
        "segments": [
            {
                "type": "code",
                "subsegments": [[0x0, ".data", "D_801D0C00"], [0x10, "c", 10]],
            },
            [0x1B48],
        ]
    }
    assert layout_names(document) == {"D_801D0C00", "10"}


def test_the_source_folder_comes_from_the_layout_options(tmp_path: Path) -> None:
    layout = tmp_path / "config/emi/test/arc/00/splat.yaml"
    layout.parent.mkdir(parents=True)
    layout.write_text(
        "segments:\n"
        "  - type: code\n"
        "    start: 0\n"
        "    subsegments:\n"
        "      - [0x0, c, a]\n"
    )
    assert images(tmp_path) == {
        "overlays/test/arc/00": ("config/emi/test/arc/00/splat.yaml", {"a"})
    }
