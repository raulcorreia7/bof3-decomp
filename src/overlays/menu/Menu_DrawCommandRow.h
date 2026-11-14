/* Draw a row of up to four command buttons from g_MenuCommandRows[row]: a window, the label text and the frame sprite per button. The selected button has its own frame. A button is dimmed (color 7) when it is not the selected one while the selection is in range, when label id 0x12 is used without game-request bit 0, or when label id 8 is used without the fountain pen and without an ink.toml. */
/* func_801DDC74 (start), func_801D4CD4 (bate), func_801D5C7C (shisu), func_801DA77C (shop) */
MATCH void Menu_DrawCommandRow(s16 x, s16 y, u8 row, u8 selected, s32 unused) {
    u8  i;
    u8* label;
    u16 color;
    s32 offset;
    s32 col;
    s32 label_width;

    row &= BYTE_MASK;
    selected &= BYTE_MASK;
    i = 0;
    if (g_MenuCommandRows[row][0] == 0) {
        return;
    }
    do {
        UI_DrawWindow((s32)(u16)(x + i * 48), (s32)(u16)y, 45, 20, 0, g_WindowStyle);
        color = 0;
        if (selected < g_MenuCommandRows[row][0]) {
            color = (i != selected) ? 7 : 0;
        }
        if (g_MenuCommandRows[row][1 + i] == 0x12 && (g_GameRequestFlags & AREA_LOAD_FLAG_WORLD_MAP) == 0) {
            color = 7;
        }
        if (g_MenuCommandRows[row][1 + i] == 8 && (u8)Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN) == 0 && (Item_Count(ITEM_CAT_ITEM, ITEM_SKILL_INK, 0) & HALF_MASK) == 0) {
            color = 7;
        }
        label       = g_MenuCommandLabels[g_MenuCommandRows[row][1 + i]];
        label_width = Game_ReadCommand(label);
        col         = i * 0x30;
        offset      = (4 - (label_width & BYTE_MASK)) * 4 + 6;
        UI_DrawText((s16)(x + col + offset), (s16)(y + 3), color, 0x10, label);
        UI_DrawSpriteRun((s16)(x + col), (s16)y, (i != selected) ? g_MenuCommandFrame : g_MenuCommandFrameSelected, 0);
        i++;
    } while (i < g_MenuCommandRows[row][0]);
}
