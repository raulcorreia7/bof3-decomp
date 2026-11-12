#!/usr/bin/env python3
"""Write or check the disc manifest ``config/disc.toml``.

  disc.py manifest   write the manifest from a disc dump and its extracted files
  disc.py verify     check the dump, the extracted files and the code images against it

The manifest lists the version, the CUE sheet, both tracks and every ISO 9660 file with its
size and hashes. ``tools/setup.py`` runs the same checks and names each file that differs.
"""

from __future__ import annotations

import argparse
import json
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from bof3.core import disc

ROOT = Path(__file__).resolve().parents[1]
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
    folder = ROOT / args.extracted
    if (folder / "SYSTEM.CNF").is_file():
        problems += disc.verify_files(data, folder)
    else:
        print(f"disc: {args.extracted} is not extracted; skipped the files")
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
    check.add_argument(
        "--extracted", default=disc.EXTRACTED, help="extracted folder, repo-relative"
    )
    check.add_argument("--no-images", action="store_true", help="skip the code images")
    check.set_defaults(run=verify)
    args = parser.parse_args(argv)
    return args.run(args)


if __name__ == "__main__":
    raise SystemExit(main())
