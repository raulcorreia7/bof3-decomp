#!/bin/sh
# Download a pinned tool atomically, verifying SHA-256 before installation.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,2p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac

if [ "$#" -lt 3 ] || [ "$#" -gt 4 ]; then
    echo 'usage: sh tools/fetch_verified.sh URL SHA256 OUTPUT [--executable]' >&2
    exit 2
fi
url=$1
checksum=$2
output=$3
if [ "$#" -eq 4 ] && [ "$4" != "--executable" ]; then
    echo 'invalid option (expected --executable)' >&2
    exit 2
fi

mkdir -p "$(dirname "$output")"
temporary="$output.tmp.$$"
trap 'rm -f "$temporary"' 0
trap 'exit 1' 1 2 3 15

curl --fail --location --silent --show-error --retry 3 -o "$temporary" "$url"
if command -v sha256sum >/dev/null 2>&1; then
    printf '%s  %s\n' "$checksum" "$temporary" | sha256sum -c -
else
    printf '%s  %s\n' "$checksum" "$temporary" | shasum -a 256 -c -
fi
if [ "$#" -eq 4 ]; then chmod +x "$temporary"; fi
mv -f "$temporary" "$output"
