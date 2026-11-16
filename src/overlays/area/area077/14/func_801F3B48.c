#include "area077_14.h"

MATCH void func_801F3B48(Pos2* pos, u8 shade) {
    TILE_1* tile = (TILE_1*)g_GfxPrimCursor;

    SetTile1(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, pos->vx, pos->vy);
    setRGB0(tile, shade, shade, shade);
    GFX_AddPrim(GFX_LAYER_UI, 12);
}
