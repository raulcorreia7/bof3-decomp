#include "area098_13.h"

/* resume: best 10 differing, one swap/order cluster (the spad pointer and the 0xC0000 constant trade v1/a2; retail hoists the unk_6C load above the unk_2E load and the addu before the -6, the stores keep source order); first `!` +0x4 (lui v1 vs a2); next lever: the permuter (queue behind func_801F4A4C), or a statement shape whose unk_6C value load hoists while the unk_2E store stays first. */
INCLUDE_ASM(func_801F3994);
