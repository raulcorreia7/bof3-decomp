#include "area048_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3AE4(u32 angle, s32 pos, s32 variant) {
    SVECTOR   trans;
    SVECTOR   rot;
    MATRIX    matrix;
    long      flag;
    long      depth;
    POLY_FT4* prim;
    u32       word;
    s32       i;
    s32       j;
    s32       k;
    s32       row;

    setVector(&trans, (pos >> 9) - 0x4000, -0x3A40, -0x80);
    setVector(&rot, 0, 0, angle);
    PushMatrix();
    RotTransMatrix(&trans, matrix, &flag);
    Camera_SetModelMatrix(&rot, &matrix);
    row = 0;
    for (i = 0; i < 8; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (D_801F4DF4[i * 2 + (variant & 1)] != 0) {
            for (j = 0; j < 4; j++) {
                k                         = row + j * 3;
                g_ScratchPadVectors[j].vx = D_801F4D94[k] * 128;
                g_ScratchPadVectors[j].vy = D_801F4D95[k] * 128;
                g_ScratchPadVectors[j].vz = -(D_801F4D96[k] * 320);
            }
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            word = D_801F4DF4[i * 2 + (variant & 1)];
            if ((word & 0xF80000) == 0) {
                word |= (((angle >> 5) & 0x38) + 0x50) << 16;
            }
            Area_ApplyTileToQuad(word, prim, 1);
            Area_CellAddPrim(pos, 0xB8000, D_801F4E34[(variant & 1) * 2 + i * 4 + (variant >> 4)], sizeof(POLY_FT4));
        }
        row += 12;
    }
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F3AE4);
#endif
