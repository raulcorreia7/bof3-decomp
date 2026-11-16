"""prepare_link reads Splat's linker script and never rewrites it."""

from __future__ import annotations

from pathlib import Path
from types import SimpleNamespace

import pytest

from bof3.core.paths import ASM, BUILD, CONFIG
from bof3.link import script
from bof3.resolve.manifests import SectionPlacement

TARGET = "emi/etc/start/08"
SPLAT = (
    "    .rodata 0x801E1000 : AT(0)\n"
    "    {\n"
    "        build/src/start/func_801E1C20.c.o(.rodata);\n"
    "    }\n"
)
WRAPPER = "build/p2/emi/etc/start/08/placements/func_801E1C20.rodata.s.o(.rodata)"


def _prepare(
    root: Path, monkeypatch: pytest.MonkeyPatch, state: str
) -> script.Prepared:
    unit = SimpleNamespace(name="func_801E1C20", vaddr=0x801E1C20, source=None)
    manifest = SimpleNamespace(
        binary="build/bin/start.bin",
        splat=f"{CONFIG}/{TARGET}/splat.yaml",
        load_address=0x801E0000,
        section_placements={
            "start": [SectionPlacement(0x801E1C20, ".rodata", 0x801E1000, 0x40)]
        },
    )
    monkeypatch.setattr(script, "load_target_manifest", lambda *a, **k: manifest)
    monkeypatch.setattr(
        script.target_map,
        "load_target",
        lambda *a, **k: SimpleNamespace(reviewed_code=[unit]),
    )
    monkeypatch.setattr(script.status_model, "unit_state", lambda _: state)
    monkeypatch.setattr(
        script, "parse_splat_layout", lambda *a: SimpleNamespace(image_base=0x801E0000)
    )
    return script.prepare_link(root, TARGET)


def test_a_unit_goes_from_wrapper_to_object_on_one_splat_script(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    (tmp_path / CONFIG / TARGET).mkdir(parents=True)
    (tmp_path / CONFIG / TARGET / "splat.yaml").write_text("", encoding="utf-8")
    linker = tmp_path / BUILD / ASM / TARGET / "linker.ld"
    linker.parent.mkdir(parents=True)
    linker.write_text(SPLAT, encoding="utf-8")

    placed = _prepare(tmp_path, monkeypatch, "non_exact")
    assert WRAPPER in placed.text
    assert "func_801E1C20.c.o(.rodata)" not in placed.text
    assert linker.read_text(encoding="utf-8") == SPLAT

    matched = _prepare(tmp_path, monkeypatch, "exact")
    assert "func_801E1C20.c.o(.rodata)" in matched.text
    assert WRAPPER not in matched.text
