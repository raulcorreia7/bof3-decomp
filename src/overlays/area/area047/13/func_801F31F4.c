#include "area047_13.h"

MATCH void func_801F31F4(s16 scale) {
    VECTOR pos;

    GFX_AddDitheredDrawMode(1U, GetTPage(0, 1, 0x380, 0x100) & 0xFFFF);
    pos.vx = D_80145EC4;
    pos.vy = D_80145EC8;
    pos.vz = D_80145ECC + 0x800000;
    func_801F2DB4(&pos, scale, 0x60, 0);
}
