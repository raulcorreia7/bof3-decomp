#include "game_00.h"

MATCH void func_801AE984(s32 sprite_x, s32 sprite_y, s32 texture_index, s32 dimmed) {
    SPRT_8* sprite;

    /* GetGraphType() is probed twice; the second result is unused. */
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    GFX_AddDrawMode(0xF);
    sprite = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(sprite);
    if ((dimmed & 0xFF) == 0) {
        setRGB0(sprite, 0x7F, 0x7F, 0x7F);
    } else {
        setRGB0(sprite, 0x28, 0x28, 0x28);
    }

    setXY0(sprite, (sprite_x + 1), sprite_y);
    setUV0(sprite, (((texture_index & 0xFF) * 8) - 56), 248);
    sprite->clut = GetClut(192, 480);
    GFX_AddPrim(1U, 0x10U);
}
