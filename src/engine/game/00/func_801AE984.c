#include "game_00.h"

MATCH void func_801AE984(s32 sprite_x, s32 sprite_y, s32 texture_index, s32 dimmed) {
    SPRT_8* sprite;

    GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    sprite = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(sprite);
    if ((dimmed & BYTE_MASK) == 0) {
        setRGB0(sprite, 127, 127, 127);
    } else {
        setRGB0(sprite, 40, 40, 40);
    }

    setXY0(sprite, (sprite_x + 1), sprite_y);
    setUV0(sprite, (((texture_index & BYTE_MASK) * 8) - 56), 248);
    setClut(sprite, 192, STAGE_PALETTE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT_8));
}
