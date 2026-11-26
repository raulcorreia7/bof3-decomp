#include "area106_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2F38(s32 index, s32 height) {
    SVECTOR   pos;
    SVECTOR   rot;
    MATRIX    matrix;
    long      flag;
    long      depth;
    POLY_FT4* prim;
    u8*       start;
    u8*       tile;
    s32       j;

    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_SCENE_BACK, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256));

    setVector(&pos, -0x37C0, -0x2DC0, -0x480);
    setVector(&rot, 0, -height, 0);

    PushMatrix();
    RotTransMatrix(&pos, matrix, &flag);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    start = &D_801F3F18[index * 4];
    tile  = start;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        for (j = 0; j < 4; j++) {
            g_ScratchPadVectors[j].vx = D_801F3EE8[*tile][j].x << 7;
            g_ScratchPadVectors[j].vy = D_801F3EE8[*tile][j].y << 7;
            g_ScratchPadVectors[j].vz = -D_801F3EE8[*tile][j].depth << 7;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (s32*)&prim->x0, (s32*)&prim->x1, (s32*)&prim->x2, (s32*)&prim->x3, &depth,
                      &flag);
        Area_ApplyTileToQuad(D_801F3F20[*tile] + (((D_801F3F30[*tile] * height) << 8) & AREA106_TILE_WORD_MASK), prim, 1);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(POLY_FT4));
        tile++;
    } while (tile < start + 4);
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F2F38);
#endif
