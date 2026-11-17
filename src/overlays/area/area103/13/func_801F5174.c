#include "area103_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5174(s32 steps, s32 radius) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s16       ground;
    s32       i;
    s32       j;
    s32       x;
    s32       y;
    s32       z;
    s32       size;
    s32       part;
    s32       phase;

    x      = (g_Task->pos.x.part.integer - 0x80) << 7;
    y      = (g_Task->pos.y.part.integer - 0x80) << 7;
    ground = (s16)(-Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) / 2);
    phase  = (g_FrameCount << 2) & 7;
    z      = ground - phase * steps;
    j      = 0;
    for (i = 0; i < 8; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        size                      = phase * steps / 4 + j * 2 + 8;
        g_ScratchPadVectors[0].vx = x - size;
        g_ScratchPadVectors[0].vy = y - size;
        g_ScratchPadVectors[0].vz = z - j * 8 + steps * 16;
        g_ScratchPadVectors[1].vx = x + size;
        g_ScratchPadVectors[1].vy = y - size;
        g_ScratchPadVectors[1].vz = z - j * 8;
        g_ScratchPadVectors[2].vx = x - size;
        g_ScratchPadVectors[2].vy = y + size;
        g_ScratchPadVectors[2].vz = z - j * 8;
        g_ScratchPadVectors[3].vx = x + size;
        g_ScratchPadVectors[3].vy = y + size;
        g_ScratchPadVectors[3].vz = z - j * 8 - steps * 16;
        RotTransPers4(&g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], &g_ScratchPadVectors[0], (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, (long*)&prim->x0,
                      &depth, &flag);
        part   = (7 - i) * 8 + 7 - phase;
        radius = part * (radius << 18) / 128 & (0xF8 << 16);
        Area_ApplyTileToQuad((part / 4 << 19) | (0xBA00 << 16) | 0x9124, prim, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
        j += steps;
    }
}
#else
INCLUDE_ASM(func_801F5174);
#endif
