#include "area198_13.h"

MATCH void func_801F2E04(void) {
    GFX_PaletteFreeSlotOwner(g_Task);
    GFX_PaletteStartAnimation(TASK(u8), (u8*)D_801F4324);
    g_Task->mirror = 1;
    Script_Select(0);
}
