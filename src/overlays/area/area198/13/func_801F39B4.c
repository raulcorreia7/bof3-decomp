#include "area198_13.h"

MATCH void func_801F39B4(void) {
    GFX_FreePaletteSlotOwner(g_Task);
    GFX_StartPaletteAnimation((u8*)g_Task, D_801F4368);
    g_Task->mirror = 1;
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    Actor_SelectScript(0);
}
