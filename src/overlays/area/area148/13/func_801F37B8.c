#include "area148_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F37B8(s32 mode, s32 value) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       dir;
    s32       shift;
    s32       i;
    s32       n;
    s32       part_offset;
    s32       vertex_offset;
    s32       row_offset;

    dir         = mode & 1;
    shift       = dir << 7;
    part_offset = 0;
    for (i = 0; i < 3; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        row_offset    = part_offset;
        vertex_offset = 0;
        for (n = 0; n < 4; n++) {
            LOH(D_1F800014_BYTE[vertex_offset])     = LOHU(D_801F5038[row_offset]) + shift - g_Task->screen_y * (s8)D_801F5034[dir];
            LOH(D_1F800014_BYTE[vertex_offset + 2]) = LOHU(D_801F5038[row_offset + 2]);
            LOH(D_1F800014_BYTE[vertex_offset + 4]) = LOHU(D_801F5038[row_offset + 4]);
            row_offset += 6;
            vertex_offset += 8;
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        func_80155560(D_801F5080[mode * 3 + i], prim, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, (s8)value, sizeof(POLY_FT4));
        part_offset += 24;
    }
}
#else
INCLUDE_ASM(func_801F37B8);
#endif
