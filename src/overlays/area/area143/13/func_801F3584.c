#include "area143_13.h"

/* Draws the light beam's ring band: thirty-two textured quads between the rim at radius height and
 * the rim at radius y. */
MATCH void func_801F3584(s32 height, s32 y, s32 flag) {
    POLY_FT4* prim;
    s32       i;
    s32       j;
    s32       angle;
    s32       p;
    s32       otz;

    g_ScratchPad.unk_34[0] = -0x3A40;
    g_ScratchPad.unk_34[1] = -0x2F40;
    g_ScratchPad.unk_38    = -0x3C0;

    for (i = 0; i < 0x20; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);

        /* The rim at height. */
        for (j = 0; j < 2; j++) {
            angle = i + j;
            angle <<= 7;
            g_ScratchPadVectors[j].vx = g_ScratchPad.unk_34[0];
            g_ScratchPadVectors[j].vy = g_ScratchPad.unk_34[1] - ((rsin(angle) * height) >> 13);
            g_ScratchPadVectors[j].vz = g_ScratchPad.unk_38 + ((rcos(angle) * height) >> 13);
        }

        /* The rim at y. */
        for (j = 0; j < 2; j++) {
            angle = i + j;
            angle <<= 7;
            g_ScratchPadVectors[j + 2].vx = g_ScratchPad.unk_34[0];
            g_ScratchPadVectors[j + 2].vy = g_ScratchPad.unk_34[1] - ((rsin(angle) * y) >> 13);
            g_ScratchPadVectors[j + 2].vz = g_ScratchPad.unk_38 + ((rcos(angle) * y) >> 13);
        }

        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &otz);

        SetSemiTrans(prim, 0);
        /* The chained store writes b0 first, as retail does. */
        prim->r0 = prim->g0 = prim->b0 = 0x50;
        prim->clut                     = getClut(0, 485);
        prim->tpage                    = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, (flag << 7) + 0x140, 256);
        setUV4(prim, D_801F4320[flag][0] + ((rsin(i << 7) * height) >> 16), D_801F4320[flag][1] + ((rcos(i << 7) * height) >> 16), D_801F4320[flag][0] + ((rsin((i + 1) << 7) * height) >> 16),
               D_801F4320[flag][1] + ((rcos((i + 1) << 7) * height) >> 16), D_801F4320[flag][0] + ((rsin(i << 7) * y) >> 16), D_801F4320[flag][1] + ((rcos(i << 7) * y) >> 16),
               D_801F4320[flag][0] + ((rsin((i + 1) << 7) * y) >> 16), D_801F4320[flag][1] + ((rcos((i + 1) << 7) * y) >> 16));

        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 0, sizeof(POLY_FT4));
    }
}
