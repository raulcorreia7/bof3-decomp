#include "battle_15.h"

/* func_800B1A74 */
/* Draws the battle list box: the frame, the title text (DATA or BEST by title_index), the row and column guide
 * lines and their corner markers. The two unused parameters are the panel task's bytes 8 and 9 that the caller passes
 * through. */
#ifdef NON_MATCHING
NON_MATCHING void Battle_DrawTitledFrame(s32 x, s16 y, s32 unused_a, s32 unused_b, u8 title_index) {
    /* FAKE: preserve the retail 0x48-byte frame; pure C is 50.49%. */
    FAKE_STACK_PADS(u8, 8);
    s32 y_word;
    /* FAKE: retain the x input in retail $s3; pure C measured 50.49%. */
    FAKE_REG(s32, x16, "s3");
    /* FAKE: retain the y input in retail $s1; pure C measured 50.49%. */
    FAKE_REG(s32, y16, "s1");
    /* FAKE: retain the box's x origin in retail $s7; pure C measured 50.49%. */
    FAKE_REG(s32, origin_x, "s7");
    /* FAKE: retain the box's y origin in retail $s8; pure C measured 50.49%. */
    FAKE_REG(s16, origin_y, "fp");
    /* FAKE: keep the initial frame x coordinate in retail $s2; pure C measured 50.49%. */
    FAKE_REG(s32, box_x, "s2");
    /* FAKE: keep frame and coordinate temporaries in retail $s0; pure C measured 50.49%. */
    FAKE_REG(s32, temp, "s0");
    /* FAKE: retain the title index from the caller in retail $s5; pure C measured 50.49%. */
    FAKE_REG(u8, style, "s5");
    s32 i;
    /* FAKE: retain the fill-byte base in retail $s4; pure C measured 50.49%. */
    FAKE_REG(u8*, fill, "s4");
    s32 col_x;
    s32 col_i;
    s32 cell_i;
    u8* style_text;

    x16      = x;
    y16      = y;
    origin_x = x16;
    origin_y = y16;
    box_x    = x16 + 3;
    box_x &= HALF_MASK;
    temp = y16 + 3;
    temp &= HALF_MASK;
    style  = title_index;
    i      = 0;
    fill   = &CHARACTER_BLOCK->window_style;
    y_word = y16 << 0x10;
    UI_DrawWindow(box_x, temp, 137, 130, 0, (s32)fill[0]);
    UI_DrawWindow(box_x, temp, 137, 20, 0, (s32)fill[0]);
    UI_DrawWindow(box_x, (y16 + 122) & HALF_MASK, 137, 8, 0, (s32)fill[0]);
    style_text = s_BattleFrameTitles[style];
    y16 += 7;
    y16 <<= 0x10;
    UI_DrawText((s16)(x16 - (((Game_ReadCommand(style_text) & BYTE_MASK) * 4) - 70)), (s16)(y16 >> 16), 0, 0x10U, style_text);
    x16 <<= 0x10;
    x16  = x16 >> 0x10;
    temp = y_word >> 0x10;
    UI_DrawSpriteRun((s16)x16, (s16)temp, &D_800B6D44, 1);
    UI_DrawSpriteRun((s16)x16, (s16)temp, &D_800B6D50, 1);
    cell_i = 0 & BYTE_MASK;
    do {
        UI_DrawSprite((s16)(origin_x + ((cell_i + 5) * 8)), y_word >> 16, 1, 1);
        i += 1;
        cell_i = i & BYTE_MASK;
    } while ((u32)(i & BYTE_MASK) < 8U);
    i    = 0;
    temp = origin_x << 0x10;
    do {
        UI_DrawSprite((s16)origin_x, (s32)(s16)(origin_y + (((i & BYTE_MASK) + 3) * 8)), 4, 1);
        i += 1;
    } while ((u32)(i & BYTE_MASK) < 12U);
    temp = origin_x + 0x80;
    temp <<= 0x10;
    UI_DrawSprite((s16)(temp >> 16), (s32)(s16)(origin_y + 24), 0x16, 1);
    i     = 0;
    col_x = temp >> 0x10;
    do {
        UI_DrawSprite((s16)col_x, (s32)(s16)(origin_y + (((i & BYTE_MASK) + 5) * 8)), 0x17, 1);
        i += 1;
        col_x = temp >> 0x10;
    } while ((u32)(i & BYTE_MASK) < 9U);
    UI_DrawSprite((s16)(origin_x + 128), (s32)(s16)(origin_y + 112), 0x18, 1);
    temp = origin_y + 0x78;
    temp <<= 0x10;
    UI_DrawSprite((s16)origin_x, temp >> 16, 0x19, 1);
    i     = 0;
    col_i = 0 & BYTE_MASK;
    do {
        UI_DrawSprite((s16)(origin_x + ((col_i + 1) * 8)), temp >> 16, 0x1A, 1);
        i += 1;
        col_i = i & BYTE_MASK;
    } while ((u32)(i & BYTE_MASK) < 15U);
    temp = origin_y << 0x10;
    temp = (s32)origin_y;
    UI_DrawSprite((s16)(origin_x + 8), temp, 0x32, 1);
    UI_DrawSprite((s16)(origin_x + 128), temp, 0x33, 1);
}
#else
INCLUDE_ASM(Battle_DrawTitledFrame);
#endif
