#!/usr/bin/env python3
"""Extract the retail payloads for the build; ``tools/setup.sh`` runs this last.

Finds the US disc image under ``inputs/external``, extracts it into ``build/disc``,
unpacks every EMI archive and materializes each target's payload.
Prints what is missing and what to do when the media is absent.
"""

from __future__ import annotations

import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path

from bof3.core import disc
from bof3.core.paths import BUILD
from bof3.emi.catalog import materialize_reviewed_targets
from bof3.resolve import load_target_manifests

ROOT = Path(__file__).resolve().parents[1]
MEDIA = ROOT / "inputs/external"
MISSING = f"""setup: retail media is missing. The build reads your own copy of the US disc.
setup: dump your own disc and put the two-track CUE/BIN set (Redump, 'Breath of Fire III (USA)') in {MEDIA}/,
setup: then run tools/setup.sh again.
setup: until then the disc-free checks work: meson setup build/meson && meson compile -C build/meson check-tree include-asm"""


def find_media() -> tuple[Path, list[Path]]:
    """Locate the disc set."""
    found = disc.disc_set(MEDIA)
    if found is None:
        sys.exit(MISSING)
    return found


def refuse(problems: list[str], what: str) -> None:
    """Stop with one line per mismatch."""
    if problems:
        lines = "\n".join(f"setup:   {line}" for line in problems)
        sys.exit(
            f"setup: {what} differs from {disc.MANIFEST} ({len(problems)}):\n{lines}"
        )


def extractor() -> str:
    """Build the pinned ``bof3`` CLI, or use the one named by ``BOF3_CLI``."""
    override = os.environ.get("BOF3_CLI")
    if override:
        found = shutil.which(override)
        if found is None:
            sys.exit(f"setup: BOF3_CLI is not executable: {override}")
        return found
    manifest = ROOT / "tools/bof3-tools/Cargo.toml"
    if not manifest.is_file():
        sys.exit(
            "setup: tools/bof3-tools is empty; run: git submodule update --init tools/bof3-tools"
        )
    target = (ROOT / (os.environ.get("CARGO_TARGET_DIR") or "build/rust")).resolve()
    subprocess.run(
        ["cargo", "build", "--locked", "--release", "--no-default-features",
         "--bin", "bof3", "--manifest-path", str(manifest), "--target-dir", str(target)],
        check=True,
    )  # fmt: skip
    return str(target / "release/bof3")


def main(argv: list[str] | None = None) -> int:
    """Extract and materialize the payloads unless they are current."""
    argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    ).parse_args(argv)
    manifests = load_target_manifests(ROOT)
    extracted = ROOT / BUILD / "disc"
    if extracted.is_dir() and all(
        (ROOT / manifest.binary).is_file() for manifest in manifests.values()
    ):
        print("payloads: current")
        return 0
    expected = disc.load_manifest(ROOT)
    client = None
    if extracted.is_dir() and not disc.verify_files(expected, extracted):
        print("disc: current")
    else:
        cue, bins = find_media()
        refuse(disc.verify_tracks(expected, bins), "the disc dump")
        client = extractor()
        subprocess.run(
            [client, "disc", "extract", "-i", str(cue), "-o", str(extracted)],
            check=True,
        )  # fmt: skip
        refuse(disc.verify_files(expected, extracted), "the extracted disc")
    for archive in sorted(extracted.rglob("*.EMI")):
        out = extracted / archive.relative_to(extracted).with_suffix("")
        if (out / "emi.json").is_file():
            continue
        out.parent.mkdir(parents=True, exist_ok=True)
        client = client or extractor()
        subprocess.run(
            [client, "emi", "extract", "--quiet", "-J", "-o", str(out), str(archive)],
            check=True,
        )
    materialize_reviewed_targets(root=ROOT)
    for manifest in manifests.values():
        if manifest.kind == "executable" and not (ROOT / manifest.binary).is_file():
            (ROOT / manifest.binary).parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(extracted / manifest.disc_id, ROOT / manifest.binary)
    refuse(disc.verify_images(ROOT), "the code images")
    # Fresh payloads are split inputs; drop the caches.
    shutil.rmtree(ROOT / BUILD / ".cache", ignore_errors=True)
    print(f"payloads: {len(manifests)} targets")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except subprocess.CalledProcessError as error:
        command = " ".join(str(part) for part in error.cmd[:3])
        sys.exit(
            f"setup: '{command} ...' failed with status {error.returncode}; see the output above"
        )
