#include "engine/game/00/game_00.h"

/* func_801AEA80 */
/* Draws one 8x8 icon sprite at a screen position. */
MATCH void UI_IconDraw(s32 sprite_x, s32 sprite_y, s32 icon_id, s32 dimmed) {
    SPRT_8* sprite;
    s16     clut;

    GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    sprite = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(sprite);
    if ((dimmed & BYTE_MASK) == 0) {
        setRGB0(sprite, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    } else {
        setRGB0(sprite, 64, 64, 64);
    }

    setXY0(sprite, sprite_x, sprite_y);
    setUV0(sprite, (((icon_id & BYTE_MASK) * 8) + 56), 248);
    switch (icon_id & BYTE_MASK) {
        case 1:
        case 3:
        case 0xF:
            clut = getClut(224, 480);
            break;
        default:
            clut = getClut(192, 480);
            break;
    }
    sprite->clut = clut;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT_8));
}
