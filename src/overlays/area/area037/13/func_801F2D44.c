#include "area037_13.h"

#ifdef NON_MATCHING
/* Draws the rotating petal fan around the actor: sixteen Gouraud quads whose radius and shade
 * follow the frame count. */
NON_MATCHING void func_801F2D44(void) {
    SVECTOR   position;
    SVECTOR   rotation;
    MATRIX    matrix;
    POLY_GT4* quad;
    long      depth;
    long      flag;
    s32       i;
    s32       angle;
    s32       shade;
    s32       j;
    s32       k;

    PushMatrix();
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    rotation.vx = rotation.vy = 0;
    rotation.vz               = 0x40 - abs(0x80 - (s32)((g_FrameCount * 2) & 0xFF));
    position.vx               = TASK(Actor)->pos.x.fixed;
    position.vy               = TASK(Actor)->pos.y.fixed;
    position.vz               = TASK(Actor)->pos.z.fixed;
    RotTrans(&position, (VECTOR*)matrix.t, &flag);
    RotMatrix(&rotation, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    for (i = 0; i < 16; i++) {
        quad = (POLY_GT4*)g_GfxPrimCursor;
        SetPolyGT4(quad);
        SetShadeTex(quad, 0);
        quad->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 704, 256);
        setUV4(quad, 0x20 - i * 2, 0xC0, 0x1E - i * 2, 0xC0, 0x20 - i * 2, 0xD8, 0x1E - i * 2, 0xD8);
        quad->clut = getClut(240, 483);
        angle      = g_FrameCount * 512;
        shade      = rcos(i == 0 ? angle & 0xFFF : (angle + (i - 1) * 512) & 0xFFF);
        if (i == 0) {
            quad->b0 = 128;
        } else {
            s32 tint = (shade * (i - 1) >> 11) + 128;
            quad->b0 = tint;
        }
        quad->r0 = quad->g0 = quad->b0 = quad->b0;
        quad->r1 = quad->g1 = quad->b1 = quad->r2 = quad->g2 = quad->b2 = (rcos(((i + g_FrameCount) * 512) & 0xE00) * i >> 11) - 128;
        j                                                               = i + 1;
        quad->r3 = quad->g3 = quad->b3 = (rcos(((j + g_FrameCount) * 512) & 0xE00) * j >> 11) - 128;

        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = -i * 12;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = -j * 12;
        angle                                                 = g_FrameCount * 512;
        shade                                                 = rsin(i == 0 ? angle & 0xFFF : (angle - (i - 1) * 512) & 0xFFF);
        g_ScratchPadVectors[0].vy                             = i != 0 ? shade * (i - 1) >> 13 : 0;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = (u32)(rsin(((g_FrameCount - i) * 512) & 0xE00) * i) >> 13;
        k                                                     = i + 1;
        g_ScratchPadVectors[3].vy                             = rsin(((g_FrameCount - k) * 512) & 0xE00) * k >> 13;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = -144;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = 0;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&quad->x0, (long*)&quad->x1, (long*)&quad->x2, (long*)&quad->x3,
                      &depth, &flag);
        GFX_AddPrim(GFX_LAYER_BATTLE_SCENE, sizeof(POLY_GT4));
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_BATTLE_SCENE, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F2D44);
#endif
