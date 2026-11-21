from __future__ import annotations

import subprocess
from pathlib import Path

from bof3.core.paths import ROOT
from permuter_import import PERMUTER_FLAGS, function_name


def test_an_assembly_unit_gives_the_macro_argument(tmp_path: Path) -> None:
    source = tmp_path / "a.c"
    source.write_text("#if BOF3_USE_ASM\nMATCH INCLUDE_ASM(func_801642F4);\n#endif\n")
    assert function_name(source) == "func_801642F4"


def test_psyq_register_names_stay_out_of_the_preprocessed_source(
    tmp_path: Path,
) -> None:
    source = tmp_path / "a.c"
    source.write_text("#include <r3000.h>\nint f(P *p) { return p->v0; }\n")
    flags = [f for f in PERMUTER_FLAGS.split() if f.startswith(("-D", "-U"))]
    assert "-D_ASM_H" in flags
    out = subprocess.run(
        ["cpp", "-P", "-undef", f"-I{ROOT}/include/psyq", *flags, str(source)],
        capture_output=True,
        text=True,
        check=True,
    ).stdout
    assert "$" not in out
