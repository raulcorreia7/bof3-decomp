#include "area104_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F6774(void) {
    POLY_FT4* prim;
    POLY_F3*  triangle;
    s32       i;
    u16       page;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    setPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->tpage = getTPage(0, 0, 896, 256);
    prim->clut  = 0x7BC6;
    prim->u1    = 0x40;
    prim->u3    = 0x40;
    prim->v2    = 0x40;
    prim->v3    = 0x40;
    prim->x1    = 300;
    prim->x2    = 210;
    prim->y0    = 134;
    prim->y1    = 179;
    prim->y2    = 179;
    prim->y3    = 224;
    prim->u0    = 0;
    prim->u2    = 0;
    prim->v0    = 0;
    prim->v1    = 0;
    prim->x0    = 255;
    prim->x3    = 255;
    prim->r0    = 0x80;
    prim->g0    = 0x80;
    prim->b0    = 0x80;
    GFX_AddPrim(2, 0x28);

    for (i = 0; i < 4; i++) {
        triangle = (POLY_F3*)g_GfxPrimCursor;
        setPolyF3(triangle);
        SetSemiTrans(triangle, 1);
        setXY3(triangle, D_801F6B2C[i][0], D_801F6B2C[i][3], D_801F6B2C[i][1], D_801F6B2C[i][4], D_801F6B2C[i][2], D_801F6B2C[i][5]);
        setRGB0(triangle, 0, 0, 0xB8);
        GFX_AddPrim(2, 0x14);
    }

    if ((g_FrameCount & 7) == 0) {
        if ((g_FrameCount & 8) == 0) {
            page = 8;
        } else {
            page = 0x109F;
        }
        D_800396C6 = page;
        g_GfxPalettePending++;
    }
}
#else
INCLUDE_ASM(func_801F6774);
#endif
