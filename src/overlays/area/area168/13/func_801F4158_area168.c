#include "area168_13.h"

MATCH void func_801F4158_area168(s32 index, s32 row) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       y;
    s32       x;
    s32       y1;
    s32       x1;
    s16       h;
    s32       layer;

    layer                     = row; /* row arrives as the draw layer and is then reused */
    h                         = SELF(Actor)->screen_y * (s8)D_801F4BB4[index] + 0x40;
    row                       = index - 0x80;
    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + row) << 7) - h;
    h                                                     = SELF(Actor)->screen_y * (s8)D_801F4BB4[index] - 0x40;
    g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) + row) << 7) - h;
    g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = (FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), 0);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, (s8)layer, sizeof(DR_MODE));
    x                         = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
    y                         = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
    g_ScratchPadVectors[0].vz = -Area_HeightSample(x, y) / 2 - LOHU(SELF(Actor)->pos.z.part.integer) - 0x180;
    g_ScratchPadVectors[2].vz = -Area_HeightSample(x, y) / 2 - LOHU(SELF(Actor)->pos.z.part.integer);
    x1                        = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
    y1                        = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
    g_ScratchPadVectors[1].vz = -Area_HeightSample(x1, y1) / 2 - LOHU(SELF(Actor)->pos.z.part.integer) - 0x180;
    g_ScratchPadVectors[3].vz = -Area_HeightSample(x1, y1) / 2 - LOHU(SELF(Actor)->pos.z.part.integer);
    prim                      = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad(SELF(Actor)->gravity + index, prim, 1);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, (s8)layer, sizeof(POLY_FT4));
}
