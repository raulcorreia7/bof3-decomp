#include "area173_14.h"

/* Draws one sweep frame: each cell row builds an FT4 quad from the four vertex cells around its
 * cell pair, projects the quad and stages the cell origin for the sprite pass. */
MATCH void func_801F3954(s32 frame) {
    POLY_FT4* prim;
    u16*      slot;
    s32       part;
    s32       i;
    long      depth;
    long      flag;

    part = D_801F52E8[frame][0];
    if (part >= D_801F52E9[frame][0]) {
        return;
    }
    slot = D_1F800034_U16;
    while (part < D_801F52E9[frame][0]) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        slot[0] = (D_801F4F14[part].x << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        slot[1] = (D_801F4F14[part].y << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        for (i = 0; i < 4; i++) {
            g_ScratchPadVectors[i].vx = (slot[0] + D_801F4F14[part].cells[i][0] * 64) + slot[2];
            g_ScratchPadVectors[i].vy = slot[1] + D_801F4F14[part].cells[i][1] * 64;
            g_ScratchPadVectors[i].vz = slot[3] + 0x180 - D_801F4F14[part].cells[i][2] * 64;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad(D_801F4F14[part].cell, prim, 1);
        Area_CellAddPrim((D_801F4F14[part].x << 16) + (D_1F800038 << 9), D_801F4F14[part].y << 16, 0, sizeof(POLY_FT4));
        part++;
    }
}
