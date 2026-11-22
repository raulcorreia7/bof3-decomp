#include "area082_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4430(void) {
    SVECTOR   rot;
    SVECTOR   pos;
    MATRIX    matrix;
    long      flag;
    long      depth;
    POLY_FT4* prim;
    SVECTOR*  quad;
    s32       i;
    s32       next;
    s16       screen_y;
    s32       y;
    u32       tile;

    setVector(&pos, g_Task->pos.x.fixed, g_Task->pos.y.fixed, g_Task->pos.z.fixed);
    rot.vy = 0;
    rot.vx = 0;
    rot.vz = g_Task->unk_32;

    PushMatrix();
    RotTransMatrix(&pos, matrix, &flag);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    tile = (1U << 28) | (3U << 24) | (1U << 15) | (TPAGE_ABR_ADD << 12);
    if (g_Task->param.unk_0B != 0) {
        SND_PlaySE(g_Task->param.unk_0B + 0x201);
        g_Task->param.unk_0B = 0;
        tile |= 0x0F;
    } else {
        tile |= (1U << 11) | 0x0C;
    }

    quad = g_ScratchPadVectors;
    i    = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);

        quad[1].vy = 0;
        quad[0].vy = 0;
        quad[1].vx = 0;
        quad[0].vx = 0;
        quad[2].vx = (D_801F5764[i].x * 3) << 7;
        quad[2].vy = (D_801F5764[i].y * 3) << 7;
        next       = (i + 1) & 3;
        quad[3].vx = (D_801F5764[next].x * 3) << 7;
        quad[1].vz = -0x240;
        quad[0].vz = -0x240;
        quad[3].vy = (D_801F5764[next].y * 3) << 7;
        quad[3].vz = 0;
        quad[2].vz = 0;

        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);

        screen_y = g_Task->screen_y;
        if (screen_y >= 0x41) {
            y = g_Task->screen_y - ((rcos(g_Task->unk_32 + (i << 10)) >> 7) + 0x20);
        } else {
            y = screen_y;
        }
        Area_ApplyTileToQuad(((u32)(y & -8) << 16) | tile, prim, 1);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, 0x28);
        i++;
    } while (i < 4);

    PopMatrix();
}
#else
INCLUDE_ASM(func_801F4430);
#endif
