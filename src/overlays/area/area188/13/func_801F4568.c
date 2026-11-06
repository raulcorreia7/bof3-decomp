#include "area188_13.h"

MATCH void func_801F4568(s32* pos_a, s32* pos_b, u8 shade) {
    LINE_F2* prim;
    u16      xy[2];

    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    SetSemiTrans(prim, 1);
    Area_ProjectPoint(pos_a, xy);
    setXY0(prim, xy[0], xy[1]);
    Area_ProjectPoint(pos_b, xy);
    prim->x1 = xy[0];
    prim->y1 = xy[1];
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(2, 0x10);
}
