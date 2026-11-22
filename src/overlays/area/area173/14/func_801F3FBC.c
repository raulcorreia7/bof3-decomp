#include "area173_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3FBC(s32 mode, s32 value) {
    POLY_FT4* prim;
    s32       tpage;
    s32       i;
    s32       j;
    s8        factor;
    long      p;
    long      flag;

    factor        = D_801F530C[mode];
    D_1F800034[0] = ((COORD_INT(g_Task->pos.x) - 0x80) << 7) + mode * 0xC0 - 0x40 - g_Task->screen_y * factor;
    D_1F800036    = ((COORD_INT(g_Task->pos.y) - 0x80) << 7) - 0x40;

    i = 0;
    do {
        if (GetGraphType() == 1) {
            tpage = 0x225;
        } else if (GetGraphType() == 2) {
            tpage = 0x225;
        } else {
            tpage = 0x95;
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
        Area_CellAddPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, (s8)value, sizeof(DR_MODE));

        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        for (j = 0; j < 4; j++) {
            setVector(&g_ScratchPadVectors[j], D_1F800034[0] + LOHU(D_801F5310[i * 24 + j * 6]), D_1F800034[1] + LOHU(D_801F5312[i * 24 + j * 6]), LOHU(D_801F5314[i * 24 + j * 6]));
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_ApplyTileToQuad(D_801F5358[g_Task->param.unk_0B * 6 + mode * 3 + i], prim, 1);
        i++;
        Area_CellAddPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, (s8)value, sizeof(POLY_FT4));
    } while (i < 3);
}
#else
INCLUDE_ASM(func_801F3FBC);
#endif
