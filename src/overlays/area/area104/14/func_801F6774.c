#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F6774(void) {
    POLY_FT4* prim;
    POLY_F3*  triangle;
    s32       i;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    setPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->tpage = getTPage(0, 0, 896, 256);
    prim->clut  = 0x7BC6;
    setUV4(prim, 0, 0, 0x40, 0, 0, 0x40, 0x40, 0x40);
    setXY4(prim, 255, 134, 300, 179, 210, 179, 255, 224);
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(2, 0x28);

    for (i = 0; i < 4; i++) {
        triangle = (POLY_F3*)g_GfxPrimCursor;
        setPolyF3(triangle);
        SetSemiTrans(triangle, 1);
        triangle->x0 = D_801F6B2C[i][0];
        triangle->x1 = D_801F6B2C[i][1];
        triangle->x2 = D_801F6B2C[i][2];
        triangle->y0 = D_801F6B2C[i][3];
        triangle->y1 = D_801F6B2C[i][4];
        triangle->y2 = D_801F6B2C[i][5];
        setRGB0(triangle, 0, 0, 0xB8);
        GFX_AddPrim(2, 0x14);
    }

    if ((g_FrameCount & 7) == 0) {
        if ((g_FrameCount & 8) == 0) {
            D_800396C6 = 8;
        } else {
            D_800396C6 = 0x109F;
        }
        g_GfxPalettePending++;
    }
}
#else
INCLUDE_ASM(func_801F6774);
#endif
