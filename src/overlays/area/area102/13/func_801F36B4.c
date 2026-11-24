#include "area102_13.h"

#ifdef NON_MATCHING
/* Draws eight stacked quads over the task's cell, each row raised by the task's
 * velocity and swaying with the frame count. */
NON_MATCHING void func_801F36B4(s32 steps) {
    POLY_FT4* prim;
    FAKE_REG(SVECTOR*, corners, "s7");
    s16* out;
    long depth;
    long flag;
    s32  height;
    s32  i;
    s32  order;
    s32  phase;
    s32  rise;
    s32  spread;
    s32  step;
    s32  x;
    s32  y;
    s32  shade;

    phase   = (g_FrameCount * 4) & 7;
    step    = phase * steps;
    x       = (COORD_INT(TASK(Actor)->pos.x) - 0x80) << 7;
    y       = (COORD_INT(TASK(Actor)->pos.y) - 0x80) << 7;
    height  = (s16) - (COORD_INT(TASK(Actor)->pos.z) / 2);
    i       = 0;
    corners = g_ScratchPadVectors;
    out     = D_1F800034;
    order   = 0;
loop:
    prim = g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    rise        = step + (order << 3);
    corners->vx = x + rise * TASK(Actor)->vx;
    D_1F800016  = y + rise * TASK(Actor)->vy;
    D_1F800018  = height;
    RotTransPers(corners, (long*)D_1F800034, &depth, &flag);
    spread   = step / 16 + 4 + ((i < 4) ? order / 2 : steps * 2);
    shade    = (((7 - i) * 8 + 7 - phase) << 17) / (8 - steps);
    /* Not setXYWH: retail adds the radius to each corner and stores the far corners first. */
    prim->x0 = prim->x2 = out[0] - spread;
    prim->x1 = prim->x3 = out[0] + spread;
    prim->y0 = prim->y1 = out[1] - spread;
    prim->y2 = prim->y3 = out[1] + spread;
    order += steps;
    Area_ApplyTileToQuad((shade & 0xF80000) | AREA_CELL_QUAD_CODE, prim, 1);
    prim->b0 = 0;
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 3, sizeof(POLY_FT4));
    i++;
    if (i < 8) {
        goto loop;
    }
}
#else
INCLUDE_ASM(func_801F36B4);
#endif
