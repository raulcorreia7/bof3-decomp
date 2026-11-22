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
    s32       u;

    PushMatrix();
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_EFFECT, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    setVector(&rotation, 0, 0, 0x40 - abs(0x80 - (s32)((g_FrameCount * 2) & 0xFF)));
    position.vx = TASK(Actor)->pos.x.fixed;
    position.vy = TASK(Actor)->pos.y.fixed;
    position.vz = TASK(Actor)->pos.z.fixed;
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
        u           = 0x20 - i * 2;
        setUV4(quad, u, 0xC0, u - 2, 0xC0, u, 0xD8, u - 2, 0xD8);
        quad->clut = getClut(240, 483);
        angle      = (g_FrameCount * 512 + (i == 0 ? 0 : (i - 1) * 512)) & 0xFFF;
        shade      = rcos(angle);
        if (i == 0) {
            shade = 128;
        } else {
            shade = (shade * (i - 1) >> 11) + 128;
        }
        setRGB0(quad, shade, shade, shade);
        shade = (rcos(((i + g_FrameCount) * 512) & 0xE00) * i >> 11) - 128;
        setRGB1(quad, shade, shade, shade);
        setRGB2(quad, shade, shade, shade);
        shade = (rcos(((i + 1 + g_FrameCount) * 512) & 0xE00) * (i + 1) >> 11) - 128;
        setRGB3(quad, shade, shade, shade);

        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = -(i * 12);
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = -((i + 1) * 12);
        angle                                                 = (g_FrameCount * 512 - (i == 0 ? 0 : (i - 1) * 512)) & 0xFFF;
        shade                                                 = rsin(angle);
        g_ScratchPadVectors[0].vy                             = i == 0 ? 0 : (shade * (i - 1) >> 13);
        shade                                                 = (u32)(rsin(((g_FrameCount - i) * 512) & 0xE00) * i) >> 13;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy = shade;
        g_ScratchPadVectors[3].vy                             = rsin(((g_FrameCount - i - 1) * 512) & 0xE00) * (i + 1) >> 13;
        g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = -192;
        g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = 0;
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&quad->x0, (long*)&quad->x1, (long*)&quad->x2, (long*)&quad->x3,
                      &depth, &flag);
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_GT4));
    }
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F2D44);
#endif
