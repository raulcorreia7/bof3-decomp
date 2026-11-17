#include "area119_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3F04(s32 depth) {
    POLY_FT4* prim;
    long      p;
    long      flag;
    s32       i;

    i = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = -0x40C0;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = -0x40C0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = AREA_CELL_HALF;
        g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = AREA_CELL_HALF;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = depth;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_AddCellPrim(0, 0, depth, sizeof(POLY_FT4));
        i++;
    } while (i < 1);
}
#else
INCLUDE_ASM(func_801F3F04);
#endif
