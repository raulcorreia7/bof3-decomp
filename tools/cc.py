#!/usr/bin/env python3
"""Compile one C file the way the retail build did: GCC 2.7.2 PSX, maspsx, DMPSX, GNU as.

    cc.py [--build-dir DIR] [--empty-on-failure] GCC_ARGUMENT... -c SOURCE -o OBJECT
    cc.py --prune | --stats

The arguments are GCC's. `-Wa,--aspsx-version=V` and `-Wa,--expand-div` go to maspsx and
every other `-Wa,` item to the assembler. `-MMD -MP -MF FILE` writes a depfile that also
names the split assembly that `INCLUDE_ASM` pulls in. A source under `src/` also gets
`-I<its folder>` and, unless the arguments give one, `-DASM_DIR` for its image.

--build-dir DIR     resolve -o and -MF against DIR, run from the repository root and write
                    depfile paths relative to DIR (Meson and Ninja)
--empty-on-failure  hide the compiler's output; a source that does not compile leaves an
                    empty object and succeeds (draft objects for the report)
--prune             remove stray files, then the least recently used entries until the cache
                    is within its bounds, and print what went
--stats             print the cache's entries, bytes and inodes

Objects are cached in ~/.cache/bof3-cc/<first two key digits>/<key>.obj, one file per key that
holds the dependency paths and the object (BOF3_CC_CACHE_DIR moves it), keyed on the
preprocessed source, the arguments and the hashes of GCC, maspsx, DMPSX and the assembler, so
every worktree shares them; the first compiler of a key writes it and the rest wait on a lock
file that is deleted when the compile ends. BOF3_CC_CACHE=0 turns the cache off; scratch
measurements (`MATCH_SRC`, the permuter) set it, so one-off variants never enter the cache.

The cache holds at most BOF3_CC_MAX_ENTRIES entries (default 30000) and BOF3_CC_MAX_BYTES
bytes (default 256 MiB); a full build of every image is 7,300 entries and 46 MB. One write in
500 prunes it, for at most a few seconds; `--prune` does the whole job by hand.

PSX_GCC=<path> picks the compiler binary. Run it as a script: `python -m` would put the
working directory, a build directory that changes with every object, on the import path.
"""

import concurrent.futures
import contextlib
import fcntl
import glob
import hashlib
import os
import random
import re
import shutil
import subprocess
import sys
import tempfile
import time

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
MAX_ENTRIES = int(os.environ.get("BOF3_CC_MAX_ENTRIES") or 30000)
MAX_BYTES = int(os.environ.get("BOF3_CC_MAX_BYTES") or 256 << 20)
#: One cache write in this many prunes the cache, for at most PRUNE_SECONDS.
PRUNE_ONE_IN = 500
PRUNE_SECONDS = 3.0
#: A lock or temporary file this old (seconds) belongs to a compile that died.
STALE = 3600
#: A cache entry's file name: the key, with `.obj` in the object folders.
ENTRY = re.compile(r"[0-9a-f]{40}(\.obj)?$")


def _read_literal(text: str, i: int, joined: list[str]) -> tuple[int, bool]:
    """Append the characters of a string literal; return where it ends and whether it closed."""
    while i < len(text):
        char = text[i]
        if char == "\\" and i + 1 < len(text):
            joined.append(text[i + 1])
            i += 2
        elif char == '"':
            return i + 1, True
        else:
            joined.append(char)
            i += 1
    return i, False


def _skip_to_literal(text: str, i: int) -> int | None:
    """Return the index past the next adjacent literal's opening quote, or None."""
    while i < len(text) and text[i] in " \t\r\n":
        i += 1
    if i >= len(text) or text[i] != '"':
        return None
    return i + 1


def _include_name(text: str, i: int) -> str | None:
    """Join the adjacent string literals from ``i`` into one quoted path, or None."""
    joined: list[str] = []
    first = True
    while i < len(text):
        if not first:
            i = _skip_to_literal(text, i)
            if i is None:
                return None
        first = False
        i, closed = _read_literal(text, i, joined)
        value = "".join(joined)
        if len(value) >= 2 and value[0] == '"' and '"' in value[1:]:
            return value[1 : value.index('"', 1)]
        if not closed:
            return None
    return None


def inline_includes(text: str) -> list[str]:
    """Return the file names of the assembler includes in preprocessed C text."""
    names = (_include_name(text, m.end()) for m in INLINE_INCLUDE.finditer(text))
    return [name for name in names if name is not None]


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
    """Run maspsx's command line in this process; return its output, or None when it fails."""
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


def _translate(plan: dict, asm: str) -> str | None:
    """Return the assembly after maspsx and the placeholder rewrite, or None on failure."""
    masp = [f"--aspsx-version={plan['version']}"]
    if plan["div"]:
        masp.append("--expand-div")
    with open(asm, "rb") as fin:
        text = maspsx(masp, fin.read().decode("utf-8"))
    if text is None:
        return None
    from psxdecomp.dmpsx import UnknownPlaceholder, rewrite_text

    try:
        return rewrite_text(text)[0]
    except UnknownPlaceholder as exc:
        print(f"cc: {plan['source']}: {exc}", file=sys.stderr)
        return None


def _dependencies(plan: dict, gcc_args: list, env: dict, asm: str) -> list[str] | None:
    """Return the headers and split assembly the source includes, or None on failure."""
    scan = run(
        [GCC, "-MM", *gcc_args, plan["source"]],
        env=env,
        stdout=subprocess.PIPE,
        text=True,
    )
    if scan.returncode:
        return None
    deps = scan.stdout.split(":", 1)[1].replace("\\\n", " ").split()
    with open(asm, encoding="utf-8", errors="replace") as handle:
        deps += ASM_INCLUDE.findall(handle.read())
    return deps


def compile_one(plan, gcc_args, env, tmp):
    """Run the four stages; return the exit status and the dependency paths."""
    source, output = plan["source"], plan["output"]
    os.makedirs(os.path.dirname(output) or ".", exist_ok=True)
    asm = f"{tmp}/cc1.s"
    if run([GCC, *gcc_args, "-S", "-o", asm, source], env=env).returncode:
        return 1, None
    text = _translate(plan, asm)
    if text is None:
        return 1, None
    translated = f"{tmp}/masp.s"
    with open(translated, "w", encoding="utf-8") as out:
        out.write(text)
    if run([AS, *plan["as"], "-o", output, translated]).returncode:
        return 1, None
    if not plan["depfile"]:
        return 0, None
    deps = _dependencies(plan, gcc_args, env, asm)
    if deps is None:
        return 1, None
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
    """Return the cache key of a compile, or None when the cache cannot vouch for it."""
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
    """Copy the cached object to the output and rewrite the depfile; false on a miss."""
    try:
        with open(stored, "rb") as handle:
            head, data = handle.read().split(b"\n", 1)
        size = int(head)
    except (FileNotFoundError, ValueError):
        return False
    os.makedirs(os.path.dirname(plan["output"]) or ".", exist_ok=True)
    with open(plan["output"], "wb") as out:
        out.write(data[size:])
    if plan["depfile"]:
        write_depfile(plan, data[:size].decode().splitlines(), build_dir)
    with contextlib.suppress(OSError):
        os.utime(stored)  # the prune evicts the entry used longest ago
    return True


def store_cached(stored, plan, deps):
    """Write the dependency paths and the object into one cache file; a later writer replaces it."""
    text = "".join(f"{dep}\n" for dep in deps or []).encode()
    with open(plan["output"], "rb") as handle:
        data = b"%d\n" % len(text) + text + handle.read()
    temp = f"{stored}.{os.getpid()}.tmp"
    with open(temp, "wb") as out:
        out.write(data)
    os.replace(temp, stored)


@contextlib.contextmanager
def locked(path):
    """Hold an exclusive lock on a file that is deleted when the block ends.

    A waiter that gets the lock after the holder deleted the file opens the new one."""
    while True:
        handle = open(path, "a", encoding="utf-8")
        fcntl.flock(handle, fcntl.LOCK_EX)
        with contextlib.suppress(FileNotFoundError):
            if os.fstat(handle.fileno()).st_ino == os.stat(path).st_ino:
                break
        handle.close()
    try:
        yield
    finally:
        with contextlib.suppress(FileNotFoundError):
            os.unlink(path)
        handle.close()


def cached_compile(plan, gcc_args, env, tmp, build_dir):
    """Compile through the shared object cache; return the exit status."""
    key = None
    if os.environ.get("BOF3_CC_CACHE") != "0":
        key = cache_key(plan, gcc_args, env)
    if key is None:
        status, deps = compile_one(plan, gcc_args, env, tmp)
        if status == 0 and plan["depfile"]:
            write_depfile(plan, deps, build_dir)
        return status
    # One subdirectory per two hex digits: a flat directory of millions of entries fills ext4's index.
    folder = os.path.join(CACHE_DIR, key[:2])
    stored = os.path.join(folder, f"{key}.obj")
    if take_cached(plan, stored, build_dir):
        return 0
    os.makedirs(folder, exist_ok=True)
    with locked(os.path.join(folder, f"{key}.lock")):
        if take_cached(plan, stored, build_dir):
            return 0
        status, deps = compile_one(plan, gcc_args, env, tmp)
        if status == 0:
            store_cached(stored, plan, deps)
            if plan["depfile"]:
                write_depfile(plan, deps, build_dir)
    if status == 0 and random.randrange(PRUNE_ONE_IN) == 0:
        with contextlib.suppress(OSError):
            prune(time.monotonic() + PRUNE_SECONDS)
    return status


def _folders():
    """Return the cache's top folder, its two-digit object folders and the `plain` folder."""
    objects, plain = [], None
    with contextlib.suppress(FileNotFoundError), os.scandir(CACHE_DIR) as items:
        for item in items:
            if item.is_dir() and re.fullmatch(r"[0-9a-f]{2}", item.name):
                objects.append(item.path)
            elif item.is_dir() and item.name == "plain":
                plain = item.path
    return objects, plain


def _scan(folder, deadline):
    """Return a folder's entries as (mtime, bytes, path), the strays deleted and whether it ended.

    A file is stray when it is not an entry: an object or depfile of the old two-file layout,
    or a lock or temporary file older than STALE."""
    entries, strays, now = [], 0, time.time()
    with os.scandir(folder) as items:
        for item in items:
            if time.monotonic() > deadline:
                return entries, strays, False
            if item.name.startswith(".") or item.is_dir():
                continue
            if ENTRY.match(item.name):
                info = item.stat()
                entries.append((info.st_mtime, info.st_size, item.path))
            elif not item.name.endswith((".lock", ".tmp")) or (
                now - item.stat().st_mtime > STALE
            ):
                with contextlib.suppress(FileNotFoundError):
                    os.unlink(item.path)
                strays += 1
    return entries, strays, True


def _evict(entries, max_entries, max_bytes):
    """Delete the least recently used entries down to 90% of the bounds; return (count, bytes)."""
    count, size = len(entries), sum(entry[1] for entry in entries)
    removed = freed = 0
    if count > max_entries or size > max_bytes:
        for _, length, path in sorted(entries):
            if count <= max_entries * 0.9 and size <= max_bytes * 0.9:
                break
            with contextlib.suppress(FileNotFoundError):
                os.unlink(path)
            count, size = count - 1, size - length
            removed, freed = removed + 1, freed + length
    return removed, freed


def prune(deadline=float("inf")):
    """Remove stray files and the least recently used entries beyond the bounds.

    Stops early at the deadline, and evicts only after a complete scan. One prune runs at a
    time. Returns what it removed."""
    os.makedirs(CACHE_DIR, exist_ok=True)
    with open(os.path.join(CACHE_DIR, ".prune"), "a", encoding="utf-8") as lock:
        try:
            fcntl.flock(lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            return "another prune is running"
        objects, plain = _folders()
        folders = [CACHE_DIR, *objects, *([plain] if plain else [])]
        with concurrent.futures.ThreadPoolExecutor(8) as pool:
            scans = list(pool.map(lambda f: _scan(f, deadline), folders))
        strays = sum(scan[1] for scan in scans)
        removed = freed = 0
        if all(scan[2] for scan in scans):
            groups = [(scans[: len(objects) + 1], MAX_BYTES)]
            if plain:
                groups.append((scans[-1:], 1 << 62))
            for group, max_bytes in groups:
                entries = [entry for scan in group for entry in scan[0]]
                count, size = _evict(entries, MAX_ENTRIES, max_bytes)
                removed, freed = removed + count, freed + size
        done = "" if all(scan[2] for scan in scans) else " (stopped at the deadline)"
        return (
            f"removed {strays} stray files and {removed} entries ({freed} bytes){done}"
        )


def stats():
    """Return the cache's entries, bytes and inodes (every file and folder in it)."""
    objects, plain = _folders()
    entries = size = keys = inodes = 0
    for folder in [CACHE_DIR, *objects, *([plain] if plain else [])]:
        with os.scandir(folder) as items:
            for item in items:
                inodes += 1
                if folder == plain:
                    keys += 1
                elif ENTRY.match(item.name):
                    entries, size = entries + 1, size + item.stat().st_size
    return f"{entries} entries, {size} bytes, {keys} plain keys, {inodes} inodes in {CACHE_DIR}"


def compiler_env(tmp: str) -> dict[str, str]:
    """Return the environment that makes GCC find its stages and the SDK tools."""
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
    return env


def main(argv):
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0 if argv else 2
    if argv in (["--prune"], ["--stats"]):
        print(prune() if argv[0] == "--prune" else stats())
        return 0
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
    env = compiler_env(tmp)
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
