#include "battle_15.h"

/* Draws the battle list box: the frame, the DATA/BEST title over the header, the
 * row and column guide lines and the corner posts that close them. The third and
 * fourth arguments are the panel task's bytes 8 and 9 the callers pass through. */
MATCH void Battle_DrawTitledFrame(s16 x, s16 y, s32 unused_a, s32 unused_b, u8 title_index) {
    u8* title;
    u8  i;
    s32 shift;
    u8* style;

    style = &g_WindowStyle;
    UI_WindowDraw(x + 3, y + 3, 137, 130, 0, *style);
    UI_WindowDraw(x + 3, y + 3, 137, 20, 0, *style);
    UI_WindowDraw(x + 3, y + 122, 137, 8, 0, *style);
    title = s_BattleFrameTitles[title_index];
    shift = (u8)Game_ReadCommand(title) * 4 - 70;
    UI_TextDraw(x - shift, y + 7, 0, MENU_LABEL_LENGTH, title);
    UI_SpriteDrawRun(x, y, D_800B6D44, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun(x, y, D_800B6D50, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 8; i++) {
        UI_SpriteDraw(x + (i + 5) * 8, y, 1, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; i < 12; i++) {
        UI_SpriteDraw(x, y + (i + 3) * 8, 4, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(x + 128, y + 24, 0x16, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 9; i++) {
        UI_SpriteDraw(x + 128, y + (i + 5) * 8, 0x17, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(x + 128, y + 112, 0x18, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(x, y + 120, 0x19, UI_SPRITE_ALT_PAGE);
    for (i = 0; i < 15; i++) {
        UI_SpriteDraw(x + (i + 1) * 8, y + 120, 0x1A, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw(x + 8, y, 0x32, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw(x + 128, y, 0x33, UI_SPRITE_ALT_PAGE);
}
