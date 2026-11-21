#include "area098_13.h"

MATCH void func_801F4220(AreaStreakSlot* slot) {
    LINE_G2* prim;
    DVECTOR  xy;

    prim = (LINE_G2*)g_GfxPrimCursor;
    SetLineG2(prim);
    SetSemiTrans(prim, 1);
    Area_ProjectPoint(&slot->head.vx, &xy);
    setXY0(prim, xy.vx, xy.vy);
    Area_ProjectPoint(&slot->tail.vx, &xy);
    prim->x1 = xy.vx;
    prim->y1 = xy.vy;
    setRGB0(prim, slot->head_shade, slot->head_shade >> 1, 0);
    setRGB1(prim, slot->tail_shade, slot->tail_shade >> 1, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(LINE_G2));
}
