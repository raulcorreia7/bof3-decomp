#!/bin/sh
# Print what GCC 2.7.2 decided for one C file, pass by pass, from its own dumps.
#
#   tools/rtl_dump.sh <c file> [letters] [function]     tools/rtl_dump.sh src/engine/area/map/Area_DrawCellRing.c lg Area_DrawCellRing
#
# Letters are GCC's -d flags (default lg): l local allocation (.lreg: each pseudo's uses, live
# length and hard register), g global allocation and reload (.greg: allocation order, conflicts,
# spills), L loop (.loop: what moves out of each loop and why, induction values), S scheduling,
# c combine, s cse, j jump. With a function name it prints that
# function's part of each dump; the dump files stay in $OUT (default a fresh folder under $TMPDIR).
# The flags below copy the image build's (build/meson/compile_commands.json) plus -DNON_MATCHING,
# so a draft body compiles; update them with the build.
set -eu
case "${1:-}" in
'' | -h | --help) sed -n '2,11p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
f=$1
d=${2:-lg}
fn=${3:-}
OUT=${OUT:-${TMPDIR:-/tmp}/rtl-$$}
mkdir -p "$OUT"
R=$(cd "$(dirname "$0")/.." && pwd)
G=$R/toolchains/gcc-2.7.2-psx
cd "$R"
(cd "$OUT" && COMPILER_PATH=$(dirname "$(readlink -f "$G/gcc")") "$G/gcc" -DMATCHING -DNON_MATCHING \
	-I"$R/src" -I"$R/include" -I"$R/include/psyq" -G0 -funsigned-char -msoft-float -gcoff \
	'-DASM_DIR="x"' -I"$R/$(dirname "$f")" -O2 "-d$d" -S -o "$OUT/out.s" "$R/$f" 2>&1 |
	grep -v warning | head -n 5) || true
if [ -n "$fn" ]; then
	for dump in "$OUT"/*.[a-z]*; do
		case $dump in *.s) continue ;; esac
		echo "==== ${dump##*.}"
		awk -v fn="$fn" '$0 ~ "^;; Function " fn "$" {on=1} on && /^;; Function / && $0 !~ fn "$" {exit} on' "$dump" |
			grep -E '^;; |^Register [0-9]+ used|^Basic block|Spilling| now in |^Loop from |^Insn [0-9]+: |^Biv |giv at |[Gg]iv reg ' | head -n 120
	done
fi
echo "rtl: dumps in $OUT"
