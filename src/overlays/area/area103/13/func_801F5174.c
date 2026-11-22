#include "area103_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5174(s32 steps, s32 radius) {
    POLY_FT4* prim;
    SVECTOR*  corners;
    long      depth;
    long      flag;
    s32       i;
    s32       j;
    s32       x;
    s32       y;
    s32       z;
    s32       size;
    s32       part;
    s32       phase;
    s32       span;
    s32       height;

    x       = (TASK(Actor)->pos.x.part.integer - 0x80) << 7;
    y       = (TASK(Actor)->pos.y.part.integer - 0x80) << 7;
    height  = (s16)Area_HeightSample(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) / 2;
    height  = -height;
    i       = 0;
    corners = g_ScratchPadVectors;
    phase   = (g_FrameCount << 2) & 7;
    span    = phase * steps;
    z       = (s16)height - span;
    j       = 0;
    for (; i < 8; i++) {
        prim = g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        size                   = span / 4 + (j * 2 + 8);
        corners[0].vx          = x - size;
        SPAD(0)->vectors[0].vy = y - size;
        SPAD(0)->vectors[0].vz = z - j * 8 + steps * 16;
        corners[1].vx          = x + size;
        SPAD(0)->vectors[1].vy = y - size;
        SPAD(0)->vectors[1].vz = z - j * 8;
        corners[2].vx          = x - size;
        SPAD(0)->vectors[2].vy = y + size;
        SPAD(0)->vectors[2].vz = z - j * 8;
        corners[3].vx          = x + size;
        SPAD(0)->vectors[3].vy = y + size;
        SPAD(0)->vectors[3].vz = z - j * 8 - steps * 16;
        RotTransPers4(&corners[1], &corners[2], &corners[3], &corners[0], (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, (long*)&prim->x0, &depth, &flag);
        part   = (7 - i) * 8 + (7 - phase);
        radius = part * (radius << 18) / 128 & (0xF8 << 16);
        Area_ApplyTileToQuad((part / 4 << 19) | (0xBA00 << 16) | 0x9124, prim, 1);
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 2, sizeof(POLY_FT4));
        j += steps;
    }
}
#else
INCLUDE_ASM(func_801F5174);
#endif
