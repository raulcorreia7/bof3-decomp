#include "area140_13.h"

/* resume: best 5 differing pure C (first `!` +0x0: lui v0 vs v1, the actor row pointer register; the selector tail is exact with `u16 word = flag` after the range sub and `word & 0xFF == 7`, whose andi fills the bnez delay slot); exact bytes with MATCH_REG(Actor*, work, "v0") but `harmful` is a gated quality metric; next lever: keep the u16 view's andi without flipping the prologue v0/v1 tie. */
INCLUDE_ASM(func_801F3DAC);
