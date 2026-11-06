/* Draw the play time window: hours and minutes of g_SaveData.play_clock with a colon that
 * blinks on the clock's thirtieths count, and the caption row. One definition
 * shared by the start, Bate, Shisu and shop overlays; each overlay includes
 * this file where the function sits and binds g_MenuClockFormat,
 * MENU_CLOCK_COLON, MENU_CLOCK_CAPTION and the caption glyph runs in its table
 * in config/symbols.toml. Every change must verify every member.
 */
/* func_801DD974 (start), func_801D49D4 (bate), func_801D597C (shisu), func_801DA47C (shop) */
MATCH void Menu_DrawPlayTimeWindow(u16 panel_x, u16 panel_y) {
    u16 x;
    u16 y;
    s16 window_y;
    s16 text_y;
    s16 row_x;
    u8  i;

    x        = panel_x;
    y        = panel_y;
    window_y = y + 3;
    text_y   = y + 4;
    UI_DrawWindow((u16)(x + 3), (u16)window_y, 85, 16, 0, D_80144952);
    sprintf((char*)g_UiFormatBuffer, g_MenuClockFormat, g_SaveData.play_clock.hours_00);
    UI_DrawAsciiString(x + 33, text_y, 0, g_UiFormatBuffer);
    sprintf((char*)g_UiFormatBuffer, g_MenuClockFormat, g_SaveData.play_clock.minutes_01);
    UI_DrawAsciiString(x + 60, text_y, 0, g_UiFormatBuffer);
    if (g_SaveData.play_clock.thirtieths_03 < 0xF) {
        UI_DrawTextString(x + 52, window_y, 0, 0xFF, MENU_CLOCK_COLON);
        UI_DrawTextString(x + 52, y + 7, 0, 0xFF, MENU_CLOCK_COLON);
    }
    UI_DrawSpriteRun(x, y, MENU_CLOCK_CAPTION, 0);
    for (i = 0, row_x = x + 0x18; i < 6; i++) {
        UI_DrawSpriteRun(row_x + i * 8, y, MENU_CAPTION_GLYPH_1, 0);
    }
    UI_DrawSpriteRun(x - 0x10, y, MENU_CAPTION_GLYPH_2, 0);
}
