#include "area104_14.h"

MATCH void func_801F555C(s16 x, s16 y, u8 row) {
    SPRT* sprite;

    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 768, 256));
    sprite = GFX_CURSOR(SPRT);
    SetSprt(sprite);
    setWH(sprite, 0x50, 0x20);
    sprite->clut = WORLD_SPRITE_CLUT;
    setXY0(sprite, x, y);
    setUV0(sprite, 0, row * 0x20 + 0x78);
    setRGB0(sprite, 128, 128, 128);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));
}
