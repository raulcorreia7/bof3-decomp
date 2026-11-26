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

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_SCENE_BACK, tpage);

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
            setVector(&SPAD(0u)->vectors[j], x_base + (D_801F3F34[row] << 7), y_base + (D_801F3F35[row] << 7), z_base - D_801F3F36[row] * depth);
            row += 3;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (s32*)((u8*)prim + 8), (s32*)((u8*)prim + 0x10), (s32*)((u8*)prim + 0x18),
                      (s32*)((u8*)prim + 0x20), &p, &flag);
        Area_ApplyTileToQuad((height << 16) | AREA106_QUAD_PART_WORD, prim, 1);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(POLY_FT4));
        n += 12;
    }
}
#else
INCLUDE_ASM(func_801F31DC);
#endif
