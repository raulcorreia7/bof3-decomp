#include "area168_13.h"

/* Best 2 differing (permuter): hold the compare constant in a local and test
 * `state == one` — li v0,1 against li a0,1 at 0x801F49E4 and the bne operand.
 * Everything else matches with the s8 state local. Next lever: permuter from
 * this form (score 10 over four windows) or a form whose constant pseudo takes
 * v0 before the value. */
INCLUDE_ASM(func_801F49D4);
