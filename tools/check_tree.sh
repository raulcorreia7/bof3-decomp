#!/bin/sh
# Reject tracked retail media, files over 1 MiB, relative includes or imports, and struct members of enum type. Needs no build inputs.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,2p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."

bad=$(git ls-files -z | xargs -0 stat -c '%s %n' | awk '{
	name = substr($0, length($1) + 2)
	if ($1 > 1048576 || tolower(name) ~ /\.(bin|iso|img|cue|exe|psx|7z|mdf|ccd|ecm)$/) print name
}')
if [ -n "$bad" ]; then
	echo "check-tree: retail data or oversized files tracked:"
	echo "$bad"
	echo "check-tree: run: git rm --cached <file>, and keep game data under inputs/ or build/"
	exit 1
fi

# Includes start at a root (src/ or include/), as in "overlays/area/X.h"; Python imports name the package.
relative=$(git grep -nE '#[[:space:]]*include[[:space:]]+"\.\.?/' -- src include ':!include/psyq'
	git grep -nE '^[[:space:]]*from \.+[A-Za-z_]* import' -- '*.py') || true
if [ -n "$relative" ]; then
	echo "check-tree: relative includes or imports:"
	echo "$relative"
	echo "check-tree: include from the source root (\"overlays/area/X.h\") and import as bof3.<module>"
	exit 1
fi
python3 tools/check_enum_members.py
echo "check-tree: ok"
