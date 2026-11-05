#include "area134_13.h"

/* resume: best 3 differing (the true-block spad reload and the 0x17 constant trade v0/v1: retail reload v0 / constant v1, ours reversed; the pointer local for D_80146865 fixes the selector reads - &D_80146865 in a0 across the tests and the clear); first `!` +0x2C (lui v0 vs v1); next lever: the permuter (work/permute/nonmatchings/func_801F33C0). */
INCLUDE_ASM(func_801F33C0);
