#include "area060_13.h"

/* first differing instruction: addu v0,a3,a0 (retail) against addu t0,a3,a0 (candidate); an inlined GFX_AddPrim twin on a per-image OT table (setaddr of the table slot, slot = (g_FrameBufferIndex + 4) * 2); best form is 0x84 bytes against 0x88, the cursor sum lives in v0 in retail */
INCLUDE_ASM(func_801F3288);
