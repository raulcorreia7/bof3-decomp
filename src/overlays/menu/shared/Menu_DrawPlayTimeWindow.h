/* Draw the play time window: hours and minutes of g_PlayClock with a colon that blinks on the clock's thirtieths count, and the caption row. */
/* func_801DD974 (start), func_801D49D4 (bate), func_801D597C (shisu), func_801DA47C (shop) */
MATCH void Menu_DrawPlayTimeWindow(u16 panel_x, u16 panel_y) {
    u16 x;
    u16 y;
    s16 window_y;
    s16 text_y;
    s16 caption_x;
    u8  i;

    x        = panel_x;
    y        = panel_y;
    window_y = y + 3;
    text_y   = y + 4;
    UI_WindowDraw((u16)(x + 3), (u16)window_y, MENU_PLAY_TIME_WINDOW_WIDTH, MENU_PLAY_TIME_WINDOW_HEIGHT, 0, g_WindowStyle);
    TEXT_Format(g_UITextFormatBuffer, g_MenuClockFormat, g_PlayClock.hours);
    UI_TextDrawAscii(x + 33, text_y, 0, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuClockFormat, g_PlayClock.minutes);
    UI_TextDrawAscii(x + 60, text_y, 0, g_UITextFormatBuffer);
    if (g_PlayClock.thirtieths < 0xF) {
        UI_TextDrawString(x + 52, window_y, 0, TEXT_LENGTH_MAX, g_MenuClockColon);
        UI_TextDrawString(x + 52, y + 7, 0, TEXT_LENGTH_MAX, g_MenuClockColon);
    }
    UI_SpriteDrawRun(x, y, g_MenuClockCaption, 0);
    for (i = 0, caption_x = x + 24; i < 6; i++) {
        UI_SpriteDrawRun(caption_x + i * 8, y, g_MenuCaptionMiddle, 0);
    }
    UI_SpriteDrawRun(x - 0x10, y, g_MenuCaptionRight, 0);
}
