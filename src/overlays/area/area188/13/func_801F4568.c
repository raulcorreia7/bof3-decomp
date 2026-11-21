#include "area188_13.h"

MATCH void func_801F4568(s32* pos_a, s32* pos_b, u8 shade) {
    LINE_F2* prim;
    DVECTOR  xy;

    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    Camera_ProjectPoint(pos_a, &xy);
    setXY0(prim, (u16)xy.vx, (u16)xy.vy);
    Camera_ProjectPoint(pos_b, &xy);
    prim->x1 = (u16)xy.vx;
    prim->y1 = (u16)xy.vy;
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_F2));
}
