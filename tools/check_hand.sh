#!/bin/sh
# Fail when a hand-written asm file was added or removed since the last configure.
#
#   tools/check_hand.sh HAND_LIST    the list `meson setup` wrote
#
# The build graph fixes where each C unit finds its assembly at configure time. A new
# asm/<target>/hand/*.s file changes nothing until Meson is configured again.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,7p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."

now=$(find asm -path '*/hand/*.s' | sort)
if [ "$now" != "$(sort "$1")" ]; then
	echo "check: a hand/ assembly file was added or removed since the last configure." >&2
	echo "check: run: meson setup --reconfigure build/meson" >&2
	exit 1
fi
