#!/bin/sh
# Near-miss loop: opcode diff, a time-boxed permuter run, the best score as an attempts row.
#
#   tools/near_miss.sh <target>@0x<ADDR> <src/...c> [SECONDS]     (default 300)
#
# The source holds the NON_MATCHING draft; the importer picks its first one. Needs
# `meson setup build/meson` and `tools/setup.sh --matching`.
set -eu
case "${1:-}" in
-h | --help | "") sed -n '2,8p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."
ref=$1 src=$2 secs=${3:-300}
py=$(command -v python3)
"$py" tools/opcode_diff.py "$ref" || true
fn=$("$py" -c 'import sys; sys.path.insert(0, "tools"); from permuter_import import function_name; from pathlib import Path; print(function_name(Path(sys.argv[1])))' "$src")
dir=work/permute/nonmatchings/$fn
rm -rf "$dir"
"$py" tools/permuter_import.py "$src"
log=$(mktemp)
timeout "$secs" "$py" -u third_party/decomp-permuter/permuter.py "$dir" -j 4 --best-only >"$log" 2>&1 || true
base=$(sed -n 's/.*base score = \([0-9]*\).*/\1/p' "$log" | head -1)
best=$(sed -n 's/.*new best score: \([0-9]*\).*/\1/p' "$log" | tail -1)
best=${best:-$base}
rm -f "$log"
"$py" tools/attempts.py add --function "$ref" --score "${best:-null}" \
	--tried "permuter ${secs}s on $fn: base ${base:-?}, best ${best:-?}" \
	--first-diff "candidates in $dir/output-*"
