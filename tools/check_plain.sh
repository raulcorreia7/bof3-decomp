#!/bin/sh
# `check-plain`: every C source compiles as plain C, without MATCHING. The
# matching helpers in include/match/match.h compile away there, so this proves
# the sources do not depend on them.
#
#   tools/check_plain.sh FLAGS [JOBS]    FLAGS is `meson setup`'s plain-flags.txt
set -eu
case "${1:-}" in
-h | --help) sed -n '2,6p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."

gcc_dir=toolchains/gcc-2.7.2-psx
if [ ! -x "$gcc_dir/gcc" ]; then
	echo "check-plain: $gcc_dir is missing (run tools/setup.sh)" >&2
	exit 1
fi
flags=${1:-}
if [ ! -f "$flags" ]; then
	echo "check-plain: $flags is missing; run meson setup build/meson" >&2
	exit 1
fi
jobs=${2:-$(nproc)}
log=$(mktemp)
trap 'rm -f "$log"' EXIT

# $1 is the blank-separated flag list and $2 the source; both split deliberately.
git ls-files 'src/*.c' | xargs -P "$jobs" -n 1 sh -c '
	if ! out=$("$0/gcc" -B"$0/" -S -o /dev/null $1 -I"$(dirname "$2")" "$2" 2>&1); then
		printf "%s\n%s\n" "check-plain: $2 does not compile" "$out"
	fi' "$gcc_dir" "$(cat "$flags")" >"$log"

if [ -s "$log" ]; then
	grep -v "warning" "$log" >&2
	exit 1
fi
echo "check-plain: $(git ls-files 'src/*.c' | wc -l) sources compile without MATCHING"
