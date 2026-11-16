#!/usr/bin/env python3
"""List one declaration written the same way in several headers.

An `extern` declaration repeated in three image headers is a seam: the thing has an owner and the
copies drift. This scan reads every header under `src/` and `include/`, groups declarations by
their whitespace-normalised text, and prints the names whose text appears in at least `--min`
different files, widest first.

A declaration shared by one group's images belongs in the group header, one shared across groups in
`src/shared/` or `include/<subsystem>/` ([layout](../../docs/layout.md)). A divergent text (two
types or extents for one name) is not listed here: that is a semantics question, not a seam.

    tools/dup_decls.py                 list the seams
    tools/dup_decls.py --min 2         include two-header pairs
    tools/dup_decls.py --json          one JSON object per seam
"""

import argparse
import glob
import json
import re

ROOTS = ("include/**/*.h", "src/**/*.h")
EXTERN = re.compile(r"^\s*extern\s+(?P<decl>[^;{}]+?)\s*;\s*$")
NAME = re.compile(r"\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\]\s*)*$")


def declarations():
    for root in ROOTS:
        for path in glob.glob(root, recursive=True):
            with open(path, errors="replace") as source:
                for line in source:
                    match = EXTERN.match(line)
                    if not match:
                        continue
                    decl = " ".join(match.group("decl").split())
                    name = NAME.search(decl)
                    if name:
                        yield name.group(1), decl, path


def main():
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument(
        "--min", type=int, default=3, help="files a declaration must repeat in"
    )
    parser.add_argument("--json", action="store_true", help="one object per seam")
    args = parser.parse_args()

    groups = {}
    for name, decl, path in declarations():
        groups.setdefault(name, {}).setdefault(decl, set()).add(path)

    seams = []
    for name, texts in groups.items():
        if len(texts) != 1:
            continue
        decl = next(iter(texts))
        files = sorted(texts[decl])
        if len(files) >= args.min:
            seams.append((len(files), name, decl, files))
    seams.sort(reverse=True)

    for count, name, decl, files in seams:
        if args.json:
            print(
                json.dumps({"count": count, "name": name, "decl": decl, "files": files})
            )
        else:
            print(f"{count}\t{name}\t{decl}\t" + " ".join(files))
    if not args.json:
        print(f"{len(seams)} declaration(s) repeated in {args.min} or more headers")


if __name__ == "__main__":
    try:
        main()
    except BrokenPipeError:
        pass
