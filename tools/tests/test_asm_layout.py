from pathlib import Path

from bof3.toolchain.splat import (
    _clean_asm_tree,
    _extract_functions,
    _flatten_asm_tree,
)


def test_a_nested_copy_of_an_extracted_function_is_dropped(tmp_path: Path) -> None:
    base = tmp_path / "asm" / "emi" / "test" / "00"
    nested = base / "764"
    nested.mkdir(parents=True)
    body = (
        "nonmatching func_80000030, 0x8\n"
        "glabel func_80000030\n"
        "jr $ra\n"
        "nop\n"
        "endlabel func_80000030\n"
    )
    (nested / "func_80000030.s").write_text(body)
    (base / "764.s").write_text(body)

    _extract_functions(base)
    assert (base / "func_80000030.s").read_text() == body
    _flatten_asm_tree(base)

    assert (base / "func_80000030.s").read_text() == body
    assert not nested.exists()


def test_split_tree_is_flattened_and_keeps_hand_and_data(tmp_path: Path) -> None:
    base = tmp_path / "asm" / "emi" / "test" / "00"
    hand = base / "hand"
    hand.mkdir(parents=True)
    (hand / "func_80000000.s").write_text("glabel func_80000000\n")
    data = base / "data"
    data.mkdir()
    (data / "D_80000010.data.s").write_text(".word 1\n")
    nested = base / "764"
    nested.mkdir()
    (nested / "func_80000020.s").write_text(
        "nonmatching func_80000020, 0x8\n"
        "glabel func_80000020\n"
        "jr $ra\n"
        "nop\n"
        "endlabel func_80000020\n"
    )
    (base / "764.s").write_text(
        "nonmatching func_80000030, 0x8\n"
        "glabel func_80000030\n"
        "jr $ra\n"
        "nop\n"
        "endlabel func_80000030\n"
        "\n"
        "nonmatching func_80000038, 0x8\n"
        "glabel func_80000038\n"
        "jr $ra\n"
        "nop\n"
        "endlabel func_80000038\n"
    )

    _flatten_asm_tree(base)
    _extract_functions(base)

    assert not nested.exists()
    assert (base / "func_80000020.s").is_file()
    assert (base / "func_80000030.s").is_file()
    assert (base / "func_80000038.s").is_file()
    assert (base / "764.s").is_file()
    assert (hand / "func_80000000.s").is_file()
    assert (data / "D_80000010.data.s").is_file()

    _clean_asm_tree(base)

    assert (hand / "func_80000000.s").is_file()
    assert not (base / "func_80000020.s").exists()
    assert not (base / "data").exists()
