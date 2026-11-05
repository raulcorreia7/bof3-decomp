#include "area191_13.h"

/* resume: best 8 differing, one register cluster (retail keeps the mode in v1 and merges the compare constant with the value accumulator in v0 - the accumulator def sits in the jump delay slot where the constant is dead on that path; our build splits v0/v1 and puts the mode in a0); the schedule and the delay-slot constant fold match; first `!` +0x00 (lui v1 vs a0); next lever: the permuter on the split (queue behind the area173 search), or a source shape that merges the accumulator with the compare constant. */
INCLUDE_ASM(func_801F3014);
