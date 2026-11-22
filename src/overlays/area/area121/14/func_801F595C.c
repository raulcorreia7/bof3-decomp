#include "area121_14.h"

/* Appends one textured torch gauge bar to the primitive cursor. */
MATCH void func_801F595C(s32 width, s32 palette) {
    POLY_FT4*       prim;
    TorchGaugeCells cells;

    prim  = (POLY_FT4*)g_GfxPrimCursor;
    cells = D_801F2C04;
    SetPolyFT4(prim);
    prim->tpage = getTPage(0, 0, 960, 0);
    prim->clut  = (cells.rows[(u8)palette].clut >> 4) | 0x7800;
    prim->x0    = 0xE4;
    prim->x1    = (u8)width + 0xE4;
    prim->y0    = 0x1D;
    prim->y1    = 0x1D;
    prim->x2    = prim->x0;
    prim->x3    = prim->x1;
    prim->y2    = prim->y0 + 0xA;
    prim->y3    = prim->y2;
    prim->u0    = cells.rows[(u8)palette].u;
    prim->u1    = prim->u0 + 4;
    prim->u2    = prim->u0;
    prim->u3    = prim->u1;
    prim->v0    = 0xD8;
    prim->v1    = 0xD8;
    setRGB0(prim, 0x80, 0x80, 0x80);
    prim->v2 = prim->v0 + 8;
    prim->v3 = prim->v2;
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, 0x28);
}
