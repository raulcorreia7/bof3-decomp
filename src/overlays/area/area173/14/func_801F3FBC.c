#include "area173_14.h"

/* Draws the three runs of the mode's board: a draw-mode packet and a projected quad per run. */
MATCH void func_801F3FBC(s32 mode, s32 value) {
    POLY_FT4* prim;
    s32       tpage;
    s32       i;
    s32       j;
    s8        factor;
    long      p;
    long      flag;

    factor        = D_801F530C[mode];
    D_1F800034[0] = (((FIX_INT(SELF(Actor)->pos.x.fixed) - 0x80) << 7) - 0x40) + mode * 0xC0 - (s16)SELF(Actor)->screen_y * factor;
    D_1F800034[1] = ((FIX_INT(SELF(Actor)->pos.y.fixed) - 0x80) << 7) - 0x40;

    i = 0;
    do {
        tpage = getTPage(1, 0, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, (s8)value, sizeof(DR_MODE));
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        for (j = 0; j < 4; j++) {
            g_ScratchPadVectors[j].vx = D_1F800034[0] + D_801F5310[i][j].x;
            g_ScratchPadVectors[j].vy = D_1F800034[1] + D_801F5310[i][j].y;
            g_ScratchPadVectors[j].vz = D_801F5310[i][j].z;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                      &flag);
        Area_ApplyTileToQuad(D_801F5358[SELF(Actor)->param.unk_0B][mode][i], prim, 1);
        i++;
        Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, (s8)value, sizeof(POLY_FT4));
    } while (i < 3);
}
