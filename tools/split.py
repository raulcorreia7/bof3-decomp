#!/usr/bin/env python3
"""Split stale targets with Splat, write each target's link script and print the build graph.

The link scripts go into ``build/ld``. The graph goes to stdout, one tab-separated row per line:

``dep PATH``                     a file the graph depends on, relative to the repository
``target ID SHA1 BINARY SCRIPT`` an image, its retail SHA-1, its payload and link script
``d NAME SOURCE ASM_DIR``        compile the draft SOURCE (it holds a NON_MATCHING function)
                                 to the object NAME, for the progress report
``c NAME SOURCE ASM_DIR``        compile SOURCE to the object NAME
``s NAME SOURCE``                assemble SOURCE
``b NAME SOURCE``                wrap the binary SOURCE
``m PATH``                       a symbol map the image's names may come from

Rows after a ``target`` row belong to it, in link order. The ``dep`` and ``d`` rows come first.
"""

from __future__ import annotations

import os
import re
import shutil
import sys
from concurrent.futures import ProcessPoolExecutor
from dataclasses import dataclass
from pathlib import Path

from bof3.core.io import repo_layout
from bof3.core.paths import BUILD, CONFIG
from bof3.link import graph, symbols
from bof3.link.inputs import write_if_changed
from bof3.link.script import prepare_link
from bof3.resolve import TargetManifest, load_target_manifests
from bof3.resolve.manifests import load_target_manifest
from bof3.status.claims import DRAFT_BYTES
from bof3.toolchain.splat import splat_output_current, split_target

#: Bounded so a split leaves cores free for the rest of the build.
WORKERS = 8

#: The files under ``config/`` that decide the graph: a target's layout and manifest, and the two
#: tables its link script resolves names against. The rest of ``config/`` is bookkeeping (attempts,
#: address names), the disc manifest or the SDK unit list, and none of it decides a row.
GRAPH_CONFIG = frozenset({"splat.yaml", "target.toml", "link.toml", "symbols.toml"})


def ensure_payload(root: Path, manifest: TargetManifest) -> Path:
    """Return the target's generated binary, deriving it from the disc when missing."""
    binary = root / manifest.binary
    if binary.is_file():
        return binary
    if manifest.kind == "executable":
        source = root / BUILD / "disc" / manifest.disc_id
    else:
        _, family, archive, slot = manifest.id.value.split("/")
        source = (
            root
            / BUILD
            / "disc"
            / "BIN"
            / family.upper()
            / archive.upper()
            / f"{int(slot)}.bin"
        )
    if not source.is_file():
        raise RuntimeError(f"missing retail payload {source}; run tools/setup.sh")
    binary.parent.mkdir(parents=True, exist_ok=True)
    shutil.copyfile(source, binary)
    return binary


@dataclass(frozen=True, slots=True)
class Done:
    """One target's split result."""

    re_split: int = 0
    error: str | None = None
    #: The target's graph rows.
    rows: tuple[str, ...] = ()
    #: Sources outside ``config`` that the target's link script depends on.
    sources: tuple[str, ...] = ()


def split_one(job: tuple[str, str]) -> Done:
    """Split one target in a worker and describe its graph."""
    root_s, target = job
    root = Path(root_s)
    manifest = load_target_manifest(
        root / CONFIG / target / "target.toml", root=root, target=target
    )
    ensure_payload(root, manifest)
    linker = root / BUILD / "asm" / target / "linker.ld"
    re_split = 0
    if not splat_output_current(root, target) or not linker.is_file():
        result = split_target(root, manifest.splat)
        if result.returncode:
            return Done(error=result.stdout + result.stderr)
        re_split = 1
    prepared = prepare_link(root, target)
    flat = target.replace("/", "+")
    script = Path(BUILD) / "ld" / f"{flat}.ld"
    write_if_changed(root / script, graph.link_script(root, prepared.text))
    sha1 = re.search(
        r"^sha1:\s*(\w+)", (root / manifest.splat).read_text(), re.MULTILINE
    )
    if sha1 is None:
        return Done(error=f"{manifest.splat}: no sha1")
    head = "\t".join(("target", target, sha1[1], manifest.binary, script.as_posix()))
    body = ("\t".join(row) for row in graph.rows(root, target, prepared.objects))
    maps = tuple(symbols.link_map(owner) for owner in symbols.link_owners(root, target))
    write_if_changed(
        root / BUILD / "ld" / f"{flat}.maps", "".join(f"{m}\n" for m in maps)
    )
    sources = tuple(path.relative_to(root).as_posix() for path in prepared.sources)
    return Done(
        re_split, rows=(head, *(f"m\t{m}" for m in maps), *body), sources=sources
    )


def graph_inputs(root: Path, sources: set[str]) -> list[str]:
    """List the files a graph depends on: the config, the Python that wrote it, and ``sources``."""
    files = {
        path.relative_to(root).as_posix()
        for path in (root / CONFIG).rglob("*")
        if path.is_file() and path.name in GRAPH_CONFIG
    }
    for module in list(sys.modules.values()):
        path = getattr(module, "__file__", None)
        if path and Path(path).is_relative_to(root / "tools"):
            files.add(Path(path).relative_to(root).as_posix())
    files.add(Path(__file__).resolve().relative_to(root).as_posix())
    return sorted(files | sources)


def run_jobs(jobs: list[tuple[str, str]]) -> list[Done]:
    """Split the jobs, in parallel when there are several."""
    if len(jobs) == 1:
        return [split_one(jobs[0])]
    workers = min(WORKERS, len(os.sched_getaffinity(0)))
    with ProcessPoolExecutor(max_workers=workers) as pool:
        return list(pool.map(split_one, jobs, chunksize=8))


def draft_rows(root: Path, rows: list[str]) -> list[str]:
    """Return a ``d`` row for each compiled source that holds a draft function."""
    result = []
    for row in rows:
        fields = row.split("\t")
        if fields[0] == "c" and DRAFT_BYTES.search((root / fields[2]).read_bytes()):
            name = graph.source_object(Path(fields[2]).relative_to("src"), draft=True)
            result.append("\t".join(("d", name, fields[2], fields[3])))
    return result


def main() -> int:
    """Split every stale target and print the Meson graph."""
    if sys.argv[1:] in (["-h"], ["--help"]):
        print(__doc__.strip())
        return 0
    root = repo_layout().root
    try:
        symbols.generate(root)
    except symbols.LinkError as error:
        sys.stderr.write(f"split: {error}\n")
        return 2
    selected = load_target_manifests(root)
    jobs = [(str(root), target) for target in selected]
    done = run_jobs(jobs)
    for item in done:
        if item.error is not None:
            sys.stderr.write(item.error)
            return 2
    seen: set[str] = set()
    for item in done:
        for row in item.rows:
            fields = row.split("\t")
            if fields[0] in "csb":
                if fields[1] in seen:
                    sys.stderr.write(f"split: object {fields[1]} is in two images\n")
                    return 2
                seen.add(fields[1])
    sources = {path for item in done for path in item.sources}
    lines = [f"dep\t{path}" for path in graph_inputs(root, sources)]
    lines += draft_rows(root, [row for item in done for row in item.rows])
    lines += (row for item in done for row in item.rows)
    sys.stdout.write("\n".join(lines) + "\n")
    sys.stderr.write(
        f"split: {len(done)} target(s), {sum(item.re_split for item in done)} re-split\n"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
