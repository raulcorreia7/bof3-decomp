#include "area085_13.h"

MATCH void func_801F3B5C(void) {
    GFX_PaletteFreeSlotOwner(SP_REF(s32, 0x44));
    GFX_PaletteStartAnimation(SELF(Actor), D_801F4330);
    Script_Select(0);
}
