#include "area104_14.h"

/* resume: best 7 differing (the shared-return skeleton matches: two gotos share the return-2, two share a return-0 stub, the leaves return directly; the residual is the code register tie (our build keeps the code in a0, retail in v1), the low/mid compare forms (retail li+bne with the return in the delay slot, ours xori/sltau) and the block layout at +0x40); first `!` +0x1C (andi v1 vs a0); next lever: the permuter on the skeleton in /tmp/a104d.c (the work variants dir), or a shape that keeps the code in v1. */
INCLUDE_ASM(func_801F66D0);
