#include "area042_13.h"

/* first differing instruction: addiu sp,sp,-40 (retail) against lui v0,0x1f80 (candidate). The body matches with state_70.word = 0, STACK_PADS(u32, 4) for the 0x28 frame and the step set as `if (!SYS_TestFlag(g_SceneEventFlags, 11)) 1 else 2`; retail
 * puts the frame adjust before the first scratchpad load. Pad type and place (u8, u16, u32), a work local and a second g_SpadWork read tried. */
INCLUDE_ASM(func_801F2C84);
