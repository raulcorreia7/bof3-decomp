#include "area174_13.h"

MATCH void func_801F3C8C(void) {
    GFX_PaletteFreeSlotOwner(g_Self);
    GFX_PaletteStartAnimation(SELF(u8), (u8*)D_801F66D4);
    SELF(Actor)->mirror = 1;
    Script_Select(9);
}
