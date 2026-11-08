#include "area085_13.h"

/* tried: local val with step==5/!=5, single work pointer, separate TASK_BYTES;
 * needs work pointer reloaded into $a1 for delay-slot sb to TASK_BYTES[1] during
 * jal Area_DrawScreenTint, and (step&1)+1 split across beq delay/jump delay */
INCLUDE_ASM(func_801F2E2C);
