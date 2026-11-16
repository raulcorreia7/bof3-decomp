#include "area106_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F31DC(s32 depth, s32 height) {
    POLY_FT4* prim;
    s32       i;
    s32       j;
    s32       n;
    s32       row;
    s32       tpage;
    s32       x_base;
    s32       y_base;
    s32       z_base;
    long      p;
    long      flag;

    tpage = getTPage(1, 0, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(5, tpage);

    x_base = -0x37C0;
    y_base = -0x2DC0;
    z_base = -0x3F8;
    n      = 12;
    for (i = 1; i < 3; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        row = n;
        for (j = 0; j < 4; j++) {
            D_1F800014[j].vx = (D_801F3F34[row] << 7) + x_base;
            D_1F800014[j].vy = (D_801F3F35[row] << 7) + y_base;
            D_1F800014[j].vz = z_base - D_801F3F36[row] * depth;
            row += 3;
        }
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (s32*)((u8*)prim + 8), (s32*)((u8*)prim + 0x10), (s32*)((u8*)prim + 0x18), (s32*)((u8*)prim + 0x20), &p, &flag);
        func_80155560((height << 16) | AREA106_QUAD_PART_WORD, prim, 1);
        GFX_AddPrim(5, sizeof(POLY_FT4));
        n += 12;
    }
}
#else
INCLUDE_ASM(func_801F31DC);
#endif
