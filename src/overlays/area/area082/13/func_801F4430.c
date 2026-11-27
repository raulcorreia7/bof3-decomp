#include "area082_13.h"

/* Draws the four tiled sections of the actor's rotating ground ring. */
MATCH void func_801F4430(void) {
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

    setVector(&pos, SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->pos.z.fixed);
    rot.vy = 0;
    rot.vx = 0;
    rot.vz = SELF(Actor)->unk_32;

    PushMatrix();
    RotTransMatrix(&pos, matrix, &flag);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    if (SELF(Actor)->param.unk_0B != 0) {
        tile = (1U << 28) | (3U << 24) | (1U << 15) | (TPAGE_ABR_ADD << 12) | 0x0F;
        SND_SEPlay(SELF(Actor)->param.unk_0B + 0x201);
        SELF(Actor)->param.unk_0B = 0;
    } else {
        tile = (1U << 28) | (3U << 24) | (1U << 15) | (TPAGE_ABR_ADD << 12) | (1U << 11) | 0x0C;
    }

    i    = 0;
    quad = g_ScratchPadVectors;
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
        quad[3].vy = (D_801F5764[next].y * 3) << 7;
        quad[1].vz = -0x240;
        quad[0].vz = -0x240;
        quad[3].vz = 0;
        quad[2].vz = 0;

        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);

        screen_y = SELF(Actor)->screen_y;
        if (screen_y >= 0x41) {
            y = (rcos(SELF(Actor)->unk_32 + (i << 10)) >> 7) + 0x20;
            y = (s16)SELF(Actor)->screen_y - y;
        } else {
            y = screen_y;
        }
        Area_ApplyTileToQuad(tile | ((u32)(y & -8) << 16), prim, 1);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, 0x28);
        i++;
    } while (i < 4);

    PopMatrix();
}
