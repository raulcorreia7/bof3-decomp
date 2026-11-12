#!/bin/sh
# Fail when the tree no longer matches what `meson setup` saw: the graph fixes the headers
# and the hand-written assembly of every image at configure time.
#
#   tools/check_configured.sh headers HEADER_LIST    every public header has a probe
#   tools/check_configured.sh hand HAND_LIST         every hand/ assembly file is in the graph
set -eu
case "${1:-}" in
-h | --help) sed -n '2,6p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."

check=${1:-} list=${2:-}
case "$check" in
headers)
	now=$(find include src -name '*.h')
	what='header'
	name='check-headers'
	done='check-headers: ok'
	;;
hand)
	now=$(find asm -path '*/hand/*.s')
	what='hand/ assembly file'
	name=check
	done=''
	;;
*)
	echo "check_configured: pass headers or hand, and the list meson setup wrote" >&2
	exit 2
	;;
esac

if [ "$(printf '%s\n' "$now" | sort)" != "$(sort "$list")" ]; then
	echo "$name: a $what was added or removed since the last configure." >&2
	echo "$name: run: meson setup --reconfigure build/meson" >&2
	exit 1
fi
if [ -n "$done" ]; then
	echo "$done"
fi
