#!/usr/bin/env python3
"""Compile one C file the way the retail build did: GCC 2.7.2 PSX, maspsx, DMPSX, GNU as.

    cc.py [--build-dir DIR] [--empty-on-failure] GCC_ARGUMENT... -c SOURCE -o OBJECT

The arguments are GCC's. `-Wa,--aspsx-version=V` and `-Wa,--expand-div` go to maspsx and
every other `-Wa,` item to the assembler. `-MMD -MP -MF FILE` writes a depfile that also
names the split assembly that `INCLUDE_ASM` pulls in. A source under `src/` also gets
`-I<its folder>` and, unless the arguments give one, `-DASM_DIR` for its image.

--build-dir DIR     resolve -o and -MF against DIR, run from the repository root and write
                    depfile paths relative to DIR (Meson and Ninja)
--empty-on-failure  hide the compiler's output; a source that does not compile leaves an
                    empty object and succeeds (draft objects for the report)

PSX_GCC=<path> picks the compiler binary. Run it as a script: `python -m` would put the
working directory, a build directory that changes with every object, on the import path.
"""

import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GCC = os.environ.get("PSX_GCC") or f"{ROOT}/toolchains/gcc-2.7.2-psx/gcc"
GCC_DIR = os.path.dirname(os.path.realpath(GCC))
AS = f"{ROOT}/bin/internal/binutils/as"
MASPSX = f"{ROOT}/third_party/maspsx/maspsx.py"
#: INCLUDE_ASM pulls split assembly in through the assembler, which `gcc -MM` cannot see.
ASM_INCLUDE = re.compile(r'^\s*\.include "([^"]+/[^"]+\.s)"', re.M)


def parse(argv):
    """Split the arguments into the pieces each stage needs."""
    plan = {
        "gcc": [],
        "as": [],
        "version": "2.56",
        "div": False,
        "dep": False,
        "phony": False,
    }
    source = output = depfile = None
    items = iter(argv)
    for arg in items:
        if arg == "-o":
            output = next(items)
        elif arg == "-MF":
            depfile = next(items)
        elif arg in ("-MMD", "-MD"):
            plan["dep"] = True
        elif arg == "-MP":
            plan["phony"] = True
        elif arg == "-c":
            pass
        elif arg.startswith("-Wa,"):
            for item in arg[4:].split(","):
                if item.startswith("--aspsx-version="):
                    plan["version"] = item.split("=", 1)[1]
                elif item == "--expand-div":
                    plan["div"] = True
                elif item:
                    plan["as"].append(item)
        elif arg.endswith(".c"):
            source = arg
        else:
            plan["gcc"].append(arg)
    if source is None or output is None:
        sys.exit("cc: -c needs one C source and one -o output")
    plan.update(source=source, output=output, depfile=depfile if plan["dep"] else None)
    return plan


def asm_dir(source, root=ROOT):
    """Return the `ASM_DIR` of a source under `src/`: its image folder, or its hand folder.

    The image follows from the source folder: `src/engine/slus`, `src/logo`, and
    `.../<archive>/<slot>/<file>` for the one `emi/<family>/<archive>/<slot>` under `config/`.
    """
    parts = os.path.relpath(os.path.abspath(source), root).split(os.sep)
    if parts[0] != "src":
        return None
    if parts[1:3] == ["engine", "slus"]:
        target = "exe/slus_004_22"
    elif parts[1] == "logo":
        target = "exe/logo"
    elif len(parts) >= 5:
        import glob

        found = glob.glob(f"{root}/config/emi/*/{parts[-3]}/{parts[-2]}/splat.yaml")
        if len(found) != 1:
            return None
        target = os.path.relpath(os.path.dirname(found[0]), f"{root}/config")
    else:
        return None
    stem = os.path.splitext(parts[-1])[0]
    hand = f"asm/{target}/hand"
    return hand if os.path.isfile(f"{root}/{hand}/{stem}.s") else f"asm/{target}"


def run(argv, **kw):
    return subprocess.run(argv, check=False, **kw)


def maspsx(args, text):
    """Run maspsx's command line in this process; return its output, or None when it fails.

    A second interpreter start costs more than maspsx's own work on a small source.
    """
    import importlib.util
    import io

    sys.path.insert(0, os.path.dirname(MASPSX))
    spec = importlib.util.spec_from_file_location("maspsx_cli", MASPSX)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    saved = sys.argv, sys.stdin, sys.stdout
    sys.argv = [MASPSX, *args]
    sys.stdin = io.StringIO(text)
    sys.stdout = out = io.StringIO()
    try:
        module.main()
    except SystemExit as exc:
        if exc.code:
            return None
    finally:
        sys.argv, sys.stdin, sys.stdout = saved
    return out.getvalue()


def compile_one(plan, env, tmp, build_dir):
    """Run the four stages; return the exit status."""
    source, output = plan["source"], plan["output"]
    gcc_args = plan["gcc"]
    if not any(a.startswith("-DASM_DIR=") for a in gcc_args):
        directory = asm_dir(source)
        if directory:
            gcc_args = [*gcc_args, f'-DASM_DIR="{directory}"']
    folder = os.path.dirname(source)
    if os.path.relpath(os.path.abspath(source), ROOT).startswith("src" + os.sep):
        gcc_args = [*gcc_args, f"-I{folder}"]
    os.makedirs(os.path.dirname(output) or ".", exist_ok=True)
    asm = f"{tmp}/cc1.s"
    if run([GCC, *gcc_args, "-S", "-o", asm, source], env=env).returncode:
        return 1
    masp = [f"--aspsx-version={plan['version']}"]
    if plan["div"]:
        masp.append("--expand-div")
    with open(asm, "rb") as fin:
        text = maspsx(masp, fin.read().decode("utf-8"))
    if text is None:
        return 1
    from psxdecomp.dmpsx import UnknownPlaceholder, rewrite_text

    try:
        text = rewrite_text(text)[0]
    except UnknownPlaceholder as exc:
        print(f"cc: {source}: {exc}", file=sys.stderr)
        return 1
    translated = f"{tmp}/masp.s"
    with open(translated, "w", encoding="utf-8") as out:
        out.write(text)
    if run([AS, *plan["as"], "-o", output, translated]).returncode:
        return 1
    if plan["depfile"]:
        scan = run(
            [GCC, "-MM", *gcc_args, source], env=env, stdout=subprocess.PIPE, text=True
        )
        if scan.returncode:
            return 1
        deps = scan.stdout.split(":", 1)[1].replace("\\\n", " ").split()
        with open(asm, encoding="utf-8", errors="replace") as handle:
            deps += ASM_INCLUDE.findall(handle.read())
        target = output
        if build_dir:
            deps = [os.path.relpath(path, build_dir) for path in deps]
            target = os.path.relpath(output, build_dir)
        lines = [f"{target}: {' '.join(deps)}\n"]
        if plan["phony"]:
            lines += [f"{dep}:\n" for dep in deps[1:]]
        with open(plan["depfile"], "w", encoding="utf-8") as out:
            out.write("".join(lines))
    return 0


def main(argv):
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0 if argv else 2
    build_dir = None
    empty = False
    while argv and argv[0] in ("--build-dir", "--empty-on-failure"):
        if argv.pop(0) == "--build-dir":
            build_dir = os.path.abspath(argv.pop(0))
        else:
            empty = True
    plan = parse(argv)
    if build_dir:
        plan["output"] = os.path.join(build_dir, plan["output"])
        if plan["depfile"]:
            plan["depfile"] = os.path.join(build_dir, plan["depfile"])
        os.chdir(ROOT)
    tmp = tempfile.mkdtemp(prefix="bof3-cc-")
    env = dict(
        os.environ,
        LC_ALL="C",
        TMPDIR=tmp,
        GCC_EXEC_PREFIX=GCC_DIR + "/",
        COMPILER_PATH=GCC_DIR,
    )
    env["PATH"] = (
        f"{GCC_DIR}:{ROOT}/toolchains/psn00b_toolchain/bin:{env.get('PATH', '')}"
    )
    stderr = os.dup(2)
    try:
        if empty:
            os.dup2(os.open(os.devnull, os.O_WRONLY), 2)
        status = compile_one(plan, env, tmp, build_dir)
    finally:
        os.dup2(stderr, 2)
        shutil.rmtree(tmp)
    if status and empty:
        open(plan["output"], "wb").close()
        print(
            f"cc: draft {plan['source']} does not compile; counted as unmatched",
            file=sys.stderr,
        )
        return 0
    return status


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
