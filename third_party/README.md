# Third-party tools

This table lists every third-party tool and source the build, the matching tools and the references
use. The repository redistributes none of them except the PsyQ headers in `include/psyq/`; everything
else is a git submodule pin, a locked package or a download checked against a sha256. Licenses come
from each project's repository; read the upstream terms before you redistribute anything.

| Name | License | How obtained | Redistributed here |
| --- | --- | --- | --- |
| GCC 2.7.2 PSX ([old-gcc](https://github.com/decompals/old-gcc) 0.13) | GPL | `tools/setup.sh` downloads the release tarball | no |
| GNU binutils (PSn00bSDK `gcc-mipsel-none-elf` 12.3.0) | GPL | `tools/setup.sh` downloads the release zip | no |
| `psyq-obj-parser` | see [maspsx](https://github.com/mkst/maspsx) | `tools/setup.sh` downloads the release binary | no |
| PsyQ 3.7 SDK (objects and libraries) | Sony, proprietary | `tools/psyq.sh` fetches the archive from archive.org at your own responsibility | no |
| PsyQ 3.7 headers | Sony, proprietary | tracked in `include/psyq/`, unmodified, for interoperability | yes |
| `maspsx` | MIT | submodule | pin only |
| `decomp-permuter` | MIT | submodule | pin only |
| `asm-differ` | Unlicense | submodule | pin only |
| `m2c` | GPL-3.0 | submodule | pin only |
| `psx_psyq_signatures` | none stated | submodule | pin only |
| `splat64`, `spimdisasm` | MIT | Python packages locked in `uv.lock` | no |
| `objdiff-cli` | Apache-2.0 | release download in [docs/toolchain.md](../docs/toolchain.md#matching-tools) | no |
| `coddog` | Apache-2.0 | release download in [docs/toolchain.md](../docs/toolchain.md#matching-tools) | no |
| `rizin` | LGPL-3.0 | release download in [docs/toolchain.md](../docs/toolchain.md#matching-tools) | no |
| `bof3-data-doc` | none stated: cite only | submodule under `references/` | pin only |
| `vast-violence` | none stated: cite only | submodule under `references/` | pin only |
| `bof3-notes` | CC-BY-SA-4.0: cite, copy no text | submodule under `references/` | pin only |
| `bof3-save-editor` | none stated: cite only | submodule under `references/` | pin only |
| `bof3-script-editor` | MIT | submodule under `references/` | pin only |

Downloads that git cannot pin carry their sha256 in `tools/setup.sh` and `tools/psyq.sh`. The host
tools are listed in the [toolchain guide](../docs/toolchain.md#host-tools). `tools/setup.sh` installs
them.

Fetched sources are third-party code, not a home for repo-owned tooling. Before you patch a fork,
document the BOF3-specific reason and compare it with current upstream.

The `references/` submodules are commit-pinned research citations. No workflow installs or runs them.
A reference confirms a name or layout the retail code already supports; it is never the evidence by
itself. The community RAM map is in the wiki `game/records`; every source is listed in the wiki
`sources` page. A large repository is not a submodule: the wiki `sources` page links each file we cite
at the commit we read.
