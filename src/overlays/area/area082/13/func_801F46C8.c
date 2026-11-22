#include "area082_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F46C8(s32 turn, s32 count, s32 angle, s32 height) {
    MATRIX   matrix;
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      j;
    s32      side;
    s32      tpage;

    PushMatrix();
    tpage = getTPage(0, 1, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_SCENE_BACK, tpage);

    RotTrans(&g_ScratchPadVectors[0], (VECTOR*)matrix.t, &flag);
    RotMatrix(&g_ScratchPadVectors[1], &matrix);
    RotMatrixZ(angle, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);

    for (i = turn; i < count; i++) {
        g_ScratchPadVectors[2].vx = g_ScratchPadVectors[3].vx = 0;
        g_ScratchPadVectors[2].vy                             = D_801F5764[i + 20].y * height;
        g_ScratchPadVectors[3].vy                             = D_801F5764[i + 21].y * height;
        g_ScratchPadVectors[2].vz                             = -D_801F5764[i + 20].x * 48;
        g_ScratchPadVectors[3].vz                             = -D_801F5764[i + 21].x * 48;

        j    = 0;
        side = -1;
        do {
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers3(&g_ScratchPadVectors[2], &g_ScratchPadVectors[3], &g_ScratchPadVectors[0], (long*)&prim->x0, (long*)&prim->x1, (long*)D_1F800034, &depth, &flag);
            setRGB0(prim, 0xC8, 0xB4, 0x0A);
            setRGB1(prim, 0xC8, 0xB4, 0x0A);
            setRGB2(prim, 0, 0, 0);
            setRGB3(prim, 0, 0, 0);
            prim->x2 = prim->x0 - side;
            prim->x3 = prim->x1 - side;
            prim->y2 = prim->y0 - side;
            prim->y3 = prim->y1 - side;
            GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(POLY_G4));
            side += 2;
            j++;
        } while (j < 2);
    }

    tpage = getTPage(0, 1, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_SCENE_BACK, tpage);
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F46C8);
#endif
