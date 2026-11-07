# shellcheck shell=sh
# Sourced by tools/pre_push.sh and tools/check_asm.sh: pick the ref a branch is compared with.

# Print the newest of public/main, origin/main and main (the one the others are ancestors of); print nothing when none exists.
newest_base_ref() {
	_ref=
	for _candidate in refs/remotes/public/main refs/remotes/origin/main main; do
		git rev-parse --verify --quiet "$_candidate^{commit}" >/dev/null || continue
		if [ -z "$_ref" ] || git merge-base --is-ancestor "$_ref" "$_candidate"; then
			_ref=$_candidate
		fi
	done
	printf '%s\n' "$_ref"
}
