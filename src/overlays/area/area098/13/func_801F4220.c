#include "area098_13.h"

MATCH void func_801F4220(AreaStreakSlot* slot) {
    LINE_G2* prim;
    DVECTOR  xy;

    prim = (LINE_G2*)g_GfxPrimCursor;
    SetLineG2(prim);
    SetSemiTrans(prim, 1);
    Area_ProjectPoint(slot->head, &xy);
    prim->x0 = xy.vx;
    prim->y0 = xy.vy;
    Area_ProjectPoint(slot->tail, &xy);
    prim->x1 = xy.vx;
    prim->y1 = xy.vy;
    prim->r0 = slot->head_shade;
    prim->g0 = slot->head_shade >> 1;
    prim->b0 = 0;
    prim->r1 = slot->tail_shade;
    prim->g1 = slot->tail_shade >> 1;
    prim->b1 = 0;
    GFX_AddPrim(2, sizeof(LINE_G2));
}
