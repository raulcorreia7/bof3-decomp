# bof3-decomp

[![ci](https://github.com/raulcorreia7/bof3-decomp/actions/workflows/ci.yml/badge.svg)](https://github.com/raulcorreia7/bof3-decomp/actions/workflows/ci.yml)
[![C match](https://raulcorreia7.github.io/bof3-status/badge.svg)](https://raulcorreia7.github.io/bof3-status/)
[![License: CC0 1.0](https://img.shields.io/badge/license-CC0--1.0-blue.svg)](LICENSE)

A matching decompilation of *Breath of Fire III* (US, PlayStation). Each game function becomes
readable C89 that compiles to the retail bytes with the period compiler (GCC 2.7.2 PSX with maspsx).
The build reproduces all 428 code images of the game byte for byte.

A function is named `TARGET@0xADDRESS`, for example `exe/slus_004_22@0x8014AA04`; the same address in
two targets is two unrelated functions. Progress: [live status](https://raulcorreia7.github.io/bof3-status/).

## Requirements

Linux x86_64; on Windows use WSL2. You need `git`, `curl`, `tar`, `unzip`, `7z`, Python 3.12 or
later, [`uv`](https://docs.astral.sh/uv/), Rust with a C compiler, Meson 1.3 or later, Ninja,
`clang-format` 23.1.3 and [`dprint`](https://dprint.dev/) 0.64.3. `tools/setup.sh` downloads GCC
2.7.2 PSX, maspsx, MIPS binutils and PsyQ 3.7 and checks each by SHA-256. Versions and install
commands: [toolchain: host tools](docs/toolchain.md#host-tools).

The disc is a dump of the US release, serial `SLUS-00422`: a CUE sheet and two BIN tracks in
`inputs/external/` ([sizes and hashes](inputs/README.md)). Without a disc you can edit code and docs
and run the disc-free checks ([without a disc](docs/toolchain.md#without-a-disc)).

## Commands

```sh
tools/setup.sh --dev                   # .venv, toolchain and disc extraction; --matching adds the matching tools
meson setup build/meson                # the build graph; run again after a header or marker change
meson compile -C build/meson           # every image to build/meson/<image>.bin
meson compile -C build/meson check     # 428 images against the retail SHA-1; pre-push without a disc
```

The repository holds no disc image, executable, audio or other game media and no SDK object. Setup
keeps everything under `build/`, `inputs/` and `toolchains/`, which Git ignores; never commit or
share those files ([third-party tools](third_party/README.md)).

## Next

- [Your first match](CONTRIBUTING.md#your-first-match): find a function, match it, open a pull request.
- [Documentation](docs/README.md): toolchain, matching, naming, layout and the rest.
- [Tools](tools/README.md): every routine task as one command.

## License

[CC0 1.0](LICENSE) for what contributors wrote, to the extent they own the rights. *Breath of Fire
III* belongs to Capcom; this project claims no rights over Capcom's code, data or marks. The PsyQ
headers in `include/psyq/` are Sony's, included unmodified for interoperability. See [NOTICE](NOTICE).
