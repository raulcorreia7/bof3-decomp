#include "area198_13.h"

MATCH void func_801F39B4(void) {
    GFX_PaletteFreeSlotOwner(g_Task);
    GFX_PaletteStartAnimation(TASK(u8), D_801F4368);
    g_Task->mirror = 1;
    g_Task->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    Script_Select(0);
}
