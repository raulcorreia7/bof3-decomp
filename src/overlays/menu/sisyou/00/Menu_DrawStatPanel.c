#include "sisyou_00.h"

/* "%3d" format and the stat-label strings in this overlay. */

/* Stat glyph-row templates in this overlay. */

MATCH void Menu_DrawStatPanel(s16 panel_x, s16 panel_y, u8 palette_index) {
    u8*        base;
    Character* entryp;
    s16        xb;
    s16        x30;
    s16        x53;
    s16        x78;
    s16        y8;
    s16        y10;
    s16        y15;
    s16        y17;
    u8         i;
    base = &g_WindowStyle;
    y15  = panel_x + 5;
    UI_DrawWindow((y15), ((panel_y + 3)), MENU_STAT_WINDOW_WIDTH, MENU_STAT_WINDOW_HEIGHT, 0, base[0]);
    xb     = panel_x + 0xB;
    y8     = panel_y + 8;
    entryp = (Character*)(&g_WindowStyle + 22 + palette_index * 0xA4);
    UI_DrawText(xb, y8, 0, TEXT_LENGTH_MAX, g_MenuLabelPower);
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, entryp->stats.power);
    x30 = panel_x + 0x30;
    y10 = panel_y + 0xA;
    UI_DrawGlyphString(x30, y10, 0, g_UiFormatBuffer);
    y15 = panel_y + 0x15;
    UI_DrawText(xb, y15, 0, TEXT_LENGTH_MAX, g_MenuLabelDefense);
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, entryp->stats.defense);
    y17 = panel_y + 0x17;
    UI_DrawGlyphString(x30, y17, 0, g_UiFormatBuffer);
    x53 = panel_x + 0x53;
    UI_DrawText(x53, y8, 0, TEXT_LENGTH_MAX, g_MenuLabelIntellect);
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, entryp->stats.intellect);
    x78 = panel_x + 0x78;
    UI_DrawGlyphString(x78, y10, 0, g_UiFormatBuffer);
    UI_DrawText(x53, y15, 0, TEXT_LENGTH_MAX, g_MenuLabelAgility);
    TEXT_Format(g_UiFormatBuffer, D_801D0C04, entryp->stats.agility);
    UI_DrawGlyphString(x78, y17, 0, g_UiFormatBuffer);
    if (entryp->master_id != GAME_NONE) {
        x30 = entryp->master_id + 0x111;
        Message_SetVariable(0, 8, Message_GetText(x30));
        WinDrawCueText(xb, panel_y + 34, 0x34);
    }
    UI_DrawSpriteRun(panel_x, panel_y, D_801D3FE8, 0);
    for (i = 0; i < 16; i++) {
        UI_DrawSpriteRun(panel_x + (i * 8), panel_y, D_801D4014, 0);
    }

    UI_DrawSpriteRun(panel_x, panel_y, D_801D4020, 0);
}
