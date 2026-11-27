#include "area171_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3070(s32 mode) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       x;
    s32       y;
    s32       y1;
    s32       tpage;

    x                         = ((SELF(Actor)->pos.x.part.integer - 0x80) << 7) + 0x40;
    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = x;

    tpage = getTPage(1, 0, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_FIELD_SCENE, tpage);

    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        y                         = ((SELF(Actor)->pos.y.part.integer - 0x7F) << 7) + (SELF(Actor)->screen_y * (s8)D_801F3F84[i] + 0x40);
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = y;
        y1                                                    = ((SELF(Actor)->pos.y.part.integer - 0x80) << 7) + (SELF(Actor)->screen_y * (s8)D_801F3F84[i] - 0x40);
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = y1;

        if (mode != 0) {
            x                         = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
            y                         = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
            g_ScratchPadVectors[0].vz = -Area_HeightSample(x, y) / 2 - SELF(Actor)->pos.z.part.fraction - 0x180;
            g_ScratchPadVectors[2].vz = -Area_HeightSample(x, y) / 2 - SELF(Actor)->pos.z.part.fraction;
            x                         = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
            y1                        = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
            g_ScratchPadVectors[1].vz = -Area_HeightSample(x, y1) / 2 - SELF(Actor)->pos.z.part.fraction - 0x180;
            g_ScratchPadVectors[3].vz = -Area_HeightSample(x, y1) / 2 - SELF(Actor)->pos.z.part.fraction;
        } else {
            g_ScratchPadVectors[1].vz = g_ScratchPadVectors[3].vz = SELF(Actor)->unk_32;
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[2].vz = SELF(Actor)->unk_32 - 0x180;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad((SELF(Actor)->vx | (0x169 << 16)) | (0x130 - i), prim, 1);
        GFX_AddPrim(GFX_LAYER_FIELD_SCENE, sizeof(POLY_FT4));
    }
}
#else
INCLUDE_ASM(func_801F3070);
#endif
