/* Draws the memory card port panel: the title, the two port tabs and the cursor at the selected port. Each image defines its own g_SaveCardPortLabelFirst and g_SaveCardPortLabelSecond. */
/* func_801D8508 (bate), func_801D94B0 (shisu), func_801DDFB0 (shop) */
MATCH void SAVE_DrawPortTabs(s16 x, s16 y, u32 tab_flags, u8 port, u8 variant) {
    s16 left;
    s16 right;
    s16 text_y;
    u16 row_offset;
    u8  color;
    u32 shade;
    u8* texture;

    Menu_DrawFilledPanel(x, y, 7, 4);
    func_801644D8(20, (u16)(x + 7), (u16)(y + 5), 16, 16, 128);
    shade = 0x1C;
    if (variant == 0) {
        shade = 0x1B;
    }
    texture = Message_GetText(shade);
    left    = (x + 6);
    UI_DrawText((x + 42), (y + 7), 0, TEXT_LENGTH_MAX, texture);

    color = (tab_flags & MENU_LIST_FLAG_TAB_1) ? MENU_SHADE_NORMAL : MENU_SHADE_DIM;
    UI_DrawText(left, (y + 25), color, TEXT_LENGTH_MAX, Message_GetText(0x85));
    right  = (x + 94);
    text_y = (y + 25);
    UI_DrawAsciiString(right, text_y, color, &g_SaveCardPortLabelFirst);

    color = (tab_flags & MENU_LIST_FLAG_TAB_2) ? MENU_SHADE_NORMAL : MENU_SHADE_DIM;
    UI_DrawText(left, (y + 41), color, TEXT_LENGTH_MAX, Message_GetText(0x85));
    text_y = (y + 41);
    UI_DrawAsciiString(right, text_y, color, &g_SaveCardPortLabelSecond);

    row_offset = (port << 4);
    Menu_DrawCursorSprite((x + 8), (row_offset + y + 28), 0);
}
