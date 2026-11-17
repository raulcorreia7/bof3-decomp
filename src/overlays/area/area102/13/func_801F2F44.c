#include "area102_13.h"

#ifdef NON_MATCHING
/* Draws eight stacked, widening quads over the task's cell, swaying with the frame count. */
NON_MATCHING void func_801F2F44(s32 steps) {
    POLY_FT4* prim;
    SVECTOR*  corners;
    long      p;
    long      flag;
    s16       height;
    s32       i;
    s32       order;
    s32       phase;
    s32       spread;
    s32       step;
    s32       x;
    s32       y;
    u32       shade;

    phase   = (g_FrameCount * 4) & 7;
    step    = phase * steps;
    x       = (COORD_INT(g_Task->pos.x) - 0x80) << 7;
    y       = (COORD_INT(g_Task->pos.y) - 0x80) << 7;
    height  = -(COORD_INT(g_Task->pos.z) / 2);
    corners = g_ScratchPadVectors;
    i       = 0;
    order   = 0;
    for (; i < 8; i++) {
        FAKE_OPAQUE(steps);
        prim = g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        corners[0].vx     = x;
        SP_REF(s16, 0x18) = height - step - (order << 3);
        SP_REF(s16, 0x16) = y;
        RotTransPers(corners, (long*)D_1F800034, &p, &flag);
        spread   = step / 16 + 4 + ((i < 4) ? order / 2 : steps * 2);
        shade    = (((7 - i) * 8 + 7 - phase) << 17) / (8 - steps);
        prim->x0 = prim->x2 = D_1F800034[0] - spread;
        prim->x1 = prim->x3 = D_1F800034[0] + spread;
        prim->y0 = prim->y1 = D_1F800034[1] - spread;
        prim->y2 = prim->y3 = D_1F800034[1] + spread;
        order += steps;
        Area_ApplyTileToQuad((shade & 0xF80000) | AREA_CELL_QUAD_CODE, prim, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));
    }
}
#else
INCLUDE_ASM(func_801F2F44);
#endif
