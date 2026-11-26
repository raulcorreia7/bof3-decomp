#include "engine/game/00/game_00.h"

/* Draws the formatted work-record byte as 8x8 digit sprites starting at (x, y). */
/* func_8019F5B8 */
MATCH void Actor_DrawValueDigits(s16 x, s16 y, u8 unused, u8 palette) {
    SPRT* sprt;
    s32   index;
    s32   next;
    u8    ch;

    index = 0;
    TEXT_Format(g_UiTextFormatBuffer, D_80195860, SELF(Actor)->unk_06);
    GFX_ADD_LAYER_DRAW_MODE(SELF(Actor)->draw_layer, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    do {
        ch = g_UiTextFormatBuffer[index & BYTE_MASK];
        if (ch != ' ') {
            g_UiTextFormatBuffer[index & BYTE_MASK] = ch - '0';
            sprt                                    = (SPRT*)g_GfxPrimCursor;
            setClut(sprt, palette * 16, STAGE_PALETTE_Y);
            setRGB0(sprt, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
            setXY0(sprt, x, y);
            setUV0(sprt, g_UiTextFormatBuffer[index & BYTE_MASK] * 8 - 80, 208);
            setWH(sprt, 8, 8);
            SetSprt(sprt);
            GFX_AddPrim(SELF(Actor)->draw_layer, sizeof(SPRT));
        }
        x += 8;
        next  = index + 1;
        index = next;
    } while (g_UiTextFormatBuffer[next & BYTE_MASK] != 0);
}
