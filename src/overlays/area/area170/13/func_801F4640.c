#include "area170_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4640(s32 sample_height) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       x;
    s32       y;
    s16*      far_z;

    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = TASK(Actor)->screen_y - 0x3BC0;
    g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = TASK(Actor)->screen_y - 0x3AC0;
    far_z                     = &g_ScratchPadVectors[3].vz;
    for (i = 0; i < 2; i++) {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256), NULL);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, 0xC);
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = -0x3880 - (i << 4);
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = -0x3880;
        if (sample_height != 0) {
            y                         = ((s16)(-0x3880 - (i << 4)) + 0x4000) << 9;
            x                         = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
            g_ScratchPadVectors[0].vz = -Area_HeightSample(x, y) / 2;
            g_ScratchPadVectors[2].vz = -Area_HeightSample(x, y) / 2 + (i == 0 ? 0x180 : 0);
            x                        = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
            y                        = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
            g_ScratchPadVectors[1].vz = -Area_HeightSample(x, y) / 2;
            g_ScratchPadVectors[3].vz = -Area_HeightSample(x, y) / 2 + (i == 0 ? 0x180 : 0);
        } else {
            g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = -0x480;
            if (i == 0) {
                g_ScratchPadVectors[3].vz = -0x300;
            } else {
                g_ScratchPadVectors[3].vz = -0x480;
            }
            g_ScratchPadVectors[2].vz = *far_z = *far_z;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(D_801F58C8[i], prim, 1);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, 0x28);
    }
}
#else
INCLUDE_ASM(func_801F4640);
#endif
