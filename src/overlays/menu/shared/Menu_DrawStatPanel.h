/* Draw the four stat labels, their values and the glyph rows.toml. */
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
    UI_WindowDraw((s32)((u16)y15), (s32)((u16)(panel_y + 3)), MENU_STAT_WINDOW_WIDTH, MENU_STAT_WINDOW_HEIGHT, 0, (s32)base[0]);
    xb        = panel_x + 0xB;
    y8        = panel_y + 8;
    /* FAKE: pointer local. The index product is materialised first and the
     * `+0x16` in its own statement, so the constant lands on the base pointer's
     * register instead of folding onto the index register; `base` is dead after
     * this point, so base16 reuses it. */
    index_off = palette_index * PARTY_RECORD_STRIDE;
    base16    = base + 0x16;
    entryp    = index_off + base16;
    UI_TextDraw(xb, y8, 0, TEXT_LENGTH_MAX, g_MenuLabelPower);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x20)));
    x30 = panel_x + 0x30;
    y10 = panel_y + 0xA;
    UI_TextDrawGlyphString(x30, y10, 0, g_UITextFormatBuffer);
    y15 = panel_y + 0x15;
    UI_TextDraw(xb, y15, 0, TEXT_LENGTH_MAX, g_MenuLabelDefense);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x22)));
    y17 = panel_y + 0x17;
    UI_TextDrawGlyphString(x30, y17, 0, g_UITextFormatBuffer);
    x53 = panel_x + 0x53;
    UI_TextDraw(x53, y8, 0, TEXT_LENGTH_MAX, g_MenuLabelIntelligence);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x26)));
    x78 = panel_x + 0x78;
    UI_TextDrawGlyphString(x78, y10, 0, g_UITextFormatBuffer);
    UI_TextDraw(x53, y15, 0, TEXT_LENGTH_MAX, g_MenuLabelAgility);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, *((u16*)(entryp + 0x24)));
    UI_TextDrawGlyphString(x78, y17, 0, g_UITextFormatBuffer);
    if (entryp[0x1B] != GAME_NONE) {
        x30 = entryp[0x1B] + 0x111;
        UI_MessageSetVariable(0, 8, UI_MessageGetText(x30));
        WinDrawCueText(xb, panel_y + 34, 0x34);
    }
    UI_SpriteDrawRun(panel_x, panel_y, g_MenuStatFrameLeft, 0);
    for (i = 0; i < 16; i++) {
        UI_SpriteDrawRun(panel_x + (i * 8), panel_y, g_MenuStatFrameMiddle, 0);
    }
    UI_SpriteDrawRun(panel_x, panel_y, g_MenuStatFrameRight, 0);
}
