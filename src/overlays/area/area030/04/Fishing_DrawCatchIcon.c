#include "area030_04.h"

/* Configures the requested AREA030 sprite and its CLUT entry after
 * selecting graphics mode 1. */
/* func_801E0F4C */
MATCH void Fishing_DrawCatchIcon(s16 sprite_x, s16 sprite_y, u8 icon_index) {
    u16   clut;
    u32   sprite_index;
    SPRT* sprite;

    Fishing_SetDrawMode(1, 1);
    sprite       = (SPRT*)Fishing_DrawSprite(2, 1, sprite_x, sprite_y);
    sprite_index = icon_index & BYTE_MASK;
    if (sprite_index != GAME_NONE) {
        /* FAKE: base-hoist retains CLUT construction register order. */
        clut = (((icon_index >> 4) + 0x1EB) << 6);
        clut |= icon_index & 0xF;
        sprite->clut = clut;
        setUV0(sprite, ((sprite_index & 0x3) << 6), ((sprite_index >> 2) * 40));
    }
}
