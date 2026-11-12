#include "game_00.h"

/* Sets no draw mode: the sprite uses the page its caller set with UI_DrawSpriteRun
 * (832, 256 when flags bit 0 is set, else 896, 256). The CLUT is (176, 481) when flags bit 1 is clear. */
MATCH void UI_DrawSprite(s16 x, s16 y, u8 sprite_id, u8 flags) {
    u8*   rect;
    SPRT* sprt;

    rect = UI_GetSpriteRect(sprite_id, flags & 0x1);
    sprt = (SPRT*)g_GfxPrimCursor;

    SetSprt(sprt);
    SetSemiTrans(sprt, 0);

    setXY0(sprt, x, y);

    setUV0(sprt, rect[0], rect[1]);
    setWH(sprt, rect[2], rect[3]);

    if (!(flags & 0x2)) {
        setClut(sprt, 176, STAGE_PALETTE_Y + 1);
    } else {
        setClut(sprt, 128, STAGE_PALETTE_Y + 2);
    }

    setRGB0(sprt, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    GFX_AddPrim(1, sizeof(SPRT));
}
