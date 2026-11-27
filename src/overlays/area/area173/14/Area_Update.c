#include "area173_14.h"

MATCH void Area_Update(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       y;
    s32       x;
    s32       y1;
    s32       x1;
    s8        bias;

    g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) | 0x40;
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));

    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        bias = FAKE_VOLATILE(u8, D_801F4ED4[AREA_ROW_SCALE_OFFSET + i]); /* FAKE: retail loads the scale unsigned and sign-extends it apart; the volatile read keeps the two steps. */
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x7F) << 7) + (s16)(SELF(Actor)->screen_y * bias + 0x40);
        bias = FAKE_VOLATILE(u8, D_801F4ED4[AREA_ROW_SCALE_OFFSET + i]); /* FAKE: retail loads the scale unsigned and sign-extends it apart; the volatile read keeps the two steps. */
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = ((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) + (s16)(SELF(Actor)->screen_y * bias - 0x40);
        x                                                     = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
        y                                                     = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
        g_ScratchPadVectors[0].vz                             = -Area_HeightSample(x, y) / 2;
        g_ScratchPadVectors[2].vz                             = -Area_HeightSample(x, y) / 2 + 0x180;
        x1                                                    = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
        y1                                                    = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
        g_ScratchPadVectors[1].vz                             = -Area_HeightSample(x1, y1) / 2;
        g_ScratchPadVectors[3].vz                             = -Area_HeightSample(x1, y1) / 2 + 0x180;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad((0x179 << 16) | (0x11D - i), prim, 1);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
    }
}
