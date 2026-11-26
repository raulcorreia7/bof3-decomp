#include "area106_13.h"

/* Draws corner rows 1 and 2 of the quad table as back-scene quads, each depth byte scaled by depth. */
MATCH void func_801F31DC(s32 depth, s32 height) {
    POLY_FT4* prim;
    s32       i;
    s32       j;
    s32       tpage;
    s32       x_base;
    s32       y_base;
    s32       z_base;
    long      p;
    long      flag;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_SCENE_BACK, tpage);

    x_base = -0x37C0;
    y_base = -0x2DC0;
    z_base = -0x3F8;
    for (i = 1; i < 3; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        for (j = 0; j < 4; j++) {
            g_ScratchPadVectors[j].vx = x_base + (D_801F3F34[i][j][0] << 7);
            g_ScratchPadVectors[j].vy = y_base + (D_801F3F34[i][j][1] << 7);
            g_ScratchPadVectors[j].vz = z_base - D_801F3F34[i][j][2] * depth;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_ApplyTileToQuad((height << 16) | AREA106_QUAD_PART_WORD, prim, 1);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(POLY_FT4));
    }
}
