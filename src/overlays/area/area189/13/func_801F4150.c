#include "area189_13.h"

MATCH void func_801F4150(s32 shade, s32 x) {
    POLY_FT4* prim;
    s32       i;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    SetSemiTrans(prim, 1);
    setXYWH(prim, x, 0x48, 0x4E, 0x1E);
    setRGB0(prim, shade, shade, shade);
    prim->tpage = getTPage(1, 2, 448, 256);
    prim->clut  = getClut(0, 0x1E8);
    setUVWH(prim, 0, 0xC0, 0x4F, 0x1F);
    func_801F497C(sizeof(POLY_FT4));

    for (i = 0; i < 2; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        SetSemiTrans(prim, 1);
        setXYWH(prim, x, 0x48, 0x4E, 0x1E);
        setRGB0(prim, D_1F800014[i].vx * shade / 0x80, D_1F800014[i].vy * shade / 0x80, D_1F800014[i].vz * shade / 0x80);
        prim->tpage = getTPage(1, 1, 448, 256);
        prim->clut  = getClut(0, i + 0x1E6);
        setUVWH(prim, i * 0x50, 0xC0, 0x4F, 0x1F);
        func_801F497C(sizeof(POLY_FT4));
    }
}
