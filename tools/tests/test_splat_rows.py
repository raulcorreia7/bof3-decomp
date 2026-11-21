from __future__ import annotations

from pathlib import Path

from bof3.toolchain.splat import _from_common_folder


def test_rows_of_an_image_with_outside_files_name_them_from_the_common_folder(
    tmp_path: Path,
) -> None:
    (tmp_path / "src/engine/slus").mkdir(parents=True)
    (tmp_path / "src/engine/slus/data_80149800.c").write_text("")
    rows = (
        "      - [0x0, c, ../sound/SND_Init]\n"
        "      - [0x4, c, func_80000004]\n"
        "      - [0x8, .rodata, func_80000004]\n"
        "      - [0xC, .rodata, data_80149800]\n"
        "      - [0x10, .data, D_80000010]\n"
        "      - [0x14, lib, toolchains/psyq/3.7/libspu/s_gks]\n"
    )
    document = {
        "options": {"src_path": "src/engine/slus"},
        "segments": [{"subsegments": [["0x0", "c", "../sound/SND_Init"]]}],
    }
    options = {"src_path": "src/engine/slus"}
    out = _from_common_folder(tmp_path, document, rows, options)
    assert options["src_path"] == "src/engine"
    assert out.splitlines() == [
        "      - [0x0, c, sound/SND_Init]",
        "      - [0x4, c, slus/func_80000004]",
        "      - [0x8, .rodata, slus/func_80000004]",
        "      - [0xC, .rodata, slus/data_80149800]",
        "      - [0x10, .data, D_80000010]",
        "      - [0x14, lib, toolchains/psyq/3.7/libspu/s_gks]",
    ]
