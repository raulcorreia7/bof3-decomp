/* Draws one save slot: the window, the party icons, the name, the level, the play time and the experience line; a NULL slot draws only the window. Each image defines its own g_SaveSlotLevelFormat, g_SaveSlotTimeFormat, g_SaveSlotTimeColon and g_SaveSlotFrameSprites. */
/* func_801D8208 (bate), func_801D91B0 (shisu) */
MATCH void SAVE_DrawSlotRow(u8 index, s32 left, s32 top, SaveSlotRow* slot) {
    s16 x;
    s16 y;
    s16 label_x;
    u8  i;
    u8  icon;

    x = left;
    y = top;
    UI_WindowDraw(left + 8, y, MENU_SAVE_SLOT_WINDOW_WIDTH, MENU_SAVE_SLOT_WINDOW_HEIGHT, 0, g_WindowStyle);
    if (slot != NULL) {
        GFX_AddDrawMode(getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
        Menu_DrawPanelIcon((left + 9), (top + 5), (u8)(index + 3), 0x1E, GetClut(16, STAGE_PALETTE_Y), GFX_COLOR_NEUTRAL);
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            icon = *(slot->bytes.unk_00 + i + 5);
            if (icon != GAME_NONE) {
                Menu_DrawPortrait((u16)(left + 0x56 + i * 0x29), (u16)(y + 2), icon, 0);
            }
        }
        UI_TextDraw((x + 21), (y + 3), 0, CHARACTER_NAME_LENGTH, slot->bytes.unk_00);
        TEXT_Format(g_UITextFormatBuffer, g_SaveSlotLevelFormat, slot->bytes.unk_00[8]);
        UI_TextDrawGlyphString((x + 31), (y + 24), 0, g_UITextFormatBuffer);
        TEXT_Format(g_UITextFormatBuffer, g_SaveSlotTimeFormat, slot->bytes.unk_00[0xC], slot->bytes.unk_00[0xD]);
        label_x = x + 0x27;
        UI_TextDrawGlyphString(label_x, (y + 37), 0, g_UITextFormatBuffer);
        UI_TextDrawGlyphString(label_x, (y + 36), 0, g_SaveSlotTimeColon);
        UI_TextDrawGlyphString(label_x, (y + 39), 0, g_SaveSlotTimeColon);
        Menu_DrawExperienceLine((x + 0x14), (y + 0x12), 0, slot->bytes.unk_00[8], slot->words[4]);
    }
    UI_SpriteDrawRun(x, y, g_SaveSlotFrameSprites, slot->bytes.unk_00[0x14] && slot ? UI_SPRITE_ALT_CLUT : 0);
    if (slot != NULL && slot->bytes.unk_00[0x14] != 0) {
        UI_SpriteDraw((x + 50), (y + 22), 0x3D, 0);
    }
}
