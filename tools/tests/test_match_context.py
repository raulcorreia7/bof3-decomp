import shutil
import subprocess
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "match_context.sh"
TARGET = "emi/test/00"

# A split file named after its symbol: only its first instruction comment carries the address.
NAMED_ASM = """\
.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

nonmatching Battle_Foo, 0x8

glabel Battle_Foo
    /* 0 80000000 27BDFFF8 */  addiu      $sp, $sp, -0x8
    /* 4 80000004 03E00008 */  jr         $ra
    /* 8 80000008 00000000 */   nop
"""

ADDRESS_ASM = """\
.include "macro.inc"

nonmatching func_80000100, 0x4

glabel func_80000100
    /* 0 80000100 00000000 */  nop
"""


def make_repo(tmp_path: Path) -> Path:
    repo = tmp_path / "repo"
    (repo / "tools").mkdir(parents=True)
    shutil.copy(SCRIPT, repo / "tools" / "match_context.sh")
    (repo / "build/asm" / TARGET).mkdir(parents=True)
    (repo / "build/asm" / TARGET / "Battle_Foo.s").write_text(NAMED_ASM)
    (repo / "build/asm" / TARGET / "func_80000100.s").write_text(ADDRESS_ASM)
    (repo / "src" / "emi" / "test").mkdir(parents=True)
    (repo / "src" / "emi" / "test" / "Battle_Foo.c").write_text(
        "#ifdef NON_MATCHING\nNON_MATCHING void Battle_Foo(void) {\n}\n"
        "#else\nINCLUDE_ASM(Battle_Foo);\n#endif\n"
    )
    (repo / "src" / "emi" / "test" / "func_80000100.c").write_text(
        "INCLUDE_ASM(func_80000100);\n"
    )
    return repo


def run(repo: Path, ref: str) -> subprocess.CompletedProcess:
    return subprocess.run(
        ["sh", "tools/match_context.sh", ref],
        cwd=repo,
        capture_output=True,
        text=True,
        check=False,
    )


def test_a_split_file_named_after_its_symbol_prints_its_assembly(
    tmp_path: Path,
) -> None:
    result = run(make_repo(tmp_path), f"{TARGET}@0x80000000")
    lines = result.stdout.splitlines()
    assert lines[0] == "== asm build/asm/emi/test/00/Battle_Foo.s"
    assert lines[1] == "80000000  addiu      $sp, $sp, -0x8"
    assert "can't read" not in result.stderr
    assert lines[lines.index("== file") + 1] == "src/emi/test/Battle_Foo.c"
