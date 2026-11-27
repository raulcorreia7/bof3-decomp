#include "area077_14.h"

MATCH void func_801F54B8(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       x;
    s32       y;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    x    = SELF(Actor)->pos.x.fixed >> 9;
    y    = SELF(Actor)->pos.y.fixed >> 9;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = x - 0x4040;
    g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = x - 0x3F40;
    g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = y - 0x4030;
    g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = y - 0x3FD0;
    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = COORD_INT(SELF(Actor)->pos.z) - 0x30;
    g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = COORD_INT(SELF(Actor)->pos.z) + 0x30;
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad(AREA_SPIN_QUAD_WORD, prim, 1);
    Area_CellAddPrim(0x5D0000, 0x340000, 0, 0x28);
}
