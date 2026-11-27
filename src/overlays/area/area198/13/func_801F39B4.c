#include "area198_13.h"

MATCH void func_801F39B4(void) {
    GFX_PaletteFreeSlotOwner(g_Self);
    GFX_PaletteStartAnimation(SELF(u8), D_801F4368);
    SELF(Actor)->mirror = 1;
    SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    Script_Select(0);
}
