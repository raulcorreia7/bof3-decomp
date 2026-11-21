#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3CA8(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       y_top;
    s32       y_bottom;
    s32       i;

    y_top    = -0x2740;
    y_bottom = -0x2840;
    i        = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = -0x2940;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = y_top;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = y_bottom;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = COORD_FRAC(g_Task->pos.z);
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = FIX_FRAC(g_Task->pos.z.fixed + 0x100);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(AREA135_FLOOR_PART_WORD, prim, 1);
        Area_AddCellPrim(TO_COORD(44), TO_COORD(48 + i * 2), 0, sizeof(POLY_FT4));

        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = -0x2A40;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = COORD_FRAC(g_Task->pos.z);
        RotTransPers4(&g_ScratchPadVectors[3], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[0], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(AREA135_WALL_PART_WORD, prim, 1);
        Area_AddCellPrim(TO_COORD(44), TO_COORD(48 + i * 2), 0, sizeof(POLY_FT4));
        y_bottom += 0x100;
        y_top += 0x100;
        i++;
    } while (i < 4);
}
#else
INCLUDE_ASM(func_801F3CA8);
#endif
