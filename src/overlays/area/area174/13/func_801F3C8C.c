#include "area174_13.h"

MATCH void func_801F3C8C(void) {
    GFX_PaletteFreeSlotOwner(g_Task);
    GFX_PaletteStartAnimation((u8*)g_Task, (u8*)D_801F66D4);
    g_Task->mirror = 1;
    Script_Select(9);
}
