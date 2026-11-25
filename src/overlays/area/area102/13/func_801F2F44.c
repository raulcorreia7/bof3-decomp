#include "area102_13.h"

/* Draws eight stacked, widening quads over the task's cell, swaying with the frame count. */
MATCH void func_801F2F44(s32 steps) {
    POLY_FT4* prim;
    /* FAKE: retail keeps the scratchpad vector base in s7; a plain pointer or direct members move every saved register. */
    FAKE_REG(SVECTOR*, corners, "s7");
    s16* out;
    long p;
    long flag;
    s32  height;
    s32  i;
    s32  order;
    s32  phase;
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
    corners->vx               = x;
    g_ScratchPadVectors[0].vz = height - step - (order << 3);
    g_ScratchPadVectors[0].vy = y;
    RotTransPers(corners, (long*)D_1F800034, &p, &flag);
    spread   = step / 16 + 4 + ((i < 4) ? order / 2 : steps * 2);
    shade    = (7 - i) * 8 + 7;
    shade    = ((shade - phase) << 17) / (8 - steps);
    prim->x0 = prim->x2 = out[0] - spread;
    prim->x1 = prim->x3 = out[0] + spread;
    prim->y0 = prim->y1 = out[1] - spread;
    prim->y2 = prim->y3 = out[1] + spread;
    Area_ApplyTileToQuad((shade & 0xF80000) | AREA_CELL_QUAD_CODE, prim, 1);
    order += steps;
    Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, sizeof(POLY_FT4));
    i++;
    if (i < 8) {
        goto loop;
    }
}
