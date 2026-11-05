#include "area143_13.h"

/* Best shape so far: MEM_PTR addresses, stepping palette cursors and statement-form channel pack give the exact
 * prologue and loop tail; the residual is the entry/temp register permutation and the channel-compute order
 * (retail computes r,g,b,stp and folds the ors from stp). First differing instruction: lhu v1,0(a2) vs lhu a1
 * at 0x801F3E84. Next lever: the permuter. */
INCLUDE_ASM(func_801F3E60);
