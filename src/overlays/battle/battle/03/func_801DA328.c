#include "battle_03.h"

MATCH void func_801DA328(s16 x, s16 y, u8 u, u8 v, u8 clut_x) {
    SPRT* sprite;
    u16   clut;

    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));

    clut = clut_x;
    clut &= 0x3F;
    sprite = (SPRT*)g_GfxPrimCursor;
    setWH(sprite, 8, 8);
    sprite->clut = 0x7800 | clut;
    setRGB0(sprite, 128, 128, 128);
    sprite->v0 = v;
    sprite->u0 = u;
    setXY0(sprite, x, y);
    SetSprt(sprite);
    GFX_AddPrim(1, sizeof(SPRT));
}
