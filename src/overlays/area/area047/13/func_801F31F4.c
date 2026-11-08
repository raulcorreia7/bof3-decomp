#include "area047_13.h"

MATCH void func_801F31F4(s16 arg0) {
    VECTOR pos;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x380, 0x100) & 0xFFFF, NULL);
    GFX_AddPrim(1U, sizeof(DR_MODE));
    pos.vx = D_80145EC4;
    pos.vy = D_80145EC8;
    pos.vz = D_80145ECC + 0x800000;
    func_801F2DB4(&pos, arg0, 0x60, 0);
}
