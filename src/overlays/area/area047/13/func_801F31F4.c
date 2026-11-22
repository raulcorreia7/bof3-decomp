#include "area047_13.h"

MATCH void func_801F31F4(s16 scale) {
    VECTOR pos;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100) & HALF_MASK);
    setVector(&pos, g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, g_Game.members[0].pos.z.fixed + 0x800000);
    func_801F2DB4(&pos, scale, 0x60, 0);
}
