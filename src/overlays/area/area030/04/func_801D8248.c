#include "area030_04.h"

/* Draws the AREA030 menu icon: sets the FT4 header, picks the tpage
 * from the GPU graph type, maps the 0x58/0x9A texture cell over both halves of
 * the quad, and queues the 0x28-byte primitive. */
MATCH void func_801D8248(s16 x, s16 y, u8 height) {
    POLY_FT4* prim;
    s32       tpage;
    s16       bottom;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    tpage       = getTPage(0, 0, 832, 256);
    prim->x0    = x;
    prim->tpage = tpage;
    prim->clut  = getClut(112, 482);
    prim->x1    = x + 8;
    prim->u0    = 88;
    prim->u1    = 96;
    prim->v0    = 154;
    prim->v1    = 154;
    prim->y0    = y;
    setRGB0(prim, 128, 128, 128);
    bottom   = prim->y0;
    prim->y1 = y;
    prim->x2 = prim->x0;
    prim->x3 = prim->x1;
    prim->y2 = bottom + height;
    prim->y3 = bottom + height;
    prim->u2 = prim->u0;
    prim->u3 = prim->u1;
    prim->v2 = prim->v0 + 4;
    prim->v3 = prim->v2;
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
