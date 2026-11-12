#include "area030_04.h"

/* Draws a 0x28-byte textured quad at (x, y): the graph type selects
 * the tpage bits and the style-selected texture entry fills the UV and size
 * fields of the primitive. */
/* func_801D799C */
MATCH void Fishing_DrawWindowFill(s16 x, s16 y, u8 height, u8 style) {
    POLY_FT4* prim;
    u16       tpage;
    u16       x1;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);

    tpage       = getTPage(0, 0, D_801E218C[style].tpage, 256);
    prim->tpage = tpage;

    prim->clut = getClut(112, 482);
    prim->x0   = x;
    x1         = x + D_801E218C[style].width;
    prim->x1   = x1;
    prim->x2   = prim->x0;
    prim->y0   = y;
    prim->y1   = y;
    prim->y2   = prim->y0 + height;
    prim->y3   = prim->y2;
    prim->x3   = prim->x1;
    prim->u0   = D_801E218C[style].u;
    prim->u1   = prim->u0 + D_801E218C[style].width;
    prim->u2   = prim->u0;
    prim->u3   = prim->u1;
    prim->v0   = D_801E218C[style].v;
    prim->v1   = prim->v0;
    prim->v2   = prim->v0 + D_801E218C[style].v_span;
    prim->v3   = prim->v2;
    setRGB0(prim, 128, 128, 128);
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
