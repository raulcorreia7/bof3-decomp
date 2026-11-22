#include "battle_15.h"

/* Draws the battle list box: the frame, the DATA/BEST title over the header, the
 * row and column guide lines and the corner posts that close them. The third and
 * fourth arguments are the panel task's bytes 8 and 9 the callers pass through. */
#ifdef NON_MATCHING
NON_MATCHING void Battle_DrawTitledFrame(s32 x, s16 y, s32 unused_a, s32 unused_b, u8 title_index) {
    u8* title;
    s32 i;

    UI_WindowDraw((x + 3) & HALF_MASK, (y + 3) & HALF_MASK, 137, 130, 0, g_WindowStyle);
    UI_WindowDraw((x + 3) & HALF_MASK, (y + 3) & HALF_MASK, 137, 20, 0, g_WindowStyle);
    UI_WindowDraw((x + 3) & HALF_MASK, (y + 122) & HALF_MASK, 137, 8, 0, g_WindowStyle);

    title = s_BattleFrameTitles[title_index];
    UI_TextDraw((s16)(x - (((u8)Game_ReadCommand(title) * 4) - 70)), (s16)(y + 7), 0, MENU_LABEL_LENGTH, title);

    UI_SpriteDrawRun((s16)x, y, D_800B6D44, UI_SPRITE_ALT_PAGE);
    UI_SpriteDrawRun((s16)x, y, D_800B6D50, UI_SPRITE_ALT_PAGE);

    for (i = 0; (u32)(i & BYTE_MASK) < 8U; i++) {
        UI_SpriteDraw((s16)(x + (((i & BYTE_MASK) + 5) * 8)), y, 1, UI_SPRITE_ALT_PAGE);
    }
    for (i = 0; (u32)(i & BYTE_MASK) < 12U; i++) {
        UI_SpriteDraw((s16)x, (s16)(y + (((i & BYTE_MASK) + 3) * 8)), 4, UI_SPRITE_ALT_PAGE);
    }

    UI_SpriteDraw((s16)(x + 128), (s16)(y + 24), 0x16, UI_SPRITE_ALT_PAGE);
    for (i = 0; (u32)(i & BYTE_MASK) < 9U; i++) {
        UI_SpriteDraw((s16)(x + 128), (s16)(y + (((i & BYTE_MASK) + 5) * 8)), 0x17, UI_SPRITE_ALT_PAGE);
    }
    UI_SpriteDraw((s16)(x + 128), (s16)(y + 112), 0x18, UI_SPRITE_ALT_PAGE);

    UI_SpriteDraw((s16)x, (s16)(y + 120), 0x19, UI_SPRITE_ALT_PAGE);
    for (i = 0; (u32)(i & BYTE_MASK) < 15U; i++) {
        UI_SpriteDraw((s16)(x + (((i & BYTE_MASK) + 1) * 8)), (s16)(y + 120), 0x1A, UI_SPRITE_ALT_PAGE);
    }

    UI_SpriteDraw((s16)(x + 8), y, 0x32, UI_SPRITE_ALT_PAGE);
    UI_SpriteDraw((s16)(x + 128), y, 0x33, UI_SPRITE_ALT_PAGE);
}
#else
INCLUDE_ASM(Battle_DrawTitledFrame);
#endif
