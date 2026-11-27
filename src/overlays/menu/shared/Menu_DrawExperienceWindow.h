/* Draws the experience window of one character at x, y: the caption and value of the character's EXP (flag 0) or of the EXP to the next level (flag 1), under the window sprites. A statement macro: the two captions and the sprite run differ per image. Every change must verify every member. */
/* func_801D31B0 (bate), func_801D8C58 (shop), func_801DC150 (start) */
#define MENU_DRAW_EXPERIENCE_WINDOW(exp_caption, next_caption, sprites)                                                                                                        \
    {                                                                                                                                                                          \
        Character* character;                                                                                                                                                  \
        u8*        base;                                                                                                                                                       \
        u8*        base16;                                                                                                                                                     \
        u8*        entryp;                                                                                                                                                     \
        s16        tx;                                                                                                                                                         \
        s32        pos_x;                                                                                                                                                      \
        s32        value;                                                                                                                                                      \
        s32        index_off;                                                                                                                                                  \
        /* FAKE: retail reserves 24 unused frame bytes. */                                                                                                                     \
        FAKE_STACK_PADS(u8, 24);                                                                                                                                               \
                                                                                                                                                                               \
        base = &g_WindowStyle;                                                                                                                                                 \
        UI_WindowDraw((u16)(x + 3), (u16)(y + 3), MENU_EXPERIENCE_WINDOW_WIDTH, MENU_EXPERIENCE_WINDOW_HEIGHT, 0, base[0]);                                                    \
        index_off = index * PARTY_RECORD_STRIDE;                                                                                                                               \
        base16    = base + CHARACTER_BLOCK_RECORDS;                                                                                                                            \
        entryp    = base16 + index_off;                                                                                                                                        \
        character = (Character*)entryp;                                                                                                                                        \
        pos_x     = x;                                                                                                                                                         \
        tx        = pos_x + MENU_EXPERIENCE_NEXT_X;                                                                                                                            \
        UI_TextDraw((flag == 0) ? pos_x + MENU_EXPERIENCE_EXP_X : tx, (s16)(y + MENU_EXPERIENCE_CAPTION_Y), 0, TEXT_LENGTH_MAX, (flag == 0) ? (exp_caption) : (next_caption)); \
        if (flag == 0) {                                                                                                                                                       \
            value = character->exp;                                                                                                                                            \
        } else {                                                                                                                                                               \
            value = Char_GetExpForLevel(index, (character->level + 1) & BYTE_MASK);                                                                                            \
        }                                                                                                                                                                      \
        if (value != -1) {                                                                                                                                                     \
            TEXT_Format(g_UITextFormatBuffer, g_MenuExperienceFormat, value);                                                                                                  \
        } else {                                                                                                                                                               \
            TEXT_FormatLiteral(g_UITextFormatBuffer, g_MenuExperienceBlank);                                                                                                   \
        }                                                                                                                                                                      \
        UI_TextDrawAscii((s16)(x + MENU_EXPERIENCE_VALUE_X), (s16)(y + MENU_EXPERIENCE_VALUE_Y), 0, g_UITextFormatBuffer);                                                     \
        UI_SpriteDrawRun(x, y, (sprites), UI_SPRITE_ALT_PAGE);                                                                                                                 \
    }
