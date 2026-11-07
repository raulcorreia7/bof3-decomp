/* Draw the four stat labels, their values and the glyph rows. One definition
 * shared by the shop, start, Bate and Shisu overlays; each overlay includes
 * this file where the function sits and binds the icon, format and glyph-row
 * names in its table in config/symbols.toml.
 */
/* func_801D1444 (sisyou), func_801D2C2C (bate), func_801D3BD4 (shisu), func_801D86D4 (shop), func_801DBBCC (start) */
MATCH void Menu_DrawStatPanel(u16 panel_x, u16 panel_y, u8 palette_index) {
    u8* base;
    u8* entryp;
    u8* base16;
    s16 xb;
    s16 x30;
    s16 x53;
    s16 x78;
    s16 y8;
    s16 y10;
    s16 y15;
    s16 y17;
    u8  i;
    s32 index_off;

    base = &g_WindowStyle;
    y15  = panel_x + 5;
    UI_DrawWindow((s32)((u16)y15), (s32)((u16)(panel_y + 3)), MENU_STAT_WINDOW_WIDTH, MENU_STAT_WINDOW_HEIGHT, 0,
                  (s32)base[0]);
    xb        = panel_x + 0xB;
    y8        = panel_y + 8;
    /* FAKE: pointer local. The index product is materialised first and the
     * `+0x16` in its own statement, so the constant lands on the base pointer's
     * register instead of folding onto the index register; `base` is dead after
     * this point, so base16 reuses it. */
    index_off = palette_index * 0xA4;
    base16    = base + 0x16;
    entryp    = index_off + base16;
    UI_DrawText(xb, y8, 0, 0xFF, g_MenuLabelPower);
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x20)));
    x30 = panel_x + 0x30;
    y10 = panel_y + 0xA;
    UI_DrawGlyphString(x30, y10, 0, g_UiFormatBuffer);
    y15 = panel_y + 0x15;
    UI_DrawText(xb, y15, 0, 0xFF, g_MenuLabelDefense);
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x22)));
    y17 = panel_y + 0x17;
    UI_DrawGlyphString(x30, y17, 0, g_UiFormatBuffer);
    x53 = panel_x + 0x53;
    UI_DrawText(x53, y8, 0, 0xFF, g_MenuLabelIntellect);
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x26)));
    x78 = panel_x + 0x78;
    UI_DrawGlyphString(x78, y10, 0, g_UiFormatBuffer);
    UI_DrawText(x53, y15, 0, 0xFF, g_MenuLabelAgility);
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x24)));
    UI_DrawGlyphString(x78, y17, 0, g_UiFormatBuffer);
    if (entryp[0x1B] != GAME_NONE) {
        x30 = entryp[0x1B] + 0x111;
        TEXT_SetVariable(0, 8, Resource_GetText(x30));
        WinDrawCueText(xb, panel_y + 34, 0x34);
    }
    UI_DrawSpriteRun(panel_x, panel_y, MENU_STAT_GLYPH_0, 0);
    for (i = 0; i < 16; i++) {
        UI_DrawSpriteRun(panel_x + (i * 8), panel_y, MENU_STAT_GLYPH_1, 0);
    }
    UI_DrawSpriteRun(panel_x, panel_y, MENU_STAT_GLYPH_2, 0);
}
