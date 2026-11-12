#include "area170_13.h"

MATCH void func_801F3698(s16 x0, s16 y0, s16 x1, s16 y1, u16 x2, u16 y2, u8 r, u8 g, u8 b, u8 semi_trans) {
    POLY_F3* prim;

    prim = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(prim);
    SetSemiTrans(prim, semi_trans);
    setXY2(prim, x0, y0, x1, y1);
    prim->x2 = x2;
    prim->y2 = y2;
    setRGB0(prim, r, g, b);
    GFX_AddPrim(2, sizeof(POLY_F3));
}
