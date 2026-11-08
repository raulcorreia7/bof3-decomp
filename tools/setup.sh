#!/bin/sh
# Prepare a checkout: Python environment, pinned toolchain, retail payloads.
#
#   tools/setup.sh [--dev] [--matching] [--no-payloads] [--no-sdk]
#
#   --dev          also install pytest and Ruff
#   --matching     also install the matching tools and their submodules (implies --dev)
#   --no-payloads  skip the retail media; the disc-free checks still work
#   --no-sdk       skip the PsyQ 3.7 library objects; the toolchain and tracked headers remain
#
# Safe to run again: every step checks its result first. After it, run
#   meson setup build/meson && meson compile -C build/meson check
set -eu
cd "$(dirname "$0")/.."

dev=
matching=
payloads=1
sdk=1
for arg; do
	case $arg in
	--dev) dev=1 ;;
	--matching) dev=1 matching=1 ;;
	--no-payloads) payloads= ;;
	--no-sdk) sdk= ;;
	-h | --help)
		sed -n '2,11p' "$0" | sed 's/^# \{0,1\}//'
		exit 0
		;;
	*)
		echo "setup: unknown option $arg (see tools/setup.sh --help)" >&2
		exit 2
		;;
	esac
done

# Pinned downloads (SHA-256 checked before use).
GCC_URL=https://github.com/decompals/old-gcc/releases/download/0.13/gcc-2.7.2-psx.tar.gz
GCC_SHA256=aca64479041aa2d645dc52ebcaace276c0aa06f258c0e3f190ccf6d76701ffbc
PARSER_URL=https://github.com/mkst/maspsx/releases/download/aspsx/psyq-obj-parser
PARSER_SHA256=cadce246ea12f7419890f0a92835abae5c12ddc78c6b21ff66b2844a8eed2d83
BINUTILS_URL=https://github.com/Lameguy64/PSn00bSDK/releases/download/v0.24/gcc-mipsel-none-elf-12.3.0-linux.zip
BINUTILS_SHA256=228f031a25cf2687d8845fd1421f625bafc211fa27da428e458e80d030a726f8

# Host tools, all checked before anything changes.
missing=
for tool in git curl tar sha256sum unzip uv; do
	command -v "$tool" >/dev/null 2>&1 || missing="$missing $tool"
done
[ -z "$sdk" ] || command -v 7z >/dev/null 2>&1 || missing="$missing 7z"
if [ -n "$payloads" ]; then
	for tool in cargo cc; do
		command -v "$tool" >/dev/null 2>&1 || missing="$missing $tool"
	done
fi
if [ -n "$missing" ]; then
	echo "setup: missing host tools:$missing" >&2
	echo "setup: install them with your package manager (uv: https://docs.astral.sh/uv/, cargo: https://rustup.rs/), then run tools/setup.sh again" >&2
	exit 1
fi

step() { printf 'setup: %s\n' "$*"; }

# Submodules: a clone made without --recursive has them empty.
modules="third_party/maspsx"
[ -n "$payloads" ] && modules="$modules tools/bof3-tools"
[ -n "$matching" ] && modules="$modules third_party/decomp-permuter third_party/asm-differ third_party/m2c"
need=
for module in $modules; do
	case $(git submodule status -- "$module") in
	-*) need="$need $module" ;;
	esac
done
if [ -n "$need" ]; then
	step "submodules:$need"
	# shellcheck disable=SC2086
	git submodule update --init -- $need || {
		echo "setup: could not fetch:$need" >&2
		echo "setup: check the network and your access to the repository above, then run tools/setup.sh again" >&2
		echo "setup: without the disc extractor, run tools/setup.sh --no-payloads" >&2
		exit 1
	}
fi

# The disc extractor needs the Rust version its workspace declares; rustup's default can be older.
if [ -n "$payloads" ] && [ -z "${BOF3_CLI:-}" ]; then
	want=$(sed -n 's/^rust-version *= *"\([0-9.]*\)".*/\1/p' tools/bof3-tools/Cargo.toml)
	have=$(rustc --version 2>/dev/null | sed -n 's/^rustc \([0-9.]*\).*/\1/p')
	if [ -n "$want" ] && [ "$(printf '%s\n%s\n' "$want" "$have" | sort -V | head -n 1)" != "$want" ]; then
		echo "setup: the disc extractor needs Rust $want or later, but rustc $have is active here" >&2
		echo "setup: run: rustup default $want   then run tools/setup.sh again" >&2
		echo "setup: or set BOF3_CLI to a built bof3, or use --no-payloads (no disc work)" >&2
		exit 1
	fi
fi

# Python environment, locked. --inexact keeps groups installed earlier.
groups=
[ -n "$dev" ] && groups="--group dev"
[ -n "$matching" ] && groups="$groups --group matching"
step "python environment"
# shellcheck disable=SC2086
uv sync --locked --inexact --quiet $groups

# Compiler, object parser and binutils.
gcc_root=toolchains/gcc-2.7.2-psx
if [ ! -x "$gcc_root/gcc" ]; then
	step "GCC 2.7.2 PSX"
	sh tools/fetch_verified.sh "$GCC_URL" "$GCC_SHA256" toolchains/downloads/gcc-2.7.2-psx.tar.gz
	mkdir -p "$gcc_root"
	tar -xzf toolchains/downloads/gcc-2.7.2-psx.tar.gz -C "$gcc_root"
fi
parser=toolchains/psyq-compilers/psyq-obj-parser-cadce246
if [ ! -x "$parser" ]; then
	step "psyq-obj-parser"
	sh tools/fetch_verified.sh "$PARSER_URL" "$PARSER_SHA256" "$parser" --executable
fi
binutils=toolchains/psn00b_toolchain
if [ ! -x "$binutils/bin/mipsel-none-elf-as" ]; then
	step "PSn00b binutils"
	zip=toolchains/downloads/gcc-mipsel-none-elf-12.3.0-linux.zip
	sh tools/fetch_verified.sh "$BINUTILS_URL" "$BINUTILS_SHA256" "$zip"
	mkdir -p "$binutils"
	unzip -q -o "$zip" -d "$binutils"
	chmod +x "$binutils"/bin/*
fi

# PsyQ 3.7 library objects.
if [ -n "$sdk" ]; then
	sh tools/psyq.sh
else
	step "PsyQ library objects skipped"
fi

[ -n "$payloads" ] || {
	step "retail payloads skipped"
	exit 0
}

# Retail payloads from the disc image in inputs/external.
.venv/bin/python tools/setup.py

step "done. Next: meson setup build/meson && meson compile -C build/meson check"
command -v meson >/dev/null 2>&1 && command -v ninja >/dev/null 2>&1 ||
	step "meson and ninja are not installed; run: uv tool install meson && uv tool install ninja"
