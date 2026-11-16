#include "area048_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3AE4(s32 angle, s32 pos, s32 variant) {
    SVECTOR   trans;
    SVECTOR   rot;
    MATRIX    matrix;
    long      flag;
    long      depth;
    POLY_FT4* prim;
    u32       word;
    u8        i;
    u8        j;
    s32       ofs;

    trans.vx = (pos >> 9) - 0x4000;
    trans.vy = -0x3A40;
    trans.vz = -0x80;
    rot.vx   = 0;
    rot.vy   = 0;
    rot.vz   = angle;
    PushMatrix();
    RotTransMatrix(&trans, matrix, &flag);
    Camera_SetModelMatrix(&rot, &matrix);
    for (i = 0; i < 8; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        word = D_801F4DF4[i * 2 + (variant & 1)];
        if (word == 0) {
            continue;
        }
        ofs = i * 0xC;
        for (j = 0; j < 4; j++) {
            D_1F800014[j].vx = D_801F4D94[ofs] << 7;
            D_1F800014[j].vy = D_801F4D95[ofs] << 7;
            D_1F800014[j].vz = -(D_801F4D96[ofs] * 320);
            ofs += 3;
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        word = D_801F4DF4[i * 2 + (variant & 1)];
        if ((word & 0xF80000) == 0) {
            word |= (((angle >> 5) & 0x38) + 0x50) << 16;
        }
        func_80155560(word, prim, 1);
        Area_AddCellPrim(pos, 0xB8000, D_801F4E34[(variant & 1) * 2 + i * 4 + (variant >> 4)], sizeof(POLY_FT4));
    }
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F3AE4);
#endif
