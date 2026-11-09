/* Draws one save slot row: the window, the party icons, the name, the level, the play time and the experience line. */
/* func_801D8208 (bate), func_801D91B0 (shisu) */
MATCH void SAVE_DrawSlotRow(u8 index, s32 left, s32 top, MenuListRow* row) {
    s16 x;
    s16 y;
    s16 label_x;
    u8  i;
    u8  icon;

    x = left;
    y = top;
    UI_DrawWindow(left + 8, y, MENU_SAVE_SLOT_WINDOW_WIDTH, MENU_SAVE_SLOT_WINDOW_HEIGHT, 0, g_WindowStyle);
    if (row != NULL) {
        GFX_AddDrawMode(getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y));
        Menu_DrawPanelIcon((left + 9), (top + 5), (u8)(index + 3), 0x1E, GetClut(16, STAGE_PALETTE_Y), 128);
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            icon = *(row->unk_00 + i + 5);
            if (icon != GAME_NONE) {
                Menu_DrawPortrait((u16)(left + 0x56 + i * 0x29), (u16)(y + 2), icon, 0);
            }
        }
        UI_DrawText((x + 21), (y + 3), 0, 5, row->unk_00);
        TEXT_Format(g_UiFormatBuffer, g_SaveSlotLevelFormat, row->unk_00[8]);
        UI_DrawGlyphString((x + 31), (y + 24), 0, g_UiFormatBuffer);
        TEXT_Format(g_UiFormatBuffer, g_SaveSlotTimeFormat, row->unk_00[0xC], row->unk_00[0xD]);
        label_x = x + 0x27;
        UI_DrawGlyphString(label_x, (y + 37), 0, g_UiFormatBuffer);
        UI_DrawGlyphString(label_x, (y + 36), 0, g_SaveSlotTimeColon);
        UI_DrawGlyphString(label_x, (y + 39), 0, g_SaveSlotTimeColon);
        Menu_DrawExperienceLine((x + 0x14), (y + 0x12), 0, row->unk_00[8], ((MenuListRowWords*)row)->unk_10);
    }
    UI_DrawSpriteRun(x, y, g_SaveSlotFrameSprites, row->unk_00[0x14] && row ? 2 : 0);
    if (row != NULL && row->unk_00[0x14] != 0) {
        UI_DrawSprite((x + 50), (y + 22), 0x3D, 0);
    }
}
