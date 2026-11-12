#include "area047_13.h"

MATCH void func_801F31F4(s16 scale) {
    VECTOR pos;

    GFX_AddDitheredDrawMode(1U, GetTPage(0, 1, 0x380, 0x100) & HALF_MASK);
    pos.vx = g_Game.members[0].pos.x.fixed;
    pos.vy = g_Game.members[0].pos.y.fixed;
    pos.vz = D_80145ECC + 0x800000;
    func_801F2DB4(&pos, scale, 0x60, 0);
}
