from __future__ import annotations

from pathlib import Path

from check_sources import images, orphans

IMAGES = {
    "overlays/plchar/plp278/00": (
        "config/emi/plchar/plp278/00/splat.yaml",
        {"PlChar_FieldTask", "D_801CE400"},
    )
}


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


def test_a_source_a_unit_includes_counts_as_named(tmp_path: Path) -> None:
    layout = tmp_path / "config/emi/test/arc/00/splat.yaml"
    layout.parent.mkdir(parents=True)
    layout.write_text(
        "options:\n  src_path: src/overlays/test/arc/00\n"
        "segments:\n"
        "  - type: code\n"
        "    start: 0\n"
        "    subsegments:\n"
        "      - [0x0, c, arc_00]\n"
    )
    unit = tmp_path / "src/overlays/test/arc/00/arc_00.c"
    unit.parent.mkdir(parents=True)
    unit.write_text('#include "arc_00.h"\n#include "first.c"\n#include "second.c"\n')
    assert images(tmp_path) == {
        "overlays/test/arc/00": (
            "config/emi/test/arc/00/splat.yaml",
            {"arc_00", "first", "second"},
        )
    }
