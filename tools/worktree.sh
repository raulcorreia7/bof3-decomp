#!/bin/sh
# Create a ready-to-build Git worktree for parallel work.
#
#   tools/worktree.sh --from <checkout> <branch> [<dir>]
#
#   --from <checkout>  a built checkout of this repository (setup done, disc extracted); the new
#                      worktree links its local inputs instead of extracting them again
#   <branch>           the new branch
#   <dir>              the worktree folder (default: .worktrees/<branch>, which Git ignores)
#
# Linked from <checkout>: inputs/, toolchains/, .venv/, build/disc and build/bin. The submodule
# checkouts under third_party/ are copied, so Git sees no change in them. The script then runs
# `meson setup build/meson`. The retail files stay in <checkout>; do not delete it while the
# worktree is in use.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,15p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac

usage() {
	sed -n '2,15p' "$0" | sed 's/^# \{0,1\}//' >&2
	exit 2
}
die() {
	printf 'worktree: %s\n' "$*" >&2
	exit 1
}

from=
base=origin/main
branch=
dir=
while [ $# -gt 0 ]; do
	case $1 in
	--from) from=${2:?--from needs a path}; shift 2 ;;
	-h | --help) usage ;;
	-*) die "unknown option $1 (see tools/worktree.sh --help)" ;;
	*)
		if [ -z "$branch" ]; then branch=$1
		elif [ -z "$dir" ]; then dir=$1
		else die "too many arguments"
		fi
		shift
		;;
	esac
done
[ -n "$from" ] && [ -n "$branch" ] || usage

root=$(cd "$(dirname "$0")/.." && pwd)
from=$(cd "$from" 2>/dev/null && pwd) || die "no such checkout: $from"
[ -d "$from/build/disc" ] && [ -d "$from/build/bin" ] ||
	die "$from has no build/disc and build/bin: run tools/setup.sh there first"
[ -x "$from/.venv/bin/python" ] || die "$from has no .venv: run tools/setup.sh there first"
[ -n "$dir" ] || dir=$root/.worktrees/$branch
[ ! -e "$dir" ] || die "$dir exists"
git -C "$root" rev-parse --verify --quiet "$base^{commit}" >/dev/null || die "unknown base $base"

git -C "$root" worktree add -q -b "$branch" "$dir" "$base"
dir=$(cd "$dir" && pwd)
mkdir -p "$dir/build"

# Entries of the local folders that Git ignores; the tracked README stays.
for folder in inputs toolchains; do
	for entry in "$from/$folder"/* "$from/$folder"/.[!.]*; do
		[ -e "$entry" ] || continue
		[ -e "$dir/$folder/$(basename "$entry")" ] || ln -s "$entry" "$dir/$folder/$(basename "$entry")"
	done
done
ln -s "$from/.venv" "$dir/.venv"
ln -s "$from/build/disc" "$dir/build/disc"
ln -s "$from/build/bin" "$dir/build/bin"

# Submodules the source checkout has fetched.
for module in "$from"/third_party/*/; do
	name=${module%/}
	name=${name##*/}
	[ "$name" != references ] || continue
	[ -e "$dir/third_party/$name" ] && [ -n "$(ls -A "$module" 2>/dev/null)" ] || continue
	[ -z "$(ls -A "$dir/third_party/$name")" ] || continue
	tar -C "$module" --exclude=.git -cf - . | tar -C "$dir/third_party/$name" -xf -
done

(cd "$dir" && meson setup build/meson >build/setup.log 2>&1) ||
	die "meson setup failed; see $dir/build/setup.log"
echo "worktree: $dir ($branch from $base)"
