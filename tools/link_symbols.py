#!/usr/bin/env python3
"""Write the link script that gives one image's undefined names their addresses.

Usage: tools/link_symbols.py --root ROOT --build-dir DIR --target ID --output FILE
       tools/link_symbols.py ... --partial OBJECT
       tools/link_symbols.py --root ROOT --build-dir DIR --all TARGET...
       tools/link_symbols.py --root ROOT --target ID --explain MAP

``--partial`` resolves one object for ``tools/match.sh``: a name with no address is left to the
partial link, which reports it.

Reads the image's link script, its objects and the symbol maps it may use
(``build/ld/<image>.maps``, written by tools/split.py from ``config/symbols/<image>.toml``). It writes

- ``PROVIDE(name = address);`` for each name that no object and no other link script defines;
  a name that cannot be resolved for certain fails with the row and the fix;
- ``ASSERT(name == address, ...);`` for each row of the image's own table that its objects
  define, so the linker proves the row against the address the image gave the symbol.

``--explain`` runs after a failed link and names both addresses for each row the map shows
elsewhere.
"""

from __future__ import annotations

import hashlib
import json
import os
import sys
from pathlib import Path

from bof3.core.paths import ASM, BUILD
from bof3.link import symbols
from bof3.link.inputs import parse, write_if_changed

#: Build-directory file that records what each image's script was made from.
CACHE = "syms.cache"


def image_text(root: Path, build: Path, target: str, partial: str | None = None) -> str:
    """Return the symbol script of one image; a name that cannot be resolved is a LinkError."""
    flat = target.replace("/", "+")
    scripts = [
        root / BUILD / "ld" / f"{flat}.ld",
        root / BUILD / ASM / target / "undefined_syms_auto.txt",
        root / BUILD / ASM / target / "undefined_funcs_auto.txt",
    ]
    texts = [path.read_text(encoding="utf-8") for path in scripts]
    if partial is not None:
        objects = [partial]
        texts = texts[1:]
    else:
        objects = _objects(build, texts[0])
    maps = (root / BUILD / "ld" / f"{flat}.maps").read_text(encoding="utf-8").split()
    names, assigned = symbols.script_symbols(texts)
    scan = symbols.scan_objects(root / "bin/internal/binutils/nm", objects)
    found = symbols.resolve(
        root, target, maps, scan, names, assigned, partial=partial is not None
    )
    checks = (
        []
        if partial is not None
        else symbols.own_checks(root, target, maps, scan.defined)
    )
    return symbols.render(found, checks)


def _objects(build: Path, link_script: str) -> list[str]:
    root = str(build)
    return [
        path if path.startswith("/") else f"{root}/{path}"
        for path in dict.fromkeys(entry.path for entry in parse(link_script))
    ]


def _stamp(root: Path, build: Path, target: str) -> str:
    """Return a digest of the files that decide one image's script, by size and mtime."""
    flat = target.replace("/", "+")
    top = str(root)
    ld = f"{top}/{BUILD}/ld"
    asm = f"{top}/{BUILD}/{ASM}/{target}"
    with open(f"{ld}/{flat}.ld", encoding="utf-8") as stream:
        objects = _objects(build, stream.read())
    with open(f"{ld}/{flat}.maps", encoding="utf-8") as stream:
        maps = [f"{top}/{name}" for name in stream.read().split()]
    paths = [
        f"{ld}/{flat}.ld",
        f"{ld}/{flat}.maps",
        f"{asm}/undefined_syms_auto.txt",
        f"{asm}/undefined_funcs_auto.txt",
        f"{top}/config/link.toml",
        f"{top}/config/{target}/splat.yaml",
        __file__,
        symbols.__file__,
        parse.__code__.co_filename,
        *maps,
        *objects,
    ]
    digest = hashlib.sha1()
    for path in paths:
        try:
            info = os.stat(path)
            digest.update(f"{info.st_mtime_ns}:{info.st_size};".encode())
        except OSError:
            digest.update(b"-;")
    return digest.hexdigest()


def _job(job: tuple[str, str, str]) -> tuple[str, str, str]:
    """Resolve one image; return its target, stamp and script (an error becomes ``ASSERT(0)``)."""
    root, build, target = job
    stamp = _stamp(Path(root), Path(build), target)
    try:
        text = image_text(Path(root), Path(build), target)
    except symbols.LinkError as error:
        lines = [line.strip().replace('"', "'") for line in str(error).splitlines()]
        text = "".join(
            f'ASSERT(0, "link_symbols: {line}");\n' for line in lines if line
        )
    return target, stamp, text


def build_all(root: Path, build: Path, targets: list[str]) -> int:
    """Write ``<image>.syms.ld`` into ``build`` for each target whose inputs changed.

    One process handles every image, so a build starts no Python per image; a stamp per
    image skips what did not change. An image that cannot be resolved gets a script of
    ``ASSERT(0, ...)`` lines, so its own link fails with the message and no other image waits.
    """
    from concurrent.futures import ProcessPoolExecutor
    from multiprocessing import get_context

    cache_path = build / CACHE
    try:
        cache = json.loads(cache_path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        cache = {}
    jobs = []
    for target in targets:
        flat = target.replace("/", "+")
        if (
            cache.get(target) != _stamp(root, build, target)
            or not (build / f"{flat}.syms.ld").is_file()
        ):
            jobs.append((str(root), str(build), target))
    if jobs:
        workers = min(len(jobs), os.cpu_count() or 1)
        with ProcessPoolExecutor(workers, mp_context=get_context("fork")) as pool:
            for target, stamp, text in pool.map(_job, jobs, chunksize=4):
                write_if_changed(build / f"{target.replace('/', '+')}.syms.ld", text)
                cache[target] = stamp
        write_if_changed(cache_path, json.dumps(cache, sort_keys=True))
    return 0


def explain(flags: dict[str, str]) -> int:
    """Name each row the failed link of --target placed elsewhere (--explain MAP)."""
    messages = symbols.explain(
        Path(flags["--root"]), flags["--target"], Path(flags["--explain"])
    )
    for message in messages:
        sys.stderr.write(f"link_symbols: {message}\n")
    return 0


def main() -> int:
    """Resolve every image (``--all``) or one (``--target``, with ``--output``)."""
    argv = sys.argv[1:]
    if not argv or argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0 if argv else 2
    if "--all" in argv:
        split = argv.index("--all")
        flags = dict(zip(argv[:split:2], argv[1:split:2], strict=False))
        return build_all(
            Path(flags["--root"]), Path(flags["--build-dir"]), argv[split + 1 :]
        )
    flags = dict(zip(argv[::2], argv[1::2], strict=False))
    if "--explain" in flags:
        return explain(flags)
    missing = [
        f for f in ("--root", "--build-dir", "--target", "--output") if f not in flags
    ]
    if missing:
        sys.stderr.write(f"{__doc__.splitlines()[2]}\nmissing {', '.join(missing)}\n")
        return 2
    try:
        text = image_text(
            Path(flags["--root"]),
            Path(flags["--build-dir"]),
            flags["--target"],
            flags.get("--partial"),
        )
    except symbols.LinkError as error:
        sys.stderr.write(f"link_symbols: {error}\n")
        return 1
    write_if_changed(Path(flags["--output"]), text)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
