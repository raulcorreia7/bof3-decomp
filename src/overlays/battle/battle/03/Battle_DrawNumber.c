#include "battle_03.h"

/* renders the formatted capture count as a row of digit sprites,
 * advancing eight pixels per glyph and skipping blanks.
 */
/* func_801D9684 */
MATCH void Battle_DrawNumber(s16 x, s16 y, u8 palette, u16 value) {
    u8    i;
    SPRT* prim;

    i = 0;
    TEXT_Format(g_UiFormatBuffer, D_801D0C78, value);
    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    do {
        if (g_UiFormatBuffer[i] != ' ') {
            g_UiFormatBuffer[i] -= '0';
            prim = (SPRT*)g_GfxPrimCursor;
            setClut(prim, palette * 16, STAGE_PALETTE_Y);
            setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
            setXY0(prim, x, y);
            setUV0(prim, (g_UiFormatBuffer[i] * 8) - 80, 208);
            setWH(prim, 8, 8);
            SetSprt(prim);
            GFX_AddPrim(1, sizeof(SPRT));
        }
        x += 8;
    } while (g_UiFormatBuffer[++i] != 0);
}
