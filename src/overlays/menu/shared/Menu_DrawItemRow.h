/* Draw one party row: the stat values, the icons and the experience to the next level. */
/* func_801D37AC (bate), func_801D4754 (shisu), func_801D9254 (shop), func_801DC74C (start) */
MATCH void Menu_DrawItemRow(s32 x0, s32 y0, s32 item, s32 selection) {
    Stats* stats;
    s32    row_off;
    u8     count;
    u8     mode;
    u8     palette;
    u8     item_index;
    s16    stat_x;
    s16    stat_y;
    s32    icon_x;
    /* FAKE: use y0 directly for the final count coordinate; pure-C score 88.79%. */
    s32    count_y;

    mode       = selection & BYTE_MASK;
    palette    = (u8)((0u - (u32)(mode != 0)) & 7);
    item_index = item & BYTE_MASK;
    UI_WindowDrawOutline((s16)(x0 + 2), (s16)(y0 + 2), 0x86, 0x2A, UI_WINDOW_OUTLINE_OPEN_ALL | UI_WINDOW_OUTLINE_BLEND);
    row_off = item_index * PARTY_RECORD_STRIDE;
    stats   = (Stats*)((u8*)&g_Characters[0].stats + row_off);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->power);
    stat_x = (s16)(x0 + 0x29);
    stat_y = (s16)(y0 + 5);
    UI_TextDrawGlyphString(stat_x, stat_y, (u32)palette, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->defense);
    UI_TextDrawGlyphString(stat_x, (s16)(y0 + 18), (u32)palette, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->intelligence);
    UI_TextDrawGlyphString((s16)(x0 + 111), stat_y, (u32)palette, g_UITextFormatBuffer);
    TEXT_Format(g_UITextFormatBuffer, g_MenuStatFormat, stats->agility);
    UI_TextDrawGlyphString((s16)(x0 + 111), (s16)(y0 + 18), (u32)palette, g_UITextFormatBuffer);
    UI_TextDraw((s16)(x0 + 5), (s16)(y0 + 3), (s32)palette, 4U, &g_MenuPortraitAtlas[0x30]);
    UI_TextDraw((s16)(x0 + 5), (s16)(y0 + 16), (s32)palette, 4U, &g_MenuPortraitAtlas[0x36]);
    UI_TextDraw((s16)(x0 + 75), (s16)(y0 + 3), (s32)palette, 4U, &g_MenuPortraitAtlas[0x3C]);
    UI_TextDraw((s16)(x0 + 75), (s16)(y0 + 16), (s32)palette, 4U, &g_MenuPortraitAtlas[0x42]);
    UI_WindowDrawOutline((s16)(x0 + 0x33), (s16)(y0 + 0x2E), 0x56, 0x14, UI_WINDOW_OUTLINE_OPEN_ALL | UI_WINDOW_OUTLINE_BLEND);
    icon_x = (x0 + 0x36) & HALF_MASK;
    Menu_DrawIcon(icon_x, (y0 + 0x30) & HALF_MASK, 4U, mode);
    TEXT_Format(g_UITextFormatBuffer, g_MenuZennyFormat, (s32)g_Characters[item_index].exp);
    UI_TextDrawGlyphString((s16)(x0 + 78), (s16)(y0 + 48), (u32)palette, g_UITextFormatBuffer);
    Menu_DrawIcon(icon_x, (y0 + 0x39) & HALF_MASK, 5U, mode);
    count = g_Characters[item_index].level;
    if (count < 0x63U) {
        count_y = y0;
        TEXT_Format(g_UITextFormatBuffer, g_MenuZennyFormat, Char_GetExpForLevel(item_index, (count + 1) & BYTE_MASK));
    } else {
        count_y = y0;
        TEXT_FormatLiteral(g_UITextFormatBuffer, g_MenuNextExpBlank);
    }
    UI_TextDrawGlyphString((s16)(x0 + 78), (s16)(count_y + 57), (u32)palette, g_UITextFormatBuffer);
}
