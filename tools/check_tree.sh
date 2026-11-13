#!/bin/sh
# Reject tracked retail media, files over 2 MiB, relative includes or imports, struct members of enum type, and sources no image layout compiles. Needs no build inputs.
# The cap leaves the hand-kept config/symbols.toml room to grow with the coverage; a row carries its source.
set -eu
case "${1:-}" in
-h | --help) sed -n '2,2p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."

bad=$(git ls-files -z | xargs -0 stat -c '%s %n' | awk '{
	name = substr($0, length($1) + 2)
	if ($1 > 2097152 || tolower(name) ~ /\.(bin|iso|img|cue|exe|psx|7z|mdf|ccd|ecm)$/) print name
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
# Source rules on the lines a change adds, against the base ref.
base=${1:-}
if [ -n "$base" ]; then
	bad=0
	added=$(git diff -U0 "$base...HEAD" -- src include | grep -E '^\+[^+]' || true)
	rule() {
		printf '%s\n' "$added" | grep -nE "$1" | head -n 5 | while IFS= read -r l; do
			echo "check-tree: $2: $l"
		done
	}
	for spec in 'asm\("\$|register pin' 'goto L[0-9A-Fa-f]{4,}|decompiler label' \
		'\b(temp|var|phi|saved_reg)_[a-z0-9]|decompiler local' \
		'\bsp[0-9][0-9A-F]*\b|stack-offset name' '\bTASK_BYTES\b|\(\(u8 ?\*\) ?g_Task\)|task read by offset' \
		'\bM2C_|m2c macro' '0x[0-9A-Fa-f]{7,8}|raw address'; do
		out=$(rule "${spec%|*}" "${spec#*|}")
		if [ -n "$out" ]; then
			printf '%s\n' "$out"
			bad=1
		fi
	done
	# A prototype added to a header must be the only declaration of that name in a visible header.
	dups=$(git diff -U0 "$base...HEAD" -- include src | awk '
		/^\+\+\+ b\// { f = substr($0, 7); next }
		/^\+[^+]/ && f ~ /\.h$/ {
			line = substr($0, 2)
			if (line ~ /^[[:space:]]*#/ || line ~ /MATCH|static inline|typedef/) next
			if (line ~ /;[[:space:]]*$/) print f "\t" line
		}' | while IFS='	' read -r f line; do
			fn=$(printf '%s\n' "$line" | sed -nE 's/^[A-Za-z_][A-Za-z0-9_ *]*[ *]([A-Za-z_][A-Za-z0-9_]*)\(.*/\1/p')
			[ -n "$fn" ] || continue
			hits=$(git grep -lE "^[[:space:]]*[A-Za-z_][A-Za-z0-9_ *]*[ *]$fn\([^;]*\);[[:space:]]*$" HEAD -- include src |
				sed 's/^HEAD://' | grep '\.h$' |
				while IFS= read -r o; do
					[ "$o" = "$f" ] && continue
					case $f in
					include/*) case $o in include/*) printf '%s ' "$o" ;; esac ;;
					*)
						case $o in
						include/*) printf '%s ' "$o" ;;
						*)
							d=$(dirname "$o")
							[ "$d" = "$(dirname "$f")" ] && continue
							case $f in "$d"/*) printf '%s ' "$o" ;; esac
							;;
						esac
						;;
					esac
				done)
			hits=${hits% }
			[ -z "$hits" ] || echo "check-tree: duplicate declaration: $f declares $fn, also in $hits"
		done)
	if [ -n "$dups" ]; then
		echo "$dups"
		bad=1
	fi
	# A new header that carries a guard names it from its path.
	guards=$(git diff --name-only --diff-filter=A "$base...HEAD" -- 'include/*.h' 'src/*.h' |
		while IFS= read -r f; do
			guard=$(sed -n '1,20s/^#ifndef[[:space:]]\+\([A-Za-z0-9_]*\).*/\1/p' "$f" | head -n 1)
			[ -n "$guard" ] || continue
			case $f in
			include/*)
				want=$(printf '%s' "${f#include/}" | tr '[:lower:]./' '[:upper:]__')
				[ "$guard" = "$want" ] || echo "check-tree: header guard: $f guard $guard should be $want"
				;;
			src/overlays/*/*/*/*.h | src/engine/*/*/*.h)
				dir=$(dirname "$f")
				slot=$(basename "$dir")
				arch=$(basename "$(dirname "$dir")")
				suffix=$(printf '%s_%s_H' "$arch" "$slot" | tr '[:lower:]' '[:upper:]')
				case $guard in
				OVERLAY_*"$suffix") ;;
				*) echo "check-tree: header guard: $f guard $guard should end $suffix" ;;
				esac
				;;
			src/overlays/*/*.h)
				family=$(basename "$(dirname "$f")")
				prefix=$(printf '%s_' "$family" | tr '[:lower:]' '[:upper:]')
				case $guard in
				"$prefix"*) ;;
				*) echo "check-tree: header guard: $f guard $guard should start $prefix" ;;
				esac
				;;
			src/logo/*.h)
				case $guard in
				LOGO_*) ;;
				*) echo "check-tree: header guard: $f guard $guard should start LOGO_" ;;
				esac
				;;
			esac
		done)
	if [ -n "$guards" ]; then
		echo "$guards"
		bad=1
	fi
	# A body added to a header must not duplicate one that another header already defines.
	shared=$(git diff --diff-filter=A --name-only "$base...HEAD" -- 'src/*.h' | while IFS= read -r h; do
		grep -oE '^MATCH [^(]* \**([A-Za-z_][A-Za-z0-9_]*)\(' "$h" |
			sed -E 's/.*[ *]([A-Za-z_0-9]+)\($/\1/' |
			while IFS= read -r fn; do
				git grep -lE "^MATCH .*[ *]$fn\(" HEAD -- 'src/*.h' | sed 's/^HEAD://' | grep -vx "$h" |
					while IFS= read -r o; do echo "check-tree: shared-body: $h defines $fn, already defined in $o"; done
			done
	done)
	if [ -n "$shared" ]; then
		echo "$shared"
		bad=1
	fi
	[ "$bad" = 0 ] || exit 1
fi
python3 tools/check_enum_members.py
python3 tools/check_sources.py
echo "check-tree: ok"
