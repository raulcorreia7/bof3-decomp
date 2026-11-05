#include "area188_13.h"

MATCH void func_801F4568(s32* pos_a, s32* pos_b, u8 shade) {
    LINE_F2* prim;
    u16      xy[2];

    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    Area_ProjectPoint(pos_a, xy);
    prim->x0 = xy[0];
    prim->y0 = xy[1];
    Area_ProjectPoint(pos_b, xy);
    prim->x1 = xy[0];
    prim->y1 = xy[1];
    prim->r0 = shade;
    prim->g0 = shade;
    prim->b0 = 0;
    GFX_AddPrim(2, 0x10);
}
