#include "area173_14.h"

/* resume: best 5 differing (the y value shares its lui in the branch delay slot but our build keeps it in a1 where retail merges it with the compare constant in v0; the x value splits lui/ori around the loads in retail); first `!` +0x4 (ori v0 vs lui a0 - retail splits the x value materialization around the loads); next lever: the permuter (work/permute/nonmatchings/func_801F4A4C), the empty-do-while anchor moved the split once already. */
INCLUDE_ASM(func_801F4A4C);
