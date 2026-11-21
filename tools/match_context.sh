#!/bin/sh
# Print what to read before a function's first attempt: assembly, recorded attempts, C file.
#
#   tools/match_context.sh <target>@0x<ADDR>     tools/match_context.sh exe/slus_004_22@0x801530D0
#
# The assembly is the function's split file under build/asm/<target>/ with the offsets trimmed; the
# attempts are the last three rows of config/attempts.jsonl for the function; the file is the
# C file that holds its INCLUDE_ASM line. A split file named after its symbol is found by the
# address its first instruction comment carries, as `match.sh` does.
set -eu
case "${1:-}" in
'' | -h | --help) sed -n '2,8p' "$0" | sed 's/^# \{0,1\}//'; exit 0 ;;
esac
cd "$(dirname "$0")/.."
fn=$1
img=${fn%@*}
addr=$(printf '%s' "${fn#*@0x}" | tr '[:lower:]' '[:upper:]')
a=$(find "build/asm/$img" -maxdepth 2 -name "*${addr}*.s" | head -1)
[ -n "$a" ] || a=$(grep -rlE --include='*.s' "^ +/\* [0-9A-F]+ $addr " "build/asm/$img" 2>/dev/null | head -1)
name=$(sed -n 's/^[[:space:]]*glabel[[:space:]]*//p' "$a" 2>/dev/null | head -1)
echo "== asm ${a:-(none)}"
[ -z "$a" ] || sed -E 's#/\* [0-9A-F]+ ([0-9A-F]+) [0-9A-F]+ \*/#\1#' "$a" | grep -vE '^\s*$|glabel|\.size|nonmatching|endlabel|^\.|Generated' | cut -c5-74
echo "== attempts"
grep -h "\"$fn\"" config/attempts.jsonl 2>/dev/null | jq -r '"- \(.tried|.[0:330]) || \(.first_diff|tostring|.[0:160])"' | tail -3
echo "== file"
if [ -n "$name" ]; then
	grep -rln "INCLUDE_ASM($name)" src | head -2
else
	grep -rln "INCLUDE_ASM(func_$addr)\|INCLUDE_ASM(.*$addr)" src | head -2
fi
