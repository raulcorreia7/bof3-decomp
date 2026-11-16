#include "area173_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3954(s32 frame) {
    AreaPart* row;
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       row_index;
    s32       k;

    row_index = D_801F52E8[frame * 2];
    if (row_index >= D_801F52E9[frame * 2]) {
        return;
    }
    row = &D_801F4F14[row_index];
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        D_1F800034[0] = (row->x << 7) - 0x4040;
        D_1F800034[1] = (row->y << 7) - 0x4040;
        for (k = 0; k < 4; k++) {
            D_1F800014[k].vx = D_1F800034[0] + (row->cells[k][0] << 6) + VOL(s16, D_1F800038);
            D_1F800014[k].vy = D_1F800034[1] + (row->cells[k][1] << 6);
            D_1F800014[k].vz = (VOL(s16, D_1F80003A) + 0x180) - (row->cells[k][2] << 6);
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        func_80155560(row->cell, prim, 1);
        Area_AddCellPrim((row->x << 16) + (D_1F800038 << 9), row->y << 16, 0, sizeof(POLY_FT4));
        row_index++;
        row++;
    } while (row_index < D_801F52E9[frame * 2]);
}
#else
INCLUDE_ASM(func_801F3954);
#endif
