#include "area085_13.h"

MATCH void func_801F3B5C(void) {
    GFX_FreePaletteSlotOwner(SP_REF(s32, 0x44));
    GFX_StartPaletteAnimation(g_Task, D_801F4330);
    Actor_SelectScript(0);
}
