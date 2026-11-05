#include "area030_04.h"

/* Configures the requested AREA030 sprite and its CLUT entry after
 * selecting graphics mode 1. */
MATCH void func_801E0F4C(s16 sprite_x, s16 sprite_y, u8 icon_index) {
    u16     clut;
    u32     sprite_index;
    SPRT*   sprite;

    func_801E0C80(1, 1);
    sprite = (SPRT*)func_801E0DCC(2, 1, sprite_x, sprite_y);
    sprite_index = icon_index & BYTE_MASK;
    if (sprite_index != GAME_NONE) {
        /* FAKE: base-hoist retains CLUT construction register order. */
        clut = (u16)(((icon_index >> 4) + 0x1EB) << 6);
        clut |= icon_index & 0x0F;
        sprite->clut = clut;
        sprite->u0   = (u8)((sprite_index & 3) << 6);
        sprite->v0   = (u8)((sprite_index >> 2) * 0x28);
    }
}
