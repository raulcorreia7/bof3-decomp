#!/bin/sh
# Run every check a push needs, one line per check; exit 1 when any fails.
#
#   tools/pre_push.sh [BASE_REF]          or    meson compile -C build/meson pre-push
#
# Checks: check (only with a disc), check-headers, check-tree, include-asm, format-check,
# meson test, typeloss, quality (no touched file gets worse). BASE_REF is what the work is compared with; it defaults to the newer of
# public/main and origin/main. Each log is build/pre-push/<check>.log. Format first with
# `meson compile -C build/meson format`.
set -u
cd "$(dirname "$0")/.." || exit 2
bld=${BUILD_DIR:-build/meson}
logs=build/pre-push
mkdir -p "$logs"

ref=${1:-}
if [ -z "$ref" ]; then
	for candidate in refs/remotes/public/main refs/remotes/origin/main; do
		git rev-parse --verify --quiet "$candidate^{commit}" >/dev/null || continue
		if [ -z "$ref" ] || git merge-base --is-ancestor "$ref" "$candidate"; then
			ref=$candidate
		fi
	done
fi
[ -n "$ref" ] || { echo "pre-push: no public/main or origin/main to compare with" >&2; exit 1; }

status=0
step() {
	name=$1
	shift
	if "$@" >"$logs/$name.log" 2>&1; then
		printf 'ok    %s\n' "$name"
	else
		printf 'FAIL  %s: %s\n' "$name" "$(grep -v '^INFO' "$logs/$name.log" | tail -n 1)"
		status=1
	fi
}

targets=$(ninja -C "$bld" -t targets all 2>/dev/null)
if printf '%s\n' "$targets" | grep -q '^check:'; then
	step check meson compile -C "$bld" check
else
	echo "skip  check (no disc: Meson offers no check target)"
fi
step check-headers meson compile -C "$bld" check-headers
step check-tree meson compile -C "$bld" check-tree
step include-asm tools/check_asm.sh "$ref"
step format-check meson compile -C "$bld" format-check
step test meson test -C "$bld" --print-errorlogs
step typeloss python3 tools/typeloss.py "$ref" HEAD
step quality python3 tools/quality.py --diff "$ref"

[ "$status" -eq 0 ] && echo "pre-push: all checks passed against $ref" || echo "pre-push: failed; read build/pre-push/<check>.log"
exit "$status"
