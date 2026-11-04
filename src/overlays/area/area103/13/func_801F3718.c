#include "area103_13.h"

/* first differing instruction: lw a1,0x34(v0) (retail) against lw a0 (candidate) loading x; retail loads x, y, z into a1, a2, a0 and writes +0x20 as a halfword and +0x24 as the word 0x01000000, widths the Actor view lacks (needs: type). Locals, direct copies and a chained store tried. */
INCLUDE_ASM(func_801F3718);
