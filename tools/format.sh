#!/bin/sh
# Format the C, Python, TOML and Markdown sources, or with --check only verify them.
# CLANG_FORMAT, RUFF, PYRIGHT and DPRINT name the tools when they are not on PATH.
set -eu
cd "$(dirname "$0")/.."

check=
mode=-i
case "${1:-}" in
'') ;;
--check)
	check=1
	mode="--dry-run --Werror"
	;;
-h | --help) sed -n '2,3p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
*)
	echo "usage: tools/format.sh [--check]" >&2
	exit 2
	;;
esac

# The pinned copy in .venv wins; a tool on PATH counts only when it runs: a version-manager shim with no version set does not.
pick() { # <name> <override>
	if [ -n "$2" ]; then printf '%s\n' "$2"; elif [ -x ".venv/bin/$1" ]; then printf '%s\n' ".venv/bin/$1"; else bin/internal/find-tool "$1" 2>/dev/null || printf '\n'; fi
}
clang_format=$(pick clang-format "${CLANG_FORMAT:-}")
dprint=$(pick dprint "${DPRINT:-}")
ruff=$(pick ruff "${RUFF:-}")
for entry in "clang-format:$clang_format" "ruff:$ruff" "dprint:$dprint"; do
	tool=${entry%%:*}
	path=${entry#*:}
	[ -n "$path" ] && command -v "$path" >/dev/null 2>&1 && "$path" --version >/dev/null 2>&1 || {
		echo "format: no working $tool; install it (docs/toolchain.md#host-tools; Ruff comes with tools/setup.sh --dev) or name it in CLANG_FORMAT, RUFF or DPRINT" >&2
		exit 1
	}
done

# Data tables (D_*.c, data*.c, *_Data.c) keep the layout their generator writes.
find src include -name '*.[ch]' ! -path 'include/psyq/*' ! -name 'D_*.c' ! -name 'data*.c' ! -name '*_Data.c' -print0 |
	xargs -0 -P "$(nproc)" -n 200 "$clang_format" $mode
"$ruff" format -q ${check:+--check} tools
if [ -n "$check" ]; then
	"$ruff" check -q tools
	pyright=${PYRIGHT:-.venv/bin/pyright}
	[ -x "$pyright" ] || pyright=$(command -v "${PYRIGHT:-pyright}" || true)
	[ -n "$pyright" ] || { echo "format: no pyright; Pyright comes with tools/setup.sh --dev" >&2; exit 1; }
	"$pyright" -p pyproject.toml >/dev/null || { "$pyright" -p pyproject.toml; exit 1; }
fi
if [ -n "$check" ]; then "$dprint" check; else "$dprint" fmt; fi
