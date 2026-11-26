#include "area047_13.h"

/* Draws the animated ribbon around the actor. */
MATCH void func_801F34A0(void) {
    SVECTOR   position;
    SVECTOR   rotation;
    MATRIX    matrix;
    POLY_GT4* quad;
    long      depth;
    long      flag;
    s32       i;
    s32       angle;
    s32       shade;
    s32       u;
    s32       next;
    s32       last;

    PushMatrix();
    GFX_ADD_DITHERED_DRAW_MODE(4, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    rotation.vx = rotation.vy = rotation.vz = 0;
    position.vx                             = SELF(Actor)->pos.x.fixed;
    position.vy                             = SELF(Actor)->pos.y.fixed;
    position.vz                             = SELF(Actor)->pos.z.fixed;
    RotTransMatrix(&position, matrix, &flag);
    RotMatrix(&rotation, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    i = 0;
    u = 40;
    for (; i < 16; i++) {
        quad = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(quad);
        SetShadeTex(quad, 0);
        quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);
        setUV4(quad, u - i * 2 - i / 2, 112, u - i / 2 - i * 2 - ((i & 1) + 2), 112, u - i * 2 - i / 2, 144, u - i / 2 - i * 2 - ((i & 1) + 2), 144);
        quad->clut = getClut(240, 483);
        shade      = g_FrameCount * 512;
        if (i == 0) {
            angle = shade & 0xFFF;
        } else {
            angle = (shade + (i - 1) * 512) & 0xFFF;
        }
        shade    = rcos(angle);
        quad->b0 = i == 0 ? (u32)i + 128 : (u32)(shade * (i - 1) >> 11) + 128;
        quad->r0 = quad->g0 = quad->b0 = quad->b0;
        quad->r1 = quad->g1 = quad->b1 = quad->r2 = quad->g2 = quad->b2 = (rcos(((i + g_FrameCount) * 512) & 0xE00) * i >> 11) - 128;
        next                                                            = i + 1;
        quad->r3 = quad->g3 = quad->b3 = (rcos(((next + g_FrameCount) * 512) & 0xE00) * next >> 11) - 128;

        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = i * 16;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = next * 16;
        angle                                                 = g_FrameCount * 512;
        if (i == 0) {
            angle &= 0xFFF;
        } else {
            angle = (angle - (i - 1) * 512) & 0xFFF;
        }
        shade                     = rsin(angle);
        g_ScratchPadVectors[0].vy = i == 0 ? (s16)i : shade * (i - 1) >> 12;
        shade                     = rsin(((g_FrameCount - i) * 512) & 0xE00) * i >> 12;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = shade;
        last                                                  = i + 1;
        g_ScratchPadVectors[3].vy                             = rsin(((g_FrameCount - last) * 512) & 0xE00) * last >> 12;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = -192;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = 0;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&quad->x0, (long*)&quad->x1, (long*)&quad->x2, (long*)&quad->x3,
                      &depth, &flag);
        GFX_AddPrim(4, sizeof(POLY_GT4));
    }
    GFX_ADD_LAYER_DRAW_MODE(4, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    PopMatrix();
}
