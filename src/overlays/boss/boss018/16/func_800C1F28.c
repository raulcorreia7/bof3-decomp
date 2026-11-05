#include "boss018_16.h"

/* m2c draft: 6 differing. First diff at 800C1F4C: retail keeps 4 in a register (bne v1,v0) for slot == 4; if/else and inverted tests give sltiu/xori. Next lever: a different slot test or a loop shape. */
/* m2c draft: 6 differing. First diff at 800C1F4C: retail keeps 4 in a register (bne v1,v0) for slot == 4; if/else and inverted tests give sltiu/xori. Permuter, 13 min, best score 50: only candidates add a dead `if (D_801EB664)` branch (rejected). Next lever: a source-side slot view that keeps 4 live. */
INCLUDE_ASM(func_800C1F28);
