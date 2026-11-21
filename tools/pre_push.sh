#!/bin/sh
# Run every check a push needs, one line per check; exit 1 when any fails.
#
#   tools/pre_push.sh [BASE_REF]          or    meson compile -C build/meson pre-push
#
# The checks are the rows of tools/gate.txt, described in tools/README.md#pre-push. BASE_REF is what the work is compared with; it defaults to the newest of
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
# tools/gate.txt lists the checks. A chain check runs after the one before it; a par check runs
# beside the rest. Each writes its exit code beside its log.
export ref base bld
rm -f "$logs"/*.rc
have_check=false
ninja -C "$bld" -t targets all 2>/dev/null | grep -q '^check:' && have_check=true
have_compiler=false
[ -x toolchains/gcc-2.7.2-psx/gcc ] && have_compiler=true
names=""
chain=""
while IFS='|' read -r name needs run _ cmd; do
	case $name in '' | '#'*) continue ;; esac
	case $needs in
	disc) $have_check || { echo "skip  $name (no disc: Meson offers no check target)"; continue; } ;;
	compiler) $have_compiler || { echo "skip  $name (no toolchains/gcc-2.7.2-psx)"; continue; } ;;
	esac
	names="$names $name"
	if [ "$run" = chain ]; then
		chain="$chain$name|$cmd
"
	else
		(sh -c "$cmd" </dev/null >"$logs/$name.log" 2>&1; echo $? >"$logs/$name.rc") &
	fi
done <tools/gate.txt
(
	printf '%s' "$chain" | while IFS='|' read -r name cmd; do
		sh -c "$cmd" </dev/null >"$logs/$name.log" 2>&1
		echo $? >"$logs/$name.rc"
	done
) &
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
