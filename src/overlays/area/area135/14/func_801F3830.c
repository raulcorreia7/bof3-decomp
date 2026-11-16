#include "area135_14.h"

/* Draws one sprite cell: texture picks its texture cell, cell its screen rectangle. */
MATCH void func_801F3830(s32 texture, s32 cell) {
    POLY_FT4* prim;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    setXY4(prim, D_801F6230[(u8)cell].x, D_801F6230[(u8)cell].y, D_801F6230[(u8)cell].x + D_801F6230[(u8)cell].w, D_801F6230[(u8)cell].y, D_801F6230[(u8)cell].x,
           D_801F6230[(u8)cell].y + D_801F6230[(u8)cell].h, D_801F6230[(u8)cell].x + D_801F6230[(u8)cell].w, D_801F6230[(u8)cell].y + D_801F6230[(u8)cell].h);
    setUVWH(prim, D_801F6248[(u8)texture][0], D_801F6248[(u8)texture][1], D_801F6248[(u8)texture][2], D_801F6248[(u8)texture][3]);
    setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    prim->clut  = GetClut(0, 0x1E8);
    prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 0x240, 0x100);
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
