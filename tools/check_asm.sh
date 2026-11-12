#!/bin/sh
# Reject an increase in INCLUDE_ASM placeholders since this branch left main, in total or in any one
# image. A per-image key is the last two directories of the source folder below src/
# (<archive>/<slot>, for example game/00 for src/engine/game/00); src/engine/slus and src/logo are
# their own keys, slus and logo.
#
#   tools/check_asm.sh [BASE_REF]
#
# The baseline is the count at the merge base of HEAD and BASE_REF. BASE_REF defaults to the newest
# of public/main, origin/main and main (a local main that was never updated falls behind); the output names the
# ref and commit it used. With no such ref the check fails, because it cannot compare.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,11p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."

status=0
now_lines=$(grep -rF INCLUDE_ASM src | cut -d: -f1)
now=$(printf '%s\n' "$now_lines" | grep -c .) || now=0
ref=${1:-}
if [ -z "$ref" ]; then
	. tools/lib/baseref.sh
	ref=$(newest_base_ref)
fi
if [ -z "$ref" ] || ! git rev-parse --verify --quiet "$ref^{commit}" >/dev/null; then
	echo "include-asm: cannot compare with ${1:-main}: no such ref (INCLUDE_ASM now: $now)" >&2
	echo "include-asm: run: git fetch origin main   or pass a ref: tools/check_asm.sh <ref>" >&2
	exit 2
fi
base=$(git merge-base HEAD "$ref") || {
	echo "include-asm: HEAD and $ref share no history (a shallow clone?)" >&2
	echo "include-asm: run: git fetch --unshallow origin main" >&2
	exit 2
}
previous_lines=$(git grep -F INCLUDE_ASM "$base" -- src | cut -d: -f2)
previous=$(printf '%s\n' "$previous_lines" | grep -c .) || previous=0
echo "INCLUDE_ASM: $now now, $previous at $(git rev-parse --short "$base") (merge base with $ref)"
if [ "$now" -gt "$previous" ]; then
	echo "include-asm: $((now - previous)) more than $ref; a match removes a line, never adds one" >&2
	status=1
fi
# A lost match hidden by a new one elsewhere keeps the total level, so compare every image too.
# An image key is the last two directories of the source path (one if there is only one below src).
over=$({
	printf '%s\n' "$previous_lines" | sed 's/^/B /'
	printf '%s\n' "$now_lines" | sed 's/^/N /'
} | awk '
	NF == 2 {
		n = split($2, part, "/")
		key = part[n - 1]
		if (n > 3) key = part[n - 2] "/" key
		if (key == "engine/slus") key = "slus"
		count[$1, key]++
		seen[key]
	}
	END {
		for (key in seen)
			if (count["N", key] > count["B", key]) {
				printf "include-asm: image %s has %d INCLUDE_ASM, %d at the merge base\n", key, count["N", key], count["B", key]
			}
	}' | sort)
if [ -n "$over" ]; then
	printf '%s\n' "$over" >&2
	status=1
fi
exit "$status"
