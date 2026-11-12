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

Objects are cached in ~/.cache/bof3-cc (BOF3_CC_CACHE_DIR moves it), keyed on the preprocessed
source, the arguments and the hashes of GCC, maspsx, DMPSX and the assembler, so every worktree
shares them; the first compiler of a key writes it and the rest wait for its object.
BOF3_CC_CACHE=0 turns the cache off.

PSX_GCC=<path> picks the compiler binary. Run it as a script: `python -m` would put the
working directory, a build directory that changes with every object, on the import path.
"""

import fcntl
import glob
import hashlib
import os
import re
import shutil
import subprocess
import sys
import tempfile

from bof3.resolve.ids import asm_dir

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
GCC = os.environ.get("PSX_GCC") or f"{ROOT}/toolchains/gcc-2.7.2-psx/gcc"
GCC_DIR = os.path.dirname(os.path.realpath(GCC))
AS = f"{ROOT}/bin/internal/binutils/as"
MASPSX = f"{ROOT}/third_party/maspsx/maspsx.py"
#: INCLUDE_ASM pulls split assembly in through the assembler, which `gcc -MM` cannot see.
ASM_INCLUDE = re.compile(r'^\s*\.include "([^"]+/[^"]+\.s)"', re.M)
#: An assembler include statement in the preprocessed C text; its path may be split across
#: adjacent string literals by the INCLUDE_ASM macro, so the path is joined by _inline_includes.
INLINE_INCLUDE = re.compile(r"\.(?:include|incbin)\s+")
CACHE_DIR = os.environ.get("BOF3_CC_CACHE_DIR") or os.path.expanduser(
    "~/.cache/bof3-cc"
)


def inline_includes(text: str) -> list[str]:
    """Return the file names of the assembler includes in preprocessed C text.

    A plain ``__asm__(".include \\"x.s\\"")`` reaches the preprocessed text as one string
    literal; ``INCLUDE_ASM`` concatenates the assembly folder, the function name and ``.s``
    into adjacent literals. Both spellings join back into one quoted path here.
    """
    names = []
    for match in INLINE_INCLUDE.finditer(text):
        i = match.end()
        joined: list[str] = []
        first = True
        while i < len(text):
            if not first:
                while i < len(text) and text[i] in " \t\r\n":
                    i += 1
                if i >= len(text) or text[i] != '"':
                    break
                i += 1
            first = False
            closed = False
            while i < len(text):
                char = text[i]
                if char == "\\" and i + 1 < len(text):
                    joined.append(text[i + 1])
                    i += 2
                elif char == '"':
                    i += 1
                    closed = True
                    break
                else:
                    joined.append(char)
                    i += 1
            value = "".join(joined)
            if len(value) >= 2 and value[0] == '"' and '"' in value[1:]:
                names.append(value[1 : value.index('"', 1)])
                break
            if not closed:
                break
    return names


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


def gcc_arguments(plan):
    """Return GCC's arguments for the source: the plan's plus its folder and `ASM_DIR`."""
    source, gcc_args = plan["source"], plan["gcc"]
    if not any(a.startswith("-DASM_DIR=") for a in gcc_args):
        directory = asm_dir(source, ROOT)
        if directory:
            gcc_args = [*gcc_args, f'-DASM_DIR="{directory}"']
    if os.path.relpath(os.path.abspath(source), ROOT).startswith("src" + os.sep):
        gcc_args = [*gcc_args, f"-I{os.path.dirname(source)}"]
    return gcc_args


def compile_one(plan, gcc_args, env, tmp):
    """Run the four stages; return the exit status and the dependency paths."""
    source, output = plan["source"], plan["output"]
    os.makedirs(os.path.dirname(output) or ".", exist_ok=True)
    asm = f"{tmp}/cc1.s"
    if run([GCC, *gcc_args, "-S", "-o", asm, source], env=env).returncode:
        return 1, None
    masp = [f"--aspsx-version={plan['version']}"]
    if plan["div"]:
        masp.append("--expand-div")
    with open(asm, "rb") as fin:
        text = maspsx(masp, fin.read().decode("utf-8"))
    if text is None:
        return 1, None
    from psxdecomp.dmpsx import UnknownPlaceholder, rewrite_text

    try:
        text = rewrite_text(text)[0]
    except UnknownPlaceholder as exc:
        print(f"cc: {source}: {exc}", file=sys.stderr)
        return 1, None
    translated = f"{tmp}/masp.s"
    with open(translated, "w", encoding="utf-8") as out:
        out.write(text)
    if run([AS, *plan["as"], "-o", output, translated]).returncode:
        return 1, None
    if not plan["depfile"]:
        return 0, None
    scan = run(
        [GCC, "-MM", *gcc_args, source], env=env, stdout=subprocess.PIPE, text=True
    )
    if scan.returncode:
        return 1, None
    deps = scan.stdout.split(":", 1)[1].replace("\\\n", " ").split()
    with open(asm, encoding="utf-8", errors="replace") as handle:
        deps += ASM_INCLUDE.findall(handle.read())
    return 0, deps


def write_depfile(plan, deps, build_dir):
    """Write the Make depfile for the object from its dependency paths."""
    target = plan["output"]
    if build_dir:
        deps = [os.path.relpath(path, build_dir) for path in deps]
        target = os.path.relpath(target, build_dir)
    lines = [f"{target}: {' '.join(deps)}\n"]
    if plan["phony"]:
        lines += [f"{dep}:\n" for dep in deps[1:]]
    with open(plan["depfile"], "w", encoding="utf-8") as out:
        out.write("".join(lines))


def file_hash(path):
    """Return the SHA-1 of a file."""
    with open(path, "rb") as handle:
        return hashlib.sha1(handle.read()).hexdigest()


def tool_hashes():
    """Return the hashes of every program and script that shapes an object."""
    real_as = (
        os.environ.get("PSX_AS")
        or f"{ROOT}/toolchains/psn00b_toolchain/bin/mipsel-none-elf-as"
    )
    paths = [GCC, f"{GCC_DIR}/cc1", f"{GCC_DIR}/cpp", real_as, MASPSX, __file__]
    paths += sorted(glob.glob(f"{ROOT}/third_party/maspsx/maspsx/*.py"))
    paths += sorted(glob.glob(f"{ROOT}/tools/psxdecomp/*.py"))
    return [file_hash(path) for path in paths if os.path.isfile(path)]


def cache_key(plan, gcc_args, env):
    """Return the cache key of a compile, or None when the cache cannot vouch for it.

    The key covers the preprocessed source, the split assembly it includes, every argument but the
    output (the repository root written as `<root>`, so worktrees agree) and the tool hashes.
    """
    pre = run([GCC, *gcc_args, "-E", plan["source"]], env=env, stdout=subprocess.PIPE)
    if pre.returncode:
        return None
    text = pre.stdout
    search = [ROOT] + [item[2:] for item in plan["as"] if item.startswith("-I")]
    parts = [
        plan["version"],
        str(plan["div"]),
        plan["source"],
        *gcc_args,
        "--",
        *plan["as"],
    ]
    key = hashlib.sha1(text)
    for name in sorted(set(inline_includes(text.decode("utf-8", "replace")))):
        found = next(
            (f"{d}/{name}" for d in search if os.path.isfile(f"{d}/{name}")), None
        )
        if found is None:
            return None
        key.update(f"{name}\0{file_hash(found)}\0".encode())
    for part in [*parts, *tool_hashes()]:
        key.update(part.replace(ROOT, "<root>").encode() + b"\0")
    return key.hexdigest()


def take_cached(plan, stored, build_dir):
    """Copy the cached object and its depfile to the output; false when either is missing."""
    if not (os.path.isfile(f"{stored}.o") and os.path.isfile(f"{stored}.dep")):
        return False
    os.makedirs(os.path.dirname(plan["output"]) or ".", exist_ok=True)
    shutil.copyfile(f"{stored}.o", plan["output"])
    if plan["depfile"]:
        with open(f"{stored}.dep", encoding="utf-8") as handle:
            write_depfile(plan, handle.read().split("\n")[:-1], build_dir)
    return True


def store_cached(stored, plan, deps):
    """Write one object and its depfile into the cache; a later writer replaces both."""
    os.makedirs(CACHE_DIR, exist_ok=True)
    unique = f"{os.getpid()}.tmp"
    shutil.copyfile(plan["output"], f"{stored}.o{unique}")
    with open(f"{stored}.dep{unique}", "w", encoding="utf-8") as out:
        out.write("".join(f"{dep}\n" for dep in deps or []))
    os.replace(f"{stored}.dep{unique}", f"{stored}.dep")
    os.replace(f"{stored}.o{unique}", f"{stored}.o")


def cached_compile(plan, gcc_args, env, tmp, build_dir):
    """Compile through the shared object cache; return the exit status.

    A header change asks every worktree for the same keys at once. The first compiler of a key
    holds its lock file, writes the object and releases it; the others wait and take that object
    instead of compiling it again.
    """
    key = None
    if os.environ.get("BOF3_CC_CACHE") != "0":
        key = cache_key(plan, gcc_args, env)
    if key is None:
        status, deps = compile_one(plan, gcc_args, env, tmp)
        if status == 0 and plan["depfile"]:
            write_depfile(plan, deps, build_dir)
        return status
    stored = os.path.join(CACHE_DIR, key)
    if take_cached(plan, stored, build_dir):
        return 0
    os.makedirs(CACHE_DIR, exist_ok=True)
    with open(f"{stored}.lock", "a") as lock:
        fcntl.flock(lock, fcntl.LOCK_EX)
        if take_cached(plan, stored, build_dir):
            return 0
        status, deps = compile_one(plan, gcc_args, env, tmp)
        if status == 0:
            store_cached(stored, plan, deps)
            if plan["depfile"]:
                write_depfile(plan, deps, build_dir)
        return status


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
        status = cached_compile(plan, gcc_arguments(plan), env, tmp, build_dir)
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
