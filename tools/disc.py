#!/usr/bin/env python3
"""Write or check the disc manifest ``config/disc.toml``.

  disc.py manifest   write the manifest from a disc dump and its extracted files
  disc.py verify     check the dump, the extracted files and the code images against it
  disc.py rebuild    build every archive from the built images, patch the disc, check it

The manifest lists the version, the CUE sheet, both tracks and every ISO 9660 file with its
size and hashes. ``tools/setup.py`` runs the same checks and names each file that differs.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

from bof3.adapters.cli import run_main
from bof3.core import disc
from bof3.core.paths import ROOT

SERIAL = re.compile(r"cdrom:\\?([A-Z]{4})_(\d{3})\.(\d{2})", re.I)
REGIONS = {
    "SLUS": "NTSC-U",
    "SCUS": "NTSC-U",
    "SLES": "PAL",
    "SCES": "PAL",
    "SLPS": "NTSC-J",
}


def _find_cue(given: str | None) -> tuple[Path, list[Path]]:
    if given:
        cue = Path(given)
        found = disc.disc_set(cue.parent) if cue.is_file() else None
        if found is None or found[0].resolve() != cue.resolve():
            sys.exit(f"disc: {given} is not a complete cue/bin set")
        return found
    found = disc.disc_set(ROOT / disc.MEDIA)
    if found is None:
        sys.exit(f"disc: no cue/bin set under {disc.MEDIA}; pass --cue")
    return found


def _tracks(cue: Path) -> list[tuple[int, str]]:
    """Return ``(number, type)`` for each TRACK line of the cue sheet."""
    text = cue.read_text(encoding="utf-8", errors="ignore")
    return [
        (int(n), kind.upper())
        for n, kind in re.findall(r"^\s*TRACK\s+(\d+)\s+(\S+)", text, re.M)
    ]


def manifest(args: argparse.Namespace) -> int:
    """Hash the dump and the extracted files, then write the manifest."""
    cue, bins = _find_cue(args.cue)
    folder = ROOT / disc.EXTRACTED
    project = next(iter(sorted(folder.glob("*.xml"))), None)
    if project is None or not (folder / "SYSTEM.CNF").is_file():
        sys.exit(f"disc: {folder} is not an extracted disc; run tools/setup.sh first")
    serial = SERIAL.search((folder / "SYSTEM.CNF").read_text(errors="ignore"))
    if serial is None:
        sys.exit("disc: SYSTEM.CNF has no BOOT line")
    prefix = serial[1].upper()
    with tempfile.TemporaryDirectory() as temp:
        table = Path(temp) / "lba.json"
        subprocess.run(
            ["bof3", "disc", "lba-json", "-q", "-i", str(cue), "-o", str(table),
             "-x", str(folder), "-p", str(project)],
            check=True,
        )  # fmt: skip
        entries = json.loads(table.read_text())["entries"]
    files = []
    for entry in sorted(entries, key=lambda item: item["lba"]):
        path = Path(entry["source_path"]).resolve().relative_to(folder.resolve())
        got = disc.digest_file(folder / path)
        files.append((path.as_posix(), entry["lba"], got.size, got.sha1))
    text = disc.render(
        title="Breath of Fire III",
        region=REGIONS.get(prefix, prefix),
        serial=f"{prefix}-{serial[2]}{serial[3]}",
        redump=cue.stem,
        cue=(cue.name, disc.digest_file(cue)),
        tracks=[
            (number, path.name, kind, disc.digest_file(path))
            for (number, kind), path in zip(_tracks(cue), bins, strict=True)
        ],
        files=files,
    )
    Path(args.output).write_text(text)
    print(f"disc: wrote {args.output} ({len(files)} files, {len(bins)} tracks)")
    return 0


def verify(args: argparse.Namespace) -> int:
    """Report every mismatch by path; exit 1 when there is one."""
    data = disc.load_manifest(ROOT)
    problems = []
    found = disc.disc_set(ROOT / disc.MEDIA)
    if found is None:
        print("disc: no cue/bin set; skipped the tracks")
    else:
        problems += disc.verify_tracks(data, found[1])
    folder = ROOT / disc.EXTRACTED
    if (folder / "SYSTEM.CNF").is_file():
        problems += disc.verify_files(data, folder)
    else:
        print(f"disc: {disc.EXTRACTED} is not extracted; skipped the files")
    if not args.no_images:
        problems += disc.verify_images(ROOT)
    for line in problems:
        print(f"disc: {line}", file=sys.stderr)
    if problems:
        print(f"disc: {len(problems)} mismatch(es)", file=sys.stderr)
        return 1
    print(
        f"disc: {len(data['iso']['files'])} files and {len(data['disc']['tracks'])} tracks match"
    )
    return 0


def _cli() -> str:
    """Return the ``bof3`` command: ``BOF3_CLI``, the setup build, or the tools checkout."""
    for found in (
        os.environ.get("BOF3_CLI"),
        ROOT / "build/rust/release/bof3",
        ROOT / "tools/bof3-tools/bin/bof3",
    ):
        if found and shutil.which(found):
            return str(found)
    sys.exit("disc: no bof3 command; run tools/setup.sh or set BOF3_CLI")


def rebuild(args: argparse.Namespace) -> int:
    """Rebuild the disc from the built images and compare it with the manifest."""
    from bof3.resolve import load_target_manifests

    data = disc.load_manifest(ROOT)
    found = disc.disc_set(ROOT / disc.MEDIA)
    if found is None:
        sys.exit("disc: no cue/bin set; the rebuild patches a copy of your disc")
    cli = _cli()
    out = ROOT / args.output
    shutil.rmtree(out, ignore_errors=True)
    built: dict[
        str, Path
    ] = {}  # disc id -> the built image (a copy row shares its target's)
    for target, manifest in load_target_manifests(ROOT).items():
        image = ROOT / "build/meson" / (target.replace("/", "+") + ".bin")
        if not image.is_file():
            sys.exit(f"disc: {image.relative_to(ROOT)} is missing; run meson compile")
        built[manifest.disc_id] = image
        built.update({copy.disc_id: image for copy in manifest.copies})
    files = []
    for entry in data["iso"]["files"]:
        path = entry["path"]
        if not path.endswith(".EMI"):
            if path in built:
                files.append(f"{path}={built[path]}")
            continue
        folder = ROOT / disc.EXTRACTED / path.removesuffix(".EMI")
        stage = out / "stage"
        stage.mkdir(parents=True, exist_ok=True)
        for item in json.loads((folder / "emi.json").read_text())["entries"]:
            source = built.get(f"{path}#{item['index']}", folder / item["name"])
            shutil.copyfile(source, stage / item["name"])
        shutil.copyfile(folder / "emi.json", stage / "emi.json")
        archive = out / "emi" / path
        archive.parent.mkdir(parents=True, exist_ok=True)
        subprocess.run(
            [cli, "emi", "pack", "-q", "-J", stage / "emi.json", "-o", archive, stage],
            check=True,
        )  # fmt: skip
        files.append(f"{path}={archive}")
    shutil.rmtree(out / "stage")
    patched = out / "disc"
    subprocess.run(
        [cli, "assets", "import", "disc", found[0], "-o", patched]
        + [arg for file in files for arg in ("--file", file)],
        check=True,
    )  # fmt: skip
    cue = data["disc"]["cue"]
    bins = sorted(patched.glob("*.bin"))
    problems = disc.verify_tracks(data, bins)
    for want, path in zip(data["disc"]["tracks"], bins, strict=False):
        got = disc.file_digest(path, "sha1")
        print(f"disc: track {want['number']} SHA-1 {got}, retail {want['sha1']}")
    if disc.file_digest(patched / cue["name"], "sha1") != cue["sha1"]:
        problems.append(f"{cue['name']}: SHA-1 differs")
    extracted = out / "files"
    subprocess.run(
        [cli, "disc", "extract", "-i", patched / cue["name"], "-o", extracted],
        check=True,
    )  # fmt: skip
    problems += disc.verify_files(data, extracted)
    for line in problems:
        print(f"disc: {line}")
    if problems:
        print(f"disc: {len(problems)} mismatch(es)")
        return 1
    print(f"disc: all {len(data['iso']['files'])} files and both tracks match")
    return 0


def main(argv: list[str] | None = None) -> int:
    """Run the verb."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    sub = parser.add_subparsers(dest="verb", required=True)
    make = sub.add_parser("manifest", help="write config/disc.toml from a disc dump")
    make.add_argument(
        "--cue", help="the cue sheet (default: the set under inputs/external)"
    )
    make.add_argument("--output", default=str(ROOT / disc.MANIFEST))
    make.set_defaults(run=manifest)
    check = sub.add_parser("verify", help="check the dump, extracted files and images")
    check.add_argument("--no-images", action="store_true", help="skip the code images")
    check.set_defaults(run=verify)
    again = sub.add_parser("rebuild", help="rebuild the disc from the built images")
    again.add_argument("--output", default="build/disc-rebuild", help="repo-relative")
    again.set_defaults(run=rebuild)
    args = parser.parse_args(argv)
    return args.run(args)


if __name__ == "__main__":
    raise SystemExit(run_main(main))
