# toolchains

Generated staging area; only this README is tracked. `tools/setup.sh` creates what is missing and
verifies the pinned digests. `inputs/` and `toolchains/` are read-only to an agent.

`tools/setup.sh` fetches the pinned GCC 2.7.2 PSX archive and the PSn00b binutils. The git tools under `third_party/` are submodules pinned by their gitlinks.

`tools/psyq.sh` stages PsyQ 3.7 from the release archive: each `LIB` member converted to
`toolchains/psyq/3.7/<lib>/<member>.o`. The headers are tracked in `include/psyq/`. The script uses a
local archive under `inputs/external/private-assets/psyq/3.7/` when present; otherwise it downloads
the archive and checks the pinned SHA-256.

`tools/setup.py` finishes setup by extracting the disc; it writes `build/`, not this directory.
`toolchains/rizin/` holds the Rizin release that `bin/rz` runs
([matching tools](../docs/toolchain.md#matching-tools)).

The host tools, setup order, compiler chain and PsyQ evidence are in
[docs/toolchain.md](../docs/toolchain.md).
