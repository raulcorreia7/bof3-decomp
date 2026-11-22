#include "area198_13.h"

MATCH void func_801F39B4(void) {
    GFX_PaletteFreeSlotOwner(g_Task);
    GFX_PaletteStartAnimation(TASK(u8), D_801F4368);
    TASK(Actor)->mirror = 1;
    TASK(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    Script_Select(0);
}
