#include "area148_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F37B8(s32 mode, s32 value) {
    POLY_FT4* prim;
    s32       i;
    s32       j;
    s32       k;
    s32       row;
    s16       half;
    s16       lift;
    long      depth;
    long      flag;

    half = mode & 1;
    lift = half << 7;
    i    = 0;
    row  = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        j = 0;
        do {
            k                         = row + j * 6;
            g_ScratchPadVectors[j].vx = LOHU(D_801F5038[k]) + lift - (s16)TASK(Actor)->screen_y * (s8)D_801F5034[half];
            g_ScratchPadVectors[j].vy = LOHU(D_801F5038[k + 2]);
            g_ScratchPadVectors[j].vz = LOHU(D_801F5038[k + 4]);
            j++;
        } while (j < 4);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(D_801F5080[mode][i], prim, 1);
        i++;
        row += 24;
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, (s8)value, sizeof(POLY_FT4));
    } while (i < 3);
}
#else
INCLUDE_ASM(func_801F37B8);
#endif
