#include "area139_13.h"

MATCH void func_801F3504(s32 x, s32 y, s16 radius, u16 angle) {
    POLY_G3* prim;
    u8       i;

    i = 0;
    do {
        prim     = GFX_BeginPolyG3(1);
        prim->x0 = x;
        prim->y0 = y;
        prim->x1 = x + FIXED_MUL(radius, rcos(angle));
        prim->y1 = y + FIXED_MUL(radius, rsin(angle));
        angle += 0x100;
        prim->x2 = x + FIXED_MUL(radius, rcos(angle));
        i += 1;
        prim->y2 = y + FIXED_MUL(radius, rsin(angle));
        prim->r0 = D_801F442C[g_Task->unk_06 * 3];
        prim->g0 = D_801F442D[g_Task->unk_06 * 3];
        prim->b0 = D_801F442E[g_Task->unk_06 * 3];
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_G3));
    } while (i < 8);
}
