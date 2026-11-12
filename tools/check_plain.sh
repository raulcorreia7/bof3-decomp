#!/bin/sh
# `check-plain`: every C source compiles as plain C, without MATCHING. The
# matching helpers in include/match/match.h compile away there, so this proves
# the sources do not depend on them. A source whose plain preprocessed text has
# compiled before is skipped, so a header change recompiles only its users and
# every worktree shares the result.
#
#   tools/check_plain.sh FLAGS [JOBS]    FLAGS is `meson setup`'s plain-flags.txt
#                                        JOBS defaults to HEAVY_JOBS, else nproc/4
#
# The keys are empty files in `~/.cache/bof3-cc/plain`, one per preprocessed
# text; BOF3_CC_CACHE_DIR moves the cache and BOF3_CC_CACHE=0 turns the skip off.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,12p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
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
jobs=${2:-${HEAVY_JOBS:-$(( $(nproc) / 4 ))}}
[ "$jobs" -ge 1 ] || jobs=1
cache=
if [ "${BOF3_CC_CACHE:-}" != 0 ]; then
	cache=${BOF3_CC_CACHE_DIR:-$HOME/.cache/bof3-cc}/plain
	mkdir -p "$cache"
fi
# The compiler's own bytes join the key, so a toolchain change invalidates it.
tool=$(cat "$gcc_dir/gcc" "$gcc_dir/cc1" | sha1sum | cut -d' ' -f1)
log=$(mktemp)
compiled=$(mktemp)
trap 'rm -f "$log" "$compiled"' EXIT

# $1 flags, $2 cache dir, $3 tool hash, $4 compiled list; the source follows as $5.
# Both flag and path lists split deliberately.
git ls-files 'src/*.c' | xargs -P "$jobs" -n 1 sh -c '
	src=$5
	dir=$(dirname "$src")
	key=
	if [ -n "$2" ]; then
		key=$( { printf "%s %s\n" "$3" "$1"; "$0/gcc" -B"$0/" -E $1 -I"$dir" "$src"; } 2>/dev/null |
			sha1sum | cut -d" " -f1 )
		[ -f "$2/$key" ] && exit 0
	fi
	if out=$("$0/gcc" -B"$0/" -S -o /dev/null $1 -I"$dir" "$src" 2>&1); then
		[ -z "$key" ] || : >"$2/$key"
		printf "%s\n" "$src" >>"$4"
	else
		printf "%s\n%s\n" "check-plain: $src does not compile" "$out"
	fi
' "$gcc_dir" "$(cat "$flags")" "$cache" "$tool" "$compiled" >"$log"

if [ -s "$log" ]; then
	grep -v "warning" "$log" >&2
	exit 1
fi
echo "check-plain: $(git ls-files 'src/*.c' | wc -l) sources compile without MATCHING ($(wc -l <"$compiled") compiled)"
