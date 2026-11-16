#include "area117_13.h"

/* Lays the textured quad over the neighbouring cells at the actor's position. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F3884(s32 tile, s32 offset) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       x;
    s32       y;
    s32       x1;
    s32       y1;
    s32       lower;

    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = (((s32)g_Task->pos.x.part.integer - 0x80) << 7) + 0x40;
    g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = (((s32)g_Task->pos.y.part.integer - 0x80) << 7) + offset - 8;
    g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = (((s32)g_Task->pos.y.part.integer - 0x80) << 7) - offset + 8;
    lower                                                 = offset - 0x40;
    x                                                     = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
    y                                                     = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
    g_ScratchPadVectors[0].vz                             = -Area_SampleHeight(x, y) / 2 - lower + 8;
    g_ScratchPadVectors[2].vz                             = -Area_SampleHeight(x, y) / 2 + (offset + 0x40);
    x1                                                    = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
    y1                                                    = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
    g_ScratchPadVectors[1].vz                             = -Area_SampleHeight(x1, y1) / 2 - lower + 8;
    g_ScratchPadVectors[3].vz                             = -Area_SampleHeight(x1, y1) / 2 + (offset + 0x40);
    prim                                                  = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad(((0x2750 << 16) | 0xF3) + tile, prim, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801F3884);
#endif
