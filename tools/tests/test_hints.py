from pathlib import Path

from bof3.link import symbols
from bof3.source import hints
from bof3.source.index import Func

FUNC = Func(
    image="exe/a",
    name="func_80140000",
    addr=0x80140000,
    size=0x20,
    words=(),
    sha1="",
    status="ASM",
    src="src/a/func_80140000.c",
)


def context(table=None, splat="", ranked=()):
    return hints.Context(Path("."), FUNC, table or {}, splat, tuple(ranked))


def run(detector, text, **kwargs):
    return detector(hints.parse(text), context(**kwargs))


def test_scratchpad_counts_the_cell_and_the_reloads():
    text = """
    lui $v1, (0x1F800044 >> 16)
    lw $v1, (0x1F800044 & 0xFFFF)($v1)
    lui $v1, (0x1F800044 >> 16)
    lw $v1, (0x1F800044 & 0xFFFF)($v1)
    """
    lines = run(hints.scratchpad, text)
    assert len(lines) == 1
    assert "0x1F800044" in lines[0]
    assert "reloaded" in lines[0]


def test_scratchpad_names_a_cell_from_the_table():
    entry = symbols.Entry("g_Task", 0x1F800044, type="Task*")
    lines = run(
        hints.scratchpad,
        "lui $v1, (0x1F800044 >> 16)\nlw $v1, (0x1F800044 & 0xFFFF)($v1)",
        table={"exe/a": [entry]},
    )
    assert "g_Task" in lines[0]


def test_narrow_argument_is_a_cast_at_the_use():
    lines = run(hints.narrow_arguments, "andi $a0, $a0, 0xff")
    assert "argument a0" in lines[0]
    assert "cast" in lines[0]


def test_narrow_local_is_a_narrow_type():
    lines = run(hints.narrow_locals, "addiu $v0, $v0, 1\nandi $v0, $v0, 0xff")
    assert "local v0" in lines[0]
    assert "u8" in lines[0]


def test_jump_table_names_the_table_and_splat():
    text = "lui $at, %hi(jtbl_801EEC0C)\nlw $v0, %lo(jtbl_801EEC0C)($at)\njr $v0"
    lines = run(hints.jump_table, text, splat="jtbl_801EEC0C")
    assert "jtbl_801EEC0C" in lines[0]
    assert "yes" in lines[0]


def test_twice_finds_the_same_call_twice():
    text = """
addiu $a0, $zero, 1
jal func_80140010
nop
addiu $a0, $zero, 1
jal func_80140010
nop
"""
    lines = run(hints.twice, text)
    assert "func_80140010" in lines[0]
    assert "same argument setup" in lines[0]


def test_rodata_copy_counts_the_stack_words_before_jalr():
    text = """
lw $t0, 0x0($a0)
sw $t0, 0x10($sp)
lw $t0, 0x4($a0)
sw $t0, 0x14($sp)
lw $t0, 0x8($a0)
sw $t0, 0x18($sp)
lw $t0, 0xC($a0)
sw $t0, 0x1C($sp)
jalr $t0
nop
"""
    lines = run(hints.rodata_copy, text)
    assert "4 words" in lines[0]
    assert "jalr" in lines[0]


def test_frame_reports_size_saves_and_slots():
    text = """
addiu $sp, $sp, -0x28
sw $ra, 0x24($sp)
sw $s0, 0x20($sp)
sw $v0, 0x18($sp)
sw $v1, 0x1C($sp)
"""
    lines = run(hints.frame, text)
    assert "frame 0x28" in lines[0]
    assert "s0" in lines[0] and "ra" in lines[0]
    assert "2 stack slot(s)" in lines[0]


def test_addresses_resolve_through_the_table():
    entry = symbols.Entry("g_Game", 0x80146110, type="PartyMember", size=0x40)
    text = "lui $v0, 0x8014\naddiu $v0, $v0, 0x6110"
    lines = run(hints.addresses, text, table={"exe/a": [entry]})
    assert "0x80146110" in lines[0]
    assert "g_Game" in lines[0]


def test_twin_names_the_closest_body(tmp_path):
    closest = Func(
        image="exe/a",
        name="Twin",
        addr=0x80140010,
        size=0x8,
        words=(),
        sha1="",
        status="C",
        src="src/a/Twin.c",
    )
    (tmp_path / "src/a").mkdir(parents=True)
    (tmp_path / "src/a/Twin.h").write_text("MATCH void Twin(void) {}\n")
    ctx = hints.Context(tmp_path, FUNC, {}, "", ((0.9, closest),))
    assert "shared body src/a/Twin.h" in hints.twin(ctx)[0]
