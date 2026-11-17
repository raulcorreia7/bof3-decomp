#include "area104_14.h"

MATCH void func_801F555C(s16 x, s16 y, u8 row) {
    SPRT* sprite;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 768, 256), NULL);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MODE));
    sprite = GFX_CURSOR(SPRT);
    SetSprt(sprite);
    setWH(sprite, 0x50, 0x20);
    sprite->clut = WORLD_SPRITE_CLUT;
    setXY0(sprite, x, y);
    sprite->v0 = row * 0x20 + 0x78;
    sprite->u0 = 0;
    setRGB0(sprite, 128, 128, 128);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));
}
