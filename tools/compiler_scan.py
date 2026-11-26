#!/usr/bin/env python3
"""Score functions under other compiler builds, GCC flags and maspsx settings.

    tools/compiler_scan.py --rows ROWS.jsonl --out OUT.jsonl [--variants singles|NAME,...]
                           [--jobs 20] [--toolchains DIR]

ROWS: JSON lines with "ref" (TARGET@0xADDR) and "src" (the C file to compile, as `MATCH_SRC`).
A variant is `base`, `gcc-<version>` (an old-gcc release unpacked in DIR/gcc-<version>/), a GCC
flag added after -O2 (`-fno-schedule-insns`), `-O1`/`-O3`, `nog`/`-g`/`-ggdb` for -gcoff,
`as-<version>` (maspsx --aspsx-version), `masp<option>` (an extra maspsx option), or several
joined with `+`. Each compile runs the unit's recorded command with the variant applied, with the
object cache off, and is scored with tools/sweep_edits.py's aligned-diff score (0 = byte match).
One JSON line per (function, variant) goes to OUT; a rerun skips the lines OUT already has.
The November 2026 trial: docs/toolchain.md#compiler-chain.
"""

import argparse
import json
import os
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor, as_completed

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, f"{ROOT}/tools")
from bof3.match import MatchResult, side_by_side  # noqa: E402
from sweep_edits import SHIFT, lcs_score, link_names  # noqa: E402

GCCS = [
    "2.5.7",
    "2.5.7-psx",
    "2.6.0",
    "2.6.0-psx",
    "2.6.3",
    "2.6.3-psx",
    "2.7.0",
    "2.7.1",
    "2.7.2",
    "2.7.2-psx",
    "2.7.2-cdk",
    "2.7.2.1",
    "2.7.2.2",
    "2.7.2.3",
    "2.8.0",
    "2.8.0-psx",
    "2.8.1",
    "2.8.1-psx",
    "2.91.66",
    "2.91.66-psx",
    "2.95.2",
    "2.95.2-psx",
]
FLAGS = [
    "-fno-cse-follow-jumps",
    "-fno-cse-skip-blocks",
    "-fno-schedule-insns",
    "-fno-schedule-insns2",
    "-fschedule-insns",
    "-fno-delayed-branch",
    "-fno-strength-reduce",
    "-fno-rerun-cse-after-loop",
    "-frerun-loop-opt",
    "-fno-rerun-loop-opt",
    "-fno-force-mem",
    "-fforce-mem",
    "-fforce-addr",
    "-fno-function-cse",
    "-fno-peephole",
    "-fno-thread-jumps",
    "-fno-expensive-optimizations",
    "-fno-caller-saves",
    "-fcaller-saves",
    "-fomit-frame-pointer",
    "-fno-omit-frame-pointer",
    "-fno-defer-pop",
    "-fno-inline",
    "-finline-functions",
    "-fshort-enums",
    "-fpcc-struct-return",
    "-fvolatile",
    "-fvolatile-global",
    "-fno-common",
    "-mlong-calls",
    "-mno-abicalls",
    "-mips2",
    "-mcpu=r3000",
    "-mgas",
    "-fkeep-static-consts",
    "-fno-gcse",
    "-fno-loop-optimize",
]


def variant(name, tc):
    """name -> (env, [(old, new)] edits on the command)."""
    env, edits = {}, []
    for part in name.split("+"):
        if part == "base":
            continue
        if part.startswith("gcc-"):
            env["PSX_GCC"] = f"{tc}/{part}/gcc"
        elif part in ("-O1", "-O3", "-O0"):
            edits.append((" -O2 ", f" {part} "))
        elif part == "-fsigned-char":
            edits.append((" -funsigned-char ", " -fsigned-char "))
        elif part in ("-g", "-g1", "-g3", "-ggdb", "-gstabs", "nog"):
            edits.append((" -gcoff ", " " if part == "nog" else f" {part} "))
        elif part == "-msoft-float-off":
            edits.append((" -msoft-float ", " "))
        elif part.startswith("as-"):
            edits.append(("--aspsx-version=2.56", f"--aspsx-version={part[3:]}"))
        elif part == "drop-cse":
            edits.append((" -O2 -fno-cse-follow-jumps -fno-cse-skip-blocks ", " -O2 "))
        elif part == "no-expand-div":
            edits.append((" -Wa,--expand-div ", " "))
        elif part.startswith("masp"):
            env["FLAGS_MASPSX"] = (env.get("FLAGS_MASPSX", "") + " " + part[4:]).strip()
        else:
            edits.append((" -O2 ", f" -O2 {part} "))
    return env, edits


SINGLES = (
    ["base"]
    + [f"gcc-{g}" for g in GCCS]
    + ["-O1", "-O3"]
    + FLAGS
    + ["-fsigned-char", "-g", "-g1", "-g3", "-ggdb", "nog", "-msoft-float-off"]
    + [f"as-{v}" for v in ("2.05", "2.21", "2.34", "2.67", "2.79", "2.81", "2.86")]
    + [
        "no-expand-div",
        "masp--expand-li",
        "masp--dont-expand-li",
        "masp--macro-inc",
        "masp--no-macro-inc",
        "masp--dont-force-G0",
        "masp--passthrough",
    ]
)

SELF = os.path.abspath(__file__)


def make_match(path):
    """match.sh with a hook that applies the variant to the unit's command."""
    with open(f"{ROOT}/tools/match.sh") as handle:
        text = handle.read()
    text = text.replace('cd "$(dirname "$0")/.."', f'cd "{ROOT}"')
    anchor = 'cmd="${cmd% -c *} -c $(realpath "$MATCH_SRC") -o $co"\n'
    assert anchor in text, "tools/match.sh changed: update compiler_scan.py"
    hook = f'\tcmd=$(printf %s "$cmd" | python3 "{SELF}" --edit-cmd)\n'
    with open(path, "w") as out:
        out.write(text.replace(anchor, anchor + hook))


def edit_cmd():
    """Apply FLAGS_EDITS to the command on stdin; run cc.py through this script."""
    cmd = " " + sys.stdin.read().strip() + " "
    cmd = cmd.replace(f"{ROOT}/tools/cc.py", f"{SELF} --cc", 1)
    for old, new in json.loads(os.environ.get("FLAGS_EDITS", "[]")):
        if old not in cmd:
            sys.exit(f"compiler_scan: {old!r} not in the command")
        cmd = cmd.replace(old, new, 1)
    print(cmd.strip())


def run_cc(argv):
    """tools/cc.py with the extra maspsx options of FLAGS_MASPSX."""
    import cc

    extra = os.environ.get("FLAGS_MASPSX", "").split()
    if extra:
        plain = cc.maspsx
        cc.maspsx = lambda args, text: plain([*args, *extra], text)
    sys.exit(cc.main(argv))


def one(ref, src, name, match, tc):
    env_v, edits = variant(name, tc)
    env = {
        **os.environ,
        **env_v,
        "MATCH_SRC": src,
        "FLAGS_EDITS": json.dumps(edits),
        "BOF3_CC_CACHE": "0",
    }
    with tempfile.TemporaryDirectory(prefix="flags-") as tmp:
        env["TMPDIR"] = tmp
        run = subprocess.run(
            ["sh", match, "--diff", ref],
            cwd=ROOT,
            env=env,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            timeout=300,
            check=False,
        )
    res = MatchResult(run.returncode, run.stdout)
    row = {"ref": ref, "variant": name}
    if res.matched:
        return {**row, "score": 0, "matched": True}
    retail, cand = side_by_side(res)
    if not cand:
        return {**row, "score": None, "matched": False, "err": run.stdout[-300:]}
    moved = SHIFT.search(res.output)
    shift = int(moved[1], 16) - int(moved[2], 16) if moved else 0
    s = lcs_score(retail, cand, link_names(ref.split("@")[0]), shift)
    return {
        **row,
        "score": int(s),
        "missing": s.missing,
        "extra": s.extra,
        "operands": s.operands,
        "retail_n": len(retail),
        "cand_n": len(cand),
        "matched": False,
    }


def main():
    if sys.argv[1:2] == ["--edit-cmd"]:
        return edit_cmd()
    if sys.argv[1:2] == ["--cc"]:
        return run_cc(sys.argv[2:])
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    ap.add_argument("--rows", required=True)
    ap.add_argument("--variants", default="singles")
    ap.add_argument("--out", required=True)
    ap.add_argument("--jobs", type=int, default=20)
    ap.add_argument(
        "--toolchains",
        default=f"{ROOT}/build/toolchains",
        help="unpacked old-gcc releases",
    )
    a = ap.parse_args()
    tc = os.path.abspath(a.toolchains)
    tmp = tempfile.mkdtemp(prefix="compiler-scan-")
    match = f"{tmp}/match.sh"
    make_match(match)
    with open(a.rows) as handle:
        rows = [json.loads(line) for line in handle if line.strip()]
    names = SINGLES if a.variants == "singles" else a.variants.split(",")
    jobs = []
    for r in rows:
        src = os.path.abspath(r["src"])
        jobs += [(r["ref"], src, n) for n in names]
    done = set()
    if os.path.exists(a.out):
        with open(a.out) as handle:
            for line in handle:
                d = json.loads(line)
                done.add((d["ref"], d["variant"]))
    jobs = [j for j in jobs if (j[0], j[2]) not in done]
    with open(a.out, "a") as out, ProcessPoolExecutor(a.jobs) as pool:
        futs = {pool.submit(one, *j, match, tc): j for j in jobs}
        for n, f in enumerate(as_completed(futs)):
            try:
                d = f.result()
            except Exception as e:
                j = futs[f]
                d = {
                    "ref": j[0],
                    "variant": j[2],
                    "score": None,
                    "matched": False,
                    "err": repr(e)[:200],
                }
            out.write(json.dumps(d) + "\n")
            out.flush()
            if n % 500 == 0:
                print(n, len(jobs), file=sys.stderr, flush=True)


if __name__ == "__main__":
    main()
