#include "area140_13.h"

MATCH void func_801F3050(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       y;
    s32       x;
    s32       y1;
    s32       x1;

    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) + 0x40;
    g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x7F) << 7) + (SELF(Actor)->screen_y + 0x40);
    g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) + (s16)(SELF(Actor)->screen_y - 0x40);
    x                                                     = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
    y                                                     = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
    g_ScratchPadVectors[0].vz                             = -Area_HeightSample(x, y) / 2 + 0x40;
    g_ScratchPadVectors[2].vz                             = -Area_HeightSample(x, y) / 2 + 0x180;
    x1                                                    = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
    y1                                                    = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
    g_ScratchPadVectors[1].vz                             = -Area_HeightSample(x1, y1) / 2 + 0x40;
    g_ScratchPadVectors[3].vz                             = -Area_HeightSample(x1, y1) / 2 + 0x180;
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad((0x178 << 16) | 0x119, prim, 1);
    GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
}
