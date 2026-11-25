#include "area104_14.h"

MATCH void func_801F6774(void) {
    POLY_FT4* prim;
    POLY_F3*  triangle;
    s32       i;
    u16       tpage;
    u32       layer;
    u32       size;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    setPolyFT4(prim);
    SetSemiTrans(prim, 1);
    tpage       = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 896, 256);
    layer       = GFX_LAYER_EFFECT_FRONT;
    size        = sizeof(*prim);
    prim->tpage = tpage;
    prim->clut  = getClut(96, 495);
    prim->u1 = 0x40, prim->u3 = 0x40, prim->v2 = 0x40, prim->v3 = 0x40;
    prim->u0 = 0, prim->u2 = 0, prim->v0 = 0, prim->v1 = 0;
    prim->x0 = 255;
    prim->x1 = 300;
    prim->x2 = 210;
    prim->y0 = 134;
    prim->y2 = prim->y1 = 179;
    prim->y3            = 224;
    prim->x3            = 255;
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(layer, size);

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
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, 0x14);
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
