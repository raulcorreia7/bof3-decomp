#include "area103_13.h"

/* first differing instruction: lw a1,0x34(v0) (retail) against lw a0 (candidate) loading x; retail loads x, y, z into a1, a2, a0, writes +0x20 as a halfword (sh zero) and +0x24 as the word 0x01000000 (sw). Each width has this one access in the area code, so Actor keeps gravity as s32 and flags_24 as u8 (a union needs a second access); a Coord gravity with part.fraction = 0 is the candidate for +0x20. Locals, direct copies and a chained store tried. */
INCLUDE_ASM(func_801F3718);
