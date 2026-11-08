#include "area170_13.h"

MATCH void func_801F3594(s16 x0, s16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u8 r, u8 g, u8 b,
                         u8 semi_trans) {
    POLY_F4* prim;

    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, semi_trans);
    prim->x0 = x0;
    prim->y0 = y0;
    prim->x1 = x1;
    prim->y1 = y1;
    prim->x2 = x2;
    prim->y2 = y2;
    prim->x3 = x3;
    prim->y3 = y3;
    prim->r0 = r;
    prim->g0 = g;
    prim->b0 = b;
    GFX_AddPrim(2, 0x18);
}
