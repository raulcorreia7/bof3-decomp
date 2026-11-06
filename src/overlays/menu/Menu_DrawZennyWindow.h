/* Draw the caption string, its icon and the glyph rows. One definition shared
 * by the shop, start, Bate and Shisu overlays; each overlay includes this file
 * where the function sits and binds g_MenuZennyFormat, MENU_CAPTION_ICON and
 * the three glyph runs in its table in config/symbols.toml.
 */
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
    UI_DrawWindow(panel_x + 3, y + 3, 101, 16, 0, g_SaveData.window_style);
    sprintf((char*)g_UiFormatBuffer, g_MenuZennyFormat, caption_value);
    y += 4;
    UI_DrawAsciiString((s16)(panel_x + 20), y, 0, g_UiFormatBuffer);
    UI_DrawText(panel_x + 76, y, 0, 0xFF, MENU_CAPTION_ICON);
    UI_DrawSpriteRun((s16)panel_x, (s16)(scaled_y >> 16), MENU_CAPTION_GLYPH_0, 0);
    for (i = 0; i < 11; i++) {
        UI_DrawSpriteRun((s16)(base_x + (i * 8)), (s16)(scaled_y >> 16), MENU_CAPTION_GLYPH_1, 0);
    }
    UI_DrawSpriteRun(base_x, base_y, MENU_CAPTION_GLYPH_2, 0);
}
