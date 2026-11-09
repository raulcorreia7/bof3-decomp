#include "area077_14.h"

MATCH void func_801F3BC4(s16 x, s16 y, s16 w, s16 h) {
    TILE* tile = (TILE*)g_GfxPrimCursor;

    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->r0 = D_801F6B6C;
    tile->g0 = D_801F6B70;
    tile->x0 = x;
    tile->y0 = y;
    tile->w  = w;
    tile->h  = h;
    tile->b0 = D_801F6B74;
    GFX_AddPrim(1, 16);
}
