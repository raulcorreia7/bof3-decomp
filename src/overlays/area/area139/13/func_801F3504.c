#include "area139_13.h"

MATCH void func_801F3504(s32 x, s32 y, s16 radius, u16 angle) {
    POLY_G3* prim;
    u8       i;

    i = 0;
    do {
        prim = GFX_BeginPolyG3(1);
        setXY2(prim, x, y, x + FIXED_MUL(radius, rcos(angle)), y + FIXED_MUL(radius, rsin(angle)));
        angle += 0x100;
        prim->x2 = x + FIXED_MUL(radius, rcos(angle));
        i += 1;
        prim->y2 = y + FIXED_MUL(radius, rsin(angle));
        setRGB0(prim, D_801F442C[SELF(Actor)->unk_06 * 3], D_801F442D[SELF(Actor)->unk_06 * 3], D_801F442E[SELF(Actor)->unk_06 * 3]);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_G3));
    } while (i < 8);
}
