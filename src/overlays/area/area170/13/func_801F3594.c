#include "area170_13.h"

MATCH void func_801F3594(s16 x0, s16 y0, u16 x1, u16 y1, u16 x2, u16 y2, u16 x3, u16 y3, u8 r, u8 g, u8 b,
                         u8 semi_trans) {
    POLY_F4* prim;

    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, semi_trans);
    setXY4(prim, x0, y0, x1, y1, x2, y2, x3, y3);
    setRGB0(prim, r, g, b);
    GFX_AddPrim(2, sizeof(POLY_F4));
}
