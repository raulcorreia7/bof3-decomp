#!/bin/sh
# Stage the PsyQ 3.7 SDK: fetch the pinned archive, check it, unpack it, convert it.
#
#   tools/psyq.sh [DEST]          DEST defaults to toolchains/psyq/3.7
#
# Each library member lands in DEST/<lib>/<member>.o, converted
# from Psy-Q LNK to ELF by psyq-obj-parser.
# A local copy of the archive is used when present; otherwise it is downloaded.
set -eu

usage() {
	sed -n '2,8p' "$0" | sed 's/^# \{0,1\}//' >&2
	exit 2
}
case "${1:-}" in
-h | --help) sed -n '2,8p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
-*) usage ;;
esac
[ "$#" -le 1 ] || usage

URL=https://archive.org/download/psyq-370.7z/psyq-370.7z
SHA256=9b3955ca74915a3e3b3eb18cf4fcf2210e75cac6985cb9a2ff90df8332e910e1
LOCAL=inputs/external/private-assets/psyq/3.7/source-media/psyq-370.7z
DOWNLOAD=toolchains/downloads/psyq-370.7z
PARSER=toolchains/psyq-compilers/psyq-obj-parser-cadce246
DEST=${1:-toolchains/psyq/3.7}

parser_sha=$(sha256sum "$PARSER" | cut -d " " -f 1)
if [ "$(cat "$DEST/.source-sha256" 2>/dev/null)" = "$SHA256" ] &&
    [ "$(cat "$DEST/.parser-sha256" 2>/dev/null)" = "$parser_sha" ] &&
    [ -n "$(find "$DEST" -name "*.o" -type f -print -quit)" ]; then
    echo "psyq: $DEST current"
    exit 0
fi

archive=$LOCAL
if [ ! -f "$archive" ]; then
    archive=$DOWNLOAD
    if [ ! -f "$archive" ]; then
        mkdir -p "$(dirname "$archive")"
        curl --fail --location --silent --show-error --retry 3 -o "$archive.tmp" "$URL"
        mv "$archive.tmp" "$archive"
    fi
fi
printf '%s  %s\n' "$SHA256" "$archive" | sha256sum -c --quiet -

tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
7z x -y -o"$tmp" "$archive" 'LIB/*' >/dev/null

rm -rf "$DEST"
mkdir -p "$DEST"

if [ -x "$PARSER" ]; then
    parser=$(cd "$(dirname "$PARSER")" && pwd)/$(basename "$PARSER")
    converted=0
    failed=0
    for lib in "$tmp"/LIB/*; do
        out=$DEST/$(basename "$lib" | tr '[:upper:]' '[:lower:]' | sed 's/\.[a-z]*$//')
        mkdir -p "$out"
        case $lib in
        *.LIB | *.lib) .venv/bin/python "$(dirname "$0")/psyq_lib.py" "$lib" "$tmp/members" ;;
        *) mkdir -p "$tmp/members" && cp "$lib" "$tmp/members/$(basename "${lib%.*}" | tr '[:upper:]' '[:lower:]').obj" ;;
        esac
        for obj in "$tmp"/members/*.obj; do
            # Run inside the output folder: the parser records its -o path in the object.
            (cd "$out" && "$parser" "$obj" -o "$(basename "$obj" .obj).o" >/dev/null 2>&1) &&
                converted=$((converted + 1)) || { echo "psyq: skipping $(basename "$lib") $(basename "$obj"), which the object parser cannot read" >&2; failed=$((failed + 1)); }
        done
        rm -rf "$tmp/members"
    done
    echo "psyq: $converted library members converted"
    if [ "$failed" -ne 0 ]; then
        echo "psyq: $failed unreadable members skipped; no target links them" >&2
    fi
else
    echo "psyq: $PARSER missing; run tools/setup.sh" >&2
    exit 1
fi

echo "$SHA256" >"$DEST/.source-sha256"
echo "$parser_sha" >"$DEST/.parser-sha256"
echo "psyq: staged $DEST"
