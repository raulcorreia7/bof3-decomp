#include "game_00.h"

MATCH void func_801AE984(s32 sprite_x, s32 sprite_y, s32 texture_index, s32 dimmed) {
    SPRT_8* sprite;

    GFX_AddDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
    sprite = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(sprite);
    if ((dimmed & BYTE_MASK) == 0) {
        setRGB0(sprite, 0x7F, 0x7F, 0x7F);
    } else {
        setRGB0(sprite, 0x28, 0x28, 0x28);
    }

    setXY0(sprite, (sprite_x + 1), sprite_y);
    setUV0(sprite, (((texture_index & BYTE_MASK) * 8) - 56), 248);
    sprite->clut = GetClut(192, 480);
    GFX_AddPrim(1U, 0x10U);
}
