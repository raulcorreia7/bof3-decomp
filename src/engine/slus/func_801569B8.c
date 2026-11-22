#include "engine/slus/slus.h"

/* Draws eight stacked quads over a cell, each wider and lower than the last, swaying with the frame count. */
MATCH void func_801569B8(u8* record, s32 cell_x, s32 cell_y) {
    long      p;
    long      flag;
    POLY_FT4* prim;
    s32       i;
    s32       phase;
    s32       spread;
    s32       sway;
    s32       swing;
    s32       step;
    s32       jitter;
    s32       height;
    SVECTOR*  corners;
    s32       z;
    s32       wave;

    height  = Area_HeightSample((cell_x - 1) << 16, cell_y << 16) / 2;
    height  = -height;
    cell_x  = (cell_x - 0x81) << 7;
    cell_y  = (cell_y - 0x80) << 7;
    i       = 0;
    corners = g_ScratchPadVectors;
    phase   = g_FrameCount & 7;
    z       = (s16)height - phase * 8;
    wave    = phase;
    for (; i < 8; i++) {
        prim = g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        jitter = rand() & 3;
        swing  = abs(16 - ((g_FrameCount & 0x1FFF) >> 8));
        step   = i * 32;
        step += 32;
        spread                 = phase * 4 + step + jitter;
        sway                   = wave * swing / 10;
        SPAD(0)->vectors[0].vz = z;
        SPAD(0)->vectors[1].vz = z;
        SPAD(0)->vectors[2].vz = z;
        SPAD(0)->vectors[3].vz = z;
        corners[0].vx          = cell_x - spread + sway;
        SPAD(0)->vectors[0].vy = cell_y - spread - sway;
        corners[1].vx          = cell_x + spread + sway;
        SPAD(0)->vectors[1].vy = cell_y - spread - sway;
        corners[2].vx          = cell_x - spread + sway;
        SPAD(0)->vectors[2].vy = cell_y + spread - sway;
        corners[3].vx          = cell_x + spread + sway;
        SPAD(0)->vectors[3].vy = cell_y + spread - sway;
        RotTransPers4(&corners[1], &corners[2], &corners[3], &corners[0], (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, (long*)&prim->x0, &p, &flag);
        Area_ApplyTileToQuad((((7 - i) * 8 + (7 - phase)) / 4) << 19 | 0xBA009124, prim, 1);
        GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_FT4));
        z -= 0x40;
        wave += 8;
    }
}
