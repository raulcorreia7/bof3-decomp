#!/bin/sh
# Run every check a push needs, one line per check; exit 1 when any fails.
#
#   tools/pre_push.sh [BASE_REF]          or    meson compile -C build/meson pre-push
#
# Checks: check (only with a disc), check-plain (only with the compiler), check-headers, check-tree, externs, include-asm, markers, names, addrs, kept, format-check,
# meson test, typeloss, quality (no touched file gets worse), subsystems (writes the debt table to build/subsystems.md; never fails). BASE_REF is what the work is compared with; it defaults to the newest of
# public/main, origin/main and main; comparisons use the merge base with HEAD. Each log is
# build/pre-push/<check>.log. Format first with `meson compile -C build/meson format`.
set -u
case "${1:-}" in
-h | --help) sed -n '2,9p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.." || exit 2
bld=${BUILD_DIR:-build/meson}
logs=build/pre-push
mkdir -p "$logs"

ref=${1:-}
if [ -z "$ref" ]; then
	. tools/lib/baseref.sh
	ref=$(newest_base_ref)
fi
[ -n "$ref" ] || { echo "pre-push: no public/main or origin/main to compare with" >&2; exit 1; }

# A branch may be behind the base ref: compare the merge base, so commits that landed after the
# branch started do not read as work the branch removed. Checks that take the merge base themselves
# still get $ref; typeloss.py does not, so it gets $base.
base=$(git merge-base "$ref" HEAD 2>/dev/null) || base=$ref

status=0
# Each check runs as a background job and writes its exit code beside its log. The Ninja
# targets (check, check-headers) run one after the other because two Ninja runs must not share
# a build directory; every other check is independent and runs at the same time.
job() {
	name=$1
	shift
	(
		"$@" >"$logs/$name.log" 2>&1
		echo $? >"$logs/$name.rc"
	) &
}
rm -f "$logs"/*.rc
names=""
start() {
	names="$names $1"
	job "$@"
}

targets=$(ninja -C "$bld" -t targets all 2>/dev/null)
have_check=false
if printf '%s\n' "$targets" | grep -q '^check:'; then
	have_check=true
fi
build_chain() {
	if $have_check; then
		meson compile -C "$bld" check >"$logs/check.log" 2>&1
		echo $? >"$logs/check.rc"
	fi
	meson compile -C "$bld" check-headers >"$logs/check-headers.log" 2>&1
	echo $? >"$logs/check-headers.rc"
}
if $have_check; then
	names="$names check"
else
	echo "skip  check (no disc: Meson offers no check target)"
fi
names="$names check-headers"
build_chain &
if [ -x toolchains/gcc-2.7.2-psx/gcc ]; then
	start check-plain tools/check_plain.sh "$bld/plain-flags.txt"
else
	echo "skip  check-plain (no toolchains/gcc-2.7.2-psx)"
fi
start check-tree tools/check_tree.sh "$ref"
start externs tools/check_externs.sh "$ref"
start include-asm tools/check_asm.sh "$ref"
start format-check tools/format.sh --check
start test meson test -C "$bld" --no-rebuild --print-errorlogs
start typeloss python3 tools/typeloss.py "$base" HEAD
start markers python3 tools/check_markers.py --diff "$ref"
start names python3 tools/check_names.py --diff "$ref"
start addrs python3 tools/check_addrs.py "$ref" HEAD
start kept python3 tools/check_kept.py "$ref" HEAD
start quality python3 tools/quality.py --diff "$ref"
start subsystems python3 tools/quality.py --markdown
wait

for name in $names; do
	if [ "$(cat "$logs/$name.rc" 2>/dev/null)" = 0 ]; then
		printf 'ok    %s\n' "$name"
	else
		printf 'FAIL  %s: %s\n' "$name" "$(grep -v '^INFO' "$logs/$name.log" | tail -n 1)"
		status=1
	fi
done

[ "$status" -eq 0 ] && echo "pre-push: all checks passed against $ref" || echo "pre-push: failed; read build/pre-push/<check>.log"
exit "$status"
