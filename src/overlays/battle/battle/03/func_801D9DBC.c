#define func_801D9DBC func_801D9DBC_decl_guard
#include "battle_03.h"
#undef func_801D9DBC

MATCH void func_801D9DBC(s16 x, s16 y, u8 template_index, u16 packed_color, u8 semi_trans) {
    TILE* tile;
    u16   color;
    u16   v;

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, x, y);
    tile->w = D_801EAE50[template_index * 2];
    color   = packed_color;
    v       = D_801EAE52[template_index * 2];
    setRGB0(tile, (color >> 7) & 0xF8, (color >> 2) & 0xF8, (packed_color & 0x1F) * 8);
    tile->h = v;
    SetSemiTrans(tile, semi_trans);
    GFX_AddPrim(1, sizeof(TILE));
}
