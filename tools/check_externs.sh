#!/bin/sh
# Reject a new `extern` line in a .c file. A declaration lives in a header (see docs/conventions.md);
# the .c files that still hold one are counted at the merge base and may not gain any.
#
#   tools/check_externs.sh [BASE_REF]
#
# BASE_REF defaults to the newer of refs/remotes/public/main and refs/remotes/origin/main.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,7p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."

ref=${1:-}
if [ -z "$ref" ]; then
	for candidate in refs/remotes/public/main refs/remotes/origin/main; do
		git rev-parse --verify --quiet "$candidate^{commit}" >/dev/null || continue
		if [ -z "$ref" ] || git merge-base --is-ancestor "$ref" "$candidate"; then
			ref=$candidate
		fi
	done
fi
if [ -z "$ref" ] || ! git rev-parse --verify --quiet "$ref^{commit}" >/dev/null; then
	echo "check-externs: cannot compare with ${1:-main}: no such ref" >&2
	exit 2
fi
base=$(git merge-base HEAD "$ref") || {
	echo "check-externs: HEAD and $ref share no history" >&2
	exit 2
}
count() { grep -cE '^[[:space:]]*extern[[:space:]]' || true; }
now=$(git grep -hE '^[[:space:]]*extern[[:space:]]' -- 'src/*.c' | count)
before=$(git grep -hE '^[[:space:]]*extern[[:space:]]' "$base" -- 'src/*.c' | count)
echo "check-externs: $now extern lines in .c files now, $before at $(git rev-parse --short "$base")"
if [ "$now" -gt "$before" ]; then
	echo "check-externs: $((now - before)) more than $ref; declare the symbol in a header" >&2
	exit 1
fi
