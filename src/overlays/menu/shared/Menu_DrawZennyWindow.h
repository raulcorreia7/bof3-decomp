/* Draw the caption string, its icon and the glyph rows.toml. */
/* func_801D484C (bate), func_801D57F4 (shisu), func_801DA2F4 (shop), func_801DD7EC (start) */
MATCH void Menu_DrawZennyWindow(s32 panel_x, s32 panel_y, s32 panel_type, s32 caption_value) {
    s16 y;
    s16 base_x;
    s16 base_y;
    s32 scaled_y;
    u8  i;

    y        = panel_y;
    base_x   = panel_x;
    base_y   = y;
    scaled_y = y << 16;
    UI_WindowDraw(panel_x + 3, y + 3, MENU_ZENNY_WINDOW_WIDTH, MENU_ZENNY_WINDOW_HEIGHT, 0, g_WindowStyle);
    TEXT_Format(g_UITextFormatBuffer, g_MenuZennyFormat, caption_value);
    y += 4;
    UI_TextDrawAscii((s16)(panel_x + 20), y, 0, g_UITextFormatBuffer);
    UI_TextDraw(panel_x + 76, y, 0, TEXT_LENGTH_MAX, g_MenuCaptionIcon);
    UI_SpriteDrawRun((s16)panel_x, (s16)(scaled_y >> 16), g_MenuCaptionLeft, 0);
    for (i = 0; i < 11; i++) {
        UI_SpriteDrawRun((s16)(base_x + (i * 8)), (s16)(scaled_y >> 16), g_MenuCaptionMiddle, 0);
    }
    UI_SpriteDrawRun(base_x, base_y, g_MenuCaptionRight, 0);
}
