#include "area172_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F4E8C(s32 x, s32 y) {
    POLY_FT4* prim;
    s32       left;
    s32       top;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    left = x;
    top  = y;
    x += 0x40;
    y += 0x20;
    setXY4(prim, left, top, x, top, left, y, x, y);
    setUVWH(prim, 0, 0, 0x40, 0x20);
    prim->clut  = GetClut(0, 0x1EB);
    prim->tpage = GetTPage(1, 1, 0x300, 0x100);
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801F4E8C);
#endif
