#include "area148_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F37B8(s32 mode, s32 value) {
    POLY_FT4* prim;
    s32       i;
    s32       j;
    s32       half;
    s32       lift;
    long      depth;
    long      flag;

    half = mode & 1;
    lift = half << 7;
    i    = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        j = 0;
        do {
            D_1F800014[j].vx = LOHU(D_801F5038[i * 24 + j * 6]) + lift - g_Task->screen_y * (s8)D_801F5034[half];
            D_1F800014[j].vy = LOHU(D_801F5038[i * 24 + j * 6 + 2]);
            D_1F800014[j].vz = LOHU(D_801F5038[i * 24 + j * 6 + 4]);
            j++;
        } while (j < 4);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_ApplyTileToQuad(D_801F5080[mode * 3 + i], prim, 1);
        i++;
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, (s8)value, sizeof(POLY_FT4));
    } while (i < 3);
}
#else
INCLUDE_ASM(func_801F37B8);
#endif
