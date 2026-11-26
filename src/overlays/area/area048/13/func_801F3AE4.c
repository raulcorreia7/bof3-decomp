#include "area048_13.h"

/* Draws the eight corner quads of the table turned by angle at pos; bit 0 of variant picks each quad's tile. */
// clang-format off
MATCH void func_801F3AE4(angle, pos, variant)
u16 angle;
s32 pos;
s32 variant;
// clang-format on
{
    SVECTOR   trans;
    SVECTOR   rot;
    MATRIX    matrix;
    long      flag;
    long      depth;
    POLY_FT4* prim;
    u32       word;
    s32       i;
    s32       j;

    trans.vx = (pos >> 9) - 0x4000;
    trans.vy = -0x3A40;
    rot.vx = rot.vy = 0;
    rot.vz          = angle;
    trans.vz        = -0x80;
    PushMatrix();
    RotTransMatrix(&trans, matrix, &flag);
    Camera_SetModelMatrix(&rot, &matrix);
    for (i = 0; i < 8; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        if (D_801F4DF4[i][variant & 1] != 0) {
            for (j = 0; j < 4; j++) {
                g_ScratchPadVectors[j].vx = D_801F4D94[i][j][0] * 128;
                g_ScratchPadVectors[j].vy = D_801F4D94[i][j][1] * 128;
                g_ScratchPadVectors[j].vz = -(D_801F4D94[i][j][2] * 320);
            }
            RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                          &depth, &flag);
            word = D_801F4DF4[i][variant & 1];
            if ((word & 0xF80000) == 0) {
                word |= (((angle >> 5) & 0x38) + 0x50) << 16;
            }
            Area_ApplyTileToQuad(word, prim, 1);
            Area_CellAddPrim(pos, 0xB8000, D_801F4E34[i][variant & 1][variant >> 4], sizeof(POLY_FT4));
        }
    }
    PopMatrix();
}
