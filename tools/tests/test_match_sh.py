import os
import shutil
import subprocess
from pathlib import Path

SCRIPT = Path(__file__).resolve().parents[1] / "match.sh"
TARGET = "emi/test/00"
ADDRESS = "80000000"

ASM = """\
.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

nonmatching func_80000000, 0x4

glabel func_80000000
    /* 0 80000000 00000000 */  nop
endlabel func_80000000
"""

# A draft whose guard the image build does not enable: the definition carries no
# NON_MATCHING marker, so match.sh builds the ordinary object and the split assembly
# supplies the function.
SOURCE = """\
#ifdef NON_MATCHING
s32 func_80000000(void) {
    return 0;
}
#else
INCLUDE_ASM(func_80000000);
#endif
"""

NINJA = """\
#!/bin/sh
dir=.
target=
while [ $# -gt 0 ]; do
    case $1 in
    -C) dir=$2; shift 2 ;;
    -t) exit 0 ;;
    *) target=$1; shift ;;
    esac
done
[ -n "$target" ] || exit 0
mkdir -p "$dir/$(dirname "$target")"
printf x >"$dir/$target"
"""

NM = """\
#!/bin/sh
printf '00000000 00000004 T func_80000000\\n'
printf '00000000 00000004 T func_80000000.NON_MATCHING\\n'
"""


def make_repo(tmp_path: Path) -> Path:
    repo = tmp_path / "repo"
    (repo / "tools").mkdir(parents=True)
    shutil.copy(SCRIPT, repo / "tools" / "match.sh")
    (repo / "config" / TARGET).mkdir(parents=True)
    payload = repo / "build" / "bin" / f"{TARGET}.bin"
    payload.parent.mkdir(parents=True)
    payload.write_bytes(b"\0" * 4)
    (repo / "build" / "meson").mkdir()
    (repo / "build" / "meson" / "build.ninja").write_text("")
    (repo / "build" / "ld").mkdir()
    (repo / "build" / "ld" / "emi+test+00.ld").write_text(
        "  src+overlays+test+00+C.c.o(.text);\n"
    )
    (repo / "asm" / TARGET).mkdir(parents=True)
    (repo / "asm" / TARGET / "C.s").write_text(ASM)
    (repo / "src" / "overlays" / "test" / "00").mkdir(parents=True)
    (repo / "src" / "overlays" / "test" / "00" / "C.c").write_text(SOURCE)
    binutils = repo / "bin" / "internal" / "binutils"
    binutils.mkdir(parents=True)
    write_exe(binutils / "nm", NM)
    write_exe(binutils / "objdump", "#!/bin/sh\nexit 0\n")
    write_exe(binutils / "ld", "#!/bin/sh\nexit 0\n")
    write_exe(binutils / "objcopy", "#!/bin/sh\nexit 0\n")
    fakebin = repo / "fakebin"
    fakebin.mkdir()
    write_exe(fakebin / "ninja", NINJA)
    return repo


def write_exe(path: Path, text: str) -> None:
    path.write_text(text)
    path.chmod(0o755)


def run(repo: Path) -> subprocess.CompletedProcess:
    env = dict(os.environ, PATH=f"{repo / 'fakebin'}:{os.environ['PATH']}")
    return subprocess.run(
        ["sh", "tools/match.sh", f"{TARGET}@0x{ADDRESS}"],
        cwd=repo,
        env=env,
        capture_output=True,
        text=True,
        check=False,
    )


def test_a_function_from_the_split_assembly_never_matches(tmp_path: Path) -> None:
    result = run(make_repo(tmp_path))
    assert result.returncode == 2
    assert "still INCLUDE_ASM" in result.stderr


SPLAT = """\
segments:
  - name: main
    start: 0x0
    vram: 0x80000000
    subsegments:
      - [0x40, .rodata, C]
      - [0x80, c, C]
"""

LINK_SCRIPT = """\
    .main 0x80000000 : AT(0) SUBALIGN(4)
        src+overlays+test+00+C.c.o(.text);
        src+overlays+test+00+C.c.o(.rodata);
"""

OBJDUMP = """\
#!/bin/sh
case " $* " in
*" -r "*) printf '00000000 R_MIPS_HI16       %s\\n' "$RELOC_TARGET" ;;
esac
"""

# Records the partial link script; objcopy writes the zero word that equals the retail bytes.
LD = '#!/bin/sh\nwhile [ $# -gt 0 ]; do [ "$1" != -T ] || cp "$2" linkscript.ld; shift; done\n'
OBJCOPY = "#!/bin/sh\nfor a; do out=$a; done\nprintf '\\0\\0\\0\\0' >\"$out\"\n"
PYTHON = (
    '#!/bin/sh\nwhile [ $# -gt 0 ]; do [ "$1" != --output ] || : >"$2"; shift; done\n'
)


def rodata_repo(tmp_path: Path) -> Path:
    repo = make_repo(tmp_path)
    (repo / "config" / TARGET / "splat.yaml").write_text(SPLAT)
    (repo / "build" / "ld" / "emi+test+00.ld").write_text(LINK_SCRIPT)
    binutils = repo / "bin" / "internal" / "binutils"
    write_exe(
        binutils / "nm", "#!/bin/sh\nprintf '00000000 00000004 T func_80000000\\n'\n"
    )
    write_exe(binutils / "objdump", OBJDUMP)
    write_exe(binutils / "ld", LD)
    write_exe(binutils / "objcopy", OBJCOPY)
    (repo / ".venv" / "bin").mkdir(parents=True)
    write_exe(repo / ".venv" / "bin" / "python", PYTHON)
    return repo


def run_with(repo: Path, reloc_target: str) -> subprocess.CompletedProcess:
    env = dict(
        os.environ,
        PATH=f"{repo / 'fakebin'}:{os.environ['PATH']}",
        RELOC_TARGET=reloc_target,
    )
    return subprocess.run(
        ["sh", "tools/match.sh", f"{TARGET}@0x{ADDRESS}"],
        cwd=repo,
        env=env,
        capture_output=True,
        text=True,
        check=False,
    )


def test_the_units_own_rodata_links_at_its_retail_address(tmp_path: Path) -> None:
    repo = rodata_repo(tmp_path)
    result = run_with(repo, ".rodata")
    assert result.returncode == 0, result.stderr
    assert (
        ".rodata 0x80000040 (NOLOAD) : SUBALIGN(4)"
        in (repo / "linkscript.ld").read_text()
    )


def test_a_unit_without_a_rodata_row_links_its_rodata_at_a_sentinel(
    tmp_path: Path,
) -> None:
    repo = rodata_repo(tmp_path)
    (repo / "config" / TARGET / "splat.yaml").write_text(
        SPLAT.replace(".rodata, C", ".rodata, X")
    )
    assert run_with(repo, ".rodata").returncode == 0
    assert ".rodata 0x10 " in (repo / "linkscript.ld").read_text()


def test_the_units_own_data_is_still_not_covered(tmp_path: Path) -> None:
    result = run_with(rodata_repo(tmp_path), ".data")
    assert result.returncode == 2
    assert "not covered" in result.stderr
