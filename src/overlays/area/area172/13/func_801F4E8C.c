#include "area172_13.h"

/* Draws the 64x32 textured panel with its top left corner at (x, y). */
MATCH void func_801F4E8C(s16 x, s16 y) {
    POLY_FT4* prim;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    setXYWH(prim, x, y, 0x40, 0x20);
    setUVWH(prim, 0, 0, 0x40, 0x20);
    prim->clut  = GetClut(0, 0x1EB);
    prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 0x300, 0x100);
    setRGB0(prim, 0x80, 0x80, 0x80);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}
