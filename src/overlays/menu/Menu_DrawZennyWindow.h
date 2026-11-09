/* Draw the caption string, its icon and the glyph rows. each overlay includes this file where the function sits and binds g_MenuZennyFormat, g_MenuCaptionIcon and the three glyph runs in its table in config/symbols.toml. */
/* func_801D484C (bate), func_801D57F4 (shisu), func_801DA2F4 (shop), func_801DD7EC (start) */
MATCH void Menu_DrawZennyWindow(s32 panel_x, s32 panel_y, s32 panel_kind, s32 caption_value) {
    s16 y;
    s16 base_x;
    s16 base_y;
    s32 scaled_y;
    u8  i;

    y        = panel_y;
    base_x   = panel_x;
    base_y   = y;
    scaled_y = y << 16;
    UI_DrawWindow(panel_x + 3, y + 3, MENU_ZENNY_WINDOW_WIDTH, MENU_ZENNY_WINDOW_HEIGHT, 0, g_WindowStyle);
    TEXT_Format(g_UiFormatBuffer, g_MenuZennyFormat, caption_value);
    y += 4;
    UI_DrawAsciiString((s16)(panel_x + 20), y, 0, g_UiFormatBuffer);
    UI_DrawText(panel_x + 76, y, 0, TEXT_LENGTH_MAX, g_MenuCaptionIcon);
    UI_DrawSpriteRun((s16)panel_x, (s16)(scaled_y >> 16), g_MenuCaptionLeft, 0);
    for (i = 0; i < 11; i++) {
        UI_DrawSpriteRun((s16)(base_x + (i * 8)), (s16)(scaled_y >> 16), g_MenuCaptionMiddle, 0);
    }
    UI_DrawSpriteRun(base_x, base_y, g_MenuCaptionRight, 0);
}
