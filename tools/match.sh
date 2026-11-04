#!/bin/sh
# Compare one function's compiled bytes with the retail bytes, without the image link.
#
#   tools/match.sh <target> <function>      tools/match.sh exe/slus_004_22 Actor_ApplyVelocity
#   tools/match.sh <target>@<address>       tools/match.sh exe/slus_004_22@0x8015C9CC
#
# <function> is a symbol name, an address (8015C9CC, 0x8015C9CC) or func_<ADDR>.
#
# Exit 0: the function's .text bytes equal retail. Exit 1: they differ; the first differing
# instruction prints for retail and for the candidate. Exit 2: nothing was compared (the
# message says why and the next step).
#
# MATCH_CAND_OUT=FILE also writes the candidate's bytes there (try_body.py counts differences).
# Only .text is compared; `check-<image>` stays the acceptance gate. Method and limits:
# docs/toolchain.md#matchsh.
set -eu
cd "$(dirname "$0")/.."

B=build/meson
BIN=bin/internal/binutils

die() {
	printf 'match.sh: %s\n' "$*" >&2
	exit 2
}

case $# in
1) case $1 in
	*@*) target=${1%@*} func=${1#*@} ;;
	*) die "usage: tools/match.sh <target> <function>   (or <target>@<address>)" ;;
	esac ;;
2) target=$1 func=$2 ;;
*) die "usage: tools/match.sh <target> <function>   (or <target>@<address>)" ;;
esac

flat=$(printf %s "$target" | tr / +)
payload=build/bin/$target.bin
ldscript=build/ld/$flat.ld
[ -d "config/$target" ] || die "unknown target '$target': no config/$target. Targets are the folders under config/ that hold a splat.yaml."
[ -f "$payload" ] || die "no retail bytes at $payload. Extract the disc: tools/setup.sh (see docs/toolchain.md#setup)."
[ -f "$ldscript" ] && [ -f "$B/build.ninja" ] || die "no build graph at $B. Run: meson setup $B"
[ -x "$BIN/objdump" ] || die "no $BIN. Run: tools/setup.sh"

# --- Function address ------------------------------------------------------------------

case $func in
0x*) hex=${func#0x} ;;
func_*) hex=${func#func_} ;;
*) hex=$func ;;
esac
case $hex in
[0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f][0-9A-Fa-f]) ;;
*)
	hex=$(awk -v n="$func" '$1 == n { sub(/^0x/, "", $2); print $2; exit }' \
		"build/symbols/$flat.link" 2>/dev/null) || :
	[ -n "$hex" ] || die "no function '$func' in [$target] of config/symbols.toml. Give its address instead: tools/match.sh $target@0xADDRESS"
	;;
esac
addr=$(printf %08X "0x$hex")

# --- The unit: the C object whose asm file holds that address --------------------------

unit="" asmfile=""
for f in $(grep -lE "^ +/\* [0-9A-F]+ $addr " "asm/$target"/*.s 2>/dev/null || :); do
	u=${f##*/}
	u=${u%.s}
	if grep -qE "^ +src\+.*\+$u\.c\.o\(\.text\);" "$ldscript"; then
		unit=$u asmfile=$f
		break
	fi
done
[ -n "$unit" ] || die "$target@0x$addr is not in a C unit (no asm file with a C object in $ldscript): SDK, hand-written assembly, or a wrong address."
obj=$(awk -v u="$unit" '$1 ~ ("^src\\+.*\\+" u "\\.c\\.o\\(\\.text\\);$") { sub(/\(.*/, "", $1); print $1; exit }' "$ldscript")

# base, function name, file offset, size from the unit's asm
# shellcheck disable=SC2046 # the output is a few fields to split
set -- $(awk -v addr="$addr" '
	/^\.section/ { text = ($2 ~ /^\.text/); next }
	/^glabel / { g = $2; next }
	/^endlabel / { if (infn) { infn = 0 } next }
	$1 == "/*" && $5 == "*/" && text {
		if (base == "") base = $3
		if (g != "") { if ($3 == addr) { fname = g; foff = $2; cnt = 0; infn = 1 } g = "" }
		if (infn) cnt++
	}
	END { print base, fname, foff, cnt * 4 }' "$asmfile")
[ $# -eq 4 ] || die "no function starts at $target@0x$addr: $asmfile has that address inside another function or in a data row."
base=$1 fname=$2 foff=$3 size=$4
rel=$((0x$addr - 0x$base))

# --- Candidate object (ninja, the recorded edge) ---------------------------------------

src=$(printf %s "$obj" | sed 's/\.o$//; s/+/\//g')
[ -f "$src" ] || die "no source $src for $obj"
cand=$obj
if grep -Eq "^NON_MATCHING[^(]*[ *]$fname\(" "$src"; then
	cand=draft+${obj#src+}
	draft=1
else
	draft=
fi
log=$(mktemp "${TMPDIR:-/tmp}/match.XXXXXX")
tmp=$(mktemp -d "${TMPDIR:-/tmp}/match.XXXXXX")
trap 'rm -rf "$log" "$tmp"' EXIT
if ! ninja -C "$B" "$cand" >"$log" 2>&1; then
	sed -n '1,40p' "$log" >&2
	die "ninja could not build $cand. Fix the compile error above; a new file or header needs: meson setup --reconfigure $B"
fi
co=$B/$cand
if [ ! -s "$co" ]; then
	# A draft object is empty when the draft does not compile; run its command to show why.
	cmd=$(ninja -C "$B" -t commands "$cand" | tail -n 1 | sed 's/ --empty-on-failure//')
	(cd "$B" && sh -c "$cmd") 2>&1 | sed -n '1,10p' >&2 || :
	die "the draft in $src does not compile (error above). Fix it and run again."
fi

# The function must come from C: an INCLUDE_ASM of this address makes the object equal retail.
for f in $(grep -lE "^ +/\* [0-9A-F]+ $addr " "asm/$target"/*.s "asm/$target"/hand/*.s 2>/dev/null || :); do
	if ninja -C "$B" -t deps "$cand" | grep -q "^ *\.\./\.\./$f\$"; then
		die "$fname in $src is still INCLUDE_ASM$([ -z "$draft" ] || printf ' (the draft compiled it from %s)' "$f"): the object holds the retail assembly, not your C."
	fi
done

# --- Candidate bytes -------------------------------------------------------------------

"$BIN/nm" -S "$co" >"$tmp/nm.txt"
# shellcheck disable=SC2046 # the output is a few fields to split
set -- $(awk -v n="$fname" '$NF == n && $(NF - 1) ~ /^[Tt]$/ && NF == 4 { print $1, $2; exit }' "$tmp/nm.txt")
[ $# -eq 2 ] || {
	there=$(awk -v r="$rel" 'function hex(s, n, i) { n = 0; for (i = 1; i <= length(s); i++) n = n * 16 + index("0123456789abcdef", tolower(substr(s, i, 1))) - 1; return n }
		NF == 4 && $3 ~ /^[Tt]$/ && $4 !~ /\.NON_MATCHING$/ && hex($1) == r { print $4; exit }' "$tmp/nm.txt")
	die "$co defines no text symbol '$fname'${there:+; the symbol at +0x$(printf %X "$rel") is '$there'}. The C name must equal the symbol in [$target] of config/symbols.toml: rename the definition in $src, or the symbol."
}
coff=$((0x$1)) csize=$((0x$2))

# Relocations in the function that point into the unit's own data (a section, or a symbol the
# object defines in .data/.rodata/.bss) or use the gp are not covered.
refused=$("$BIN/objdump" -r -j .text "$co" | awk -v lo="$coff" -v hi="$((coff + csize))" '
	NR == FNR { if ($(NF - 1) ~ /^[DdBbRrGgSsCc]$/) own[$NF] = 1; next }
	$2 ~ /^R_MIPS_/ {
		o = $1; n = 0
		for (i = 1; i <= length(o); i++) n = n * 16 + index("0123456789abcdef", tolower(substr(o, i, 1))) - 1
		if (n < lo || n >= hi) next
		if (($3 ~ /^\./ && $3 !~ /^\.text/) || $3 in own) { print "own " $3; exit }
		if ($2 ~ /GPREL|LITERAL|GOT/) { print "gp " $2; exit }
	}' "$tmp/nm.txt" -)
case $refused in
'') ;;
gp*) die "not covered: $fname uses the gp register (${refused#gp }); the partial link has no gp value. Run: meson compile -C $B check-$flat" ;;
*) die "not covered: $fname reads ${refused#own }, which its own unit defines (jump table, string, constant or data) and the partial link does not place. Run: meson compile -C $B check-$flat" ;;
esac

# Partial link: .text at the unit's retail address; every other symbol from the maps.
.venv/bin/python tools/link_symbols.py --root . --build-dir "$B" --target "$target" --partial "$co" \
	--output "$tmp/syms.ld" || die "the symbol maps cannot resolve a name of $co (message above)."
{
	printf 'SECTIONS {\n  .text 0x%s : { *(.text) }\n  .data 0x10 : { *(.data .sdata .rodata .rodata.* .lit4 .lit8 .sbss .bss .scommon COMMON) }\n  /DISCARD/ : { *(*) }\n}\n' "$base"
	for f in "build/asm/$target/undefined_syms_auto.txt" "build/asm/$target/undefined_funcs_auto.txt"; do
		[ ! -f "$f" ] || cat "$f"
	done
	cat "$tmp/syms.ld"
	# shellcheck disable=SC2046 # the output is a few fields to split
	awk '
		/^(glabel|dlabel|jlabel) / { g = $2; next }
		g != "" && $1 == "/*" && $5 == "*/" { printf "PROVIDE(%s = 0x%s);\n", g, $3; g = "" }' \
		"asm/$target"/*.s $(ls "asm/$target"/hand/*.s 2>/dev/null || :)
} >"$tmp/link.ld"
link() { LC_ALL=C "$BIN/ld" -EL -e 0 -T "$tmp/link.ld" -o "$tmp/cand.elf" "$co" >"$tmp/ld.log" 2>&1; }
if ! link; then
	# A name left over may be a variable a C data unit of this image defines. Find the unit
	# that covers the name's address in splat.yaml and take the symbol's address from that
	# object's layout; the name only picks the unit.
	for sym in $(sed -n "s/.*undefined reference to \`\(.*\)'\$/\1/p" "$tmp/ld.log" | sort -u); do
		hint=${sym##*_}
		case $hint in
		[0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F][0-9A-F]) ;;
		*) continue ;;
		esac
		row=$(awk -v hint="$hint" '
			function hex(s,  n, i) { n = 0; s = tolower(s); sub(/^0x/, "", s); for (i = 1; i <= length(s); i++) n = n * 16 + index("0123456789abcdef", substr(s, i, 1)) - 1; return n }
			function dig(n,  s, i) { s = ""; for (i = 0; i < 8; i++) { s = substr("0123456789ABCDEF", n % 16 + 1, 1) s; n = int(n / 16) } return s }
			/^  - name:/ { start = vram = 0 }
			/^    start:/ { start = hex($2) }
			/^    vram:/ { vram = hex($2) }
			/^      - \[0x/ {
				l = $0; gsub(/[][,]/, " ", l); split(l, a, " ")
				if (a[3] !~ /^\./) next
				v = dig(vram + hex(a[2]) - start)
				if (v <= hint && v > best) { best = v; row = v " " a[3] " " a[4] }
			}
			END { print row }' "config/$target/splat.yaml") || row=
		set -- $row
		[ $# -eq 3 ] || continue
		dobj=${obj%+*.c.o}+$3.c.o
		ninja -C "$B" "$dobj" >/dev/null 2>&1 || continue
		"$BIN/nm" "$B/$dobj" |
			awk -v s="$sym" -v base="$1" -v want="$hint" -v sec="$2" '
				function hex(s,  n, i) { n = 0; s = tolower(s); for (i = 1; i <= length(s); i++) n = n * 16 + index("0123456789abcdef", substr(s, i, 1)) - 1; return n }
				function dig(n,  s, i) { s = ""; for (i = 0; i < 8; i++) { s = substr("0123456789ABCDEF", n % 16 + 1, 1) s; n = int(n / 16) } return s }
				$3 == s && $2 ~ (sec == ".data" ? "^[Dd]$" : sec == ".rodata" ? "^[Rr]$" : "^[Bb]$") && dig(hex(base) + hex($1)) == want { printf "PROVIDE(%s = 0x%s);\n", s, want }' >>"$tmp/link.ld"
	done
	# A C-defined variable with a plain name: take its address from the image's last link map.
	map=$B/$flat.map
	if [ -f "$map" ]; then
		for sym in $(sed -n "s/.*undefined reference to \`\(.*\)'\$/\1/p" "$tmp/ld.log" | sort -u); do
			awk -v s="$sym" '$2 == s && $1 ~ /^0x[0-9a-f]+$/ { printf "PROVIDE(%s = %s);\n", s, $1; exit }' "$map" >>"$tmp/link.ld"
		done
	fi
	link || {
		sed -n '1,6p' "$tmp/ld.log" >&2
		missing=$(sed -n "s/.*undefined reference to \`\(.*\)'\$/\1/p" "$tmp/ld.log" | sort -u | tr '\n' ' ')
		if [ -f "$map" ]; then
			die "link failed for $fname: ${missing}is in no map of [$target] in config/symbols.toml, asm/$target or $map. Add a row to [$target] of config/symbols.toml, then retry."
		fi
		die "link failed for $fname: ${missing}is in no map of [$target] in config/symbols.toml or asm/$target. If a C file of the image defines it, build the image once so its map exists (meson compile -C $B $flat.bin), then retry; otherwise add a row to [$target] of config/symbols.toml."
	}
fi
"$BIN/objcopy" -O binary -j .text "$tmp/cand.elf" "$tmp/text.bin"

# --- Compare ---------------------------------------------------------------------------

take() { tail -c "+$(($2 + 1))" "$1" | head -c "$3"; }
take "$payload" $((0x$foff)) "$size" >"$tmp/retail.bin"
take "$tmp/text.bin" $((coff)) "$csize" >"$tmp/cand.bin"
[ -z "${MATCH_CAND_OUT:-}" ] || cp "$tmp/cand.bin" "$MATCH_CAND_OUT"

dis() { # <file> <address of byte 0>: one line per instruction
	"$BIN/objdump" -D -b binary -m mips:3000 -EL --adjust-vma="$2" "$1" |
		awk -F'\t' '/^ *[0-9a-f]+:\t/ { sub(/^ +/, "", $1); printf "%s  %s  %s %s\n", toupper($1), $2, $3, $4 }'
}

want=$(printf '%s' "$target@0x$addr $fname")
scope=".text only, relocations resolved against the symbol maps; check-$flat is the gate"
if [ "$coff" -ne "$rel" ]; then
	printf 'differs: %s starts at +0x%X in the candidate, retail +0x%X: code before it in the unit has another size\n' "$fname" "$coff" "$rel"
	exit 1
fi
if cmp -s "$tmp/retail.bin" "$tmp/cand.bin"; then
	printf 'match: %s, %d bytes (%s)\n' "$want" "$size" "$scope"
	exit 0
fi
n=$(cmp "$tmp/retail.bin" "$tmp/cand.bin" 2>/dev/null | awk '/differ: /{ sub(/,.*/, "", $5); print $5 }' || :)
if [ -n "$n" ]; then
	w=$(((n - 1) / 4 * 4))
	at=$(printf '0x%08X' $((0x$addr + w)))
	take "$tmp/retail.bin" "$w" 4 >"$tmp/r4.bin"
	take "$tmp/cand.bin" "$w" 4 >"$tmp/c4.bin"
	printf 'differs: %s, first difference at %s (+0x%X, instruction %d of %d)\n' "$want" "$at" "$w" $((w / 4 + 1)) $((size / 4))
	printf '  retail    %s\n' "$(dis "$tmp/r4.bin" "$at")"
	printf '  candidate %s\n' "$(dis "$tmp/c4.bin" "$at")"
else
	printf 'differs: %s, candidate is %d bytes, retail %d; the common bytes are equal\n' "$want" "$csize" "$size"
fi
[ "$csize" -eq "$size" ] || printf '  size: candidate 0x%X, retail 0x%X\n' "$csize" "$size"
printf '  (%s)\n' "$scope"
exit 1
