#define func_801D99AC func_801D99AC_decl_guard
#include "battle_03.h"
#undef func_801D99AC

MATCH void func_801D99AC(s16 x, s16 y, u8 template_index) {
    TILE* tile;

    GFX_AddDrawMode(GetTPage(0, 2, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, x, y);
    *(u16*)&tile->w = D_801EAE50[template_index * 2];
    *(u16*)&tile->h = D_801EAE52[template_index * 2];
    setRGB0(tile, SP_REF(u8, 0), SP_REF(u8, 1), SP_REF(u8, 2));
    SetSemiTrans(tile, 1);
    GFX_AddPrim(1, 0x10);
}
