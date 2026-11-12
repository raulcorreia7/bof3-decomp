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
