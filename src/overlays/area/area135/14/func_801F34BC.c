#include "area135_14.h"

/* Box: step * 25 wide, step * 6 high, centered on the (0xC8, 0x30) panel at
 * D_801F6210/D_801F6212, drawn by func_80159FA0 with s16 x and y, plus the unk_09
 * step counter. Best form: inline call arguments with STACK_PADS(u8, 8), 6
 * differing. First ! row: sll a3,a3,1 (retail) against sll a0,a0,16 at
 * 0x801F3534: the s16 x cast schedules before the height shift. In-body,
 * helper and local-variable forms all move the casts earlier; permuter 245
 * over 10k tries. Next lever: a form whose argument setup evaluates arg 4
 * before the arg 1 cast. */
INCLUDE_ASM(func_801F34BC);
