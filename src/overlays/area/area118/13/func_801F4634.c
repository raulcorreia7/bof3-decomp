#include "area118_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4634(s32 tile_offset, s32 height) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    Actor*    task;
    s32       x;
    s32       sample_y0;
    s32       sample_y1;

    task                      = g_Task;
    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = (task->pos.x.part.integer - 0x80) * 0x80 + 0x40;
    g_ScratchPadVectors[0].vy = g_ScratchPadVectors[2].vy = (task->pos.y.part.integer - 0x80) * 0x80 + height - 8;
    g_ScratchPadVectors[1].vy = g_ScratchPadVectors[3].vy = (task->pos.y.part.integer - 0x80) * 0x80 - height + 8;

    x                         = (g_ScratchPadVectors[0].vx + 0x4000) << 9;
    sample_y0                 = (g_ScratchPadVectors[0].vy + 0x4000) << 9;
    g_ScratchPadVectors[0].vz = -Area_HeightSample(x, sample_y0) / 2 - g_Task->pos.z.part.integer - height + 8;
    g_ScratchPadVectors[2].vz = -Area_HeightSample(x, sample_y0) / 2 - g_Task->pos.z.part.integer + height;

    x                         = (g_ScratchPadVectors[1].vx + 0x4000) << 9;
    sample_y1                 = (g_ScratchPadVectors[1].vy + 0x4000) << 9;
    g_ScratchPadVectors[1].vz = -Area_HeightSample(x, sample_y1) / 2 - g_Task->pos.z.part.integer - height + 8;
    g_ScratchPadVectors[3].vz = -Area_HeightSample(x, sample_y1) / 2 - g_Task->pos.z.part.integer + height;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad(((0x2850 << 16) | 0xF3) + tile_offset, prim, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801F4634);
#endif
