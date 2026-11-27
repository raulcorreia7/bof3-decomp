#define MENU_STAT_PANEL_DEFINITION
#include "sisyou_00.h"

/* "%3d" format and the stat-label strings in this overlay. */

/* Stat glyph-row templates in this overlay. */

MATCH void Menu_DrawStatPanel(u16 panel_x, u16 panel_y, u8 palette_index) {
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
    UI_WindowDraw((y15), ((panel_y + 3)), MENU_STAT_WINDOW_WIDTH, MENU_STAT_WINDOW_HEIGHT, 0, base[0]);
    xb     = panel_x + 0xB;
    y8     = panel_y + 8;
    entryp = (Character*)(&g_WindowStyle + 22 + palette_index * PARTY_RECORD_STRIDE);
    UI_TextDraw(xb, y8, 0, TEXT_LENGTH_MAX, g_MenuLabelPower);
    TEXT_Format(g_UITextFormatBuffer, D_801D0C04, entryp->stats.power);
    x30 = panel_x + 0x30;
    y10 = panel_y + 0xA;
    UI_TextDrawGlyphString(x30, y10, 0, g_UITextFormatBuffer);
    y15 = panel_y + 0x15;
    UI_TextDraw(xb, y15, 0, TEXT_LENGTH_MAX, g_MenuLabelDefense);
    TEXT_Format(g_UITextFormatBuffer, D_801D0C04, entryp->stats.defense);
    y17 = panel_y + 0x17;
    UI_TextDrawGlyphString(x30, y17, 0, g_UITextFormatBuffer);
    x53 = panel_x + 0x53;
    UI_TextDraw(x53, y8, 0, TEXT_LENGTH_MAX, g_MenuLabelIntelligence);
    TEXT_Format(g_UITextFormatBuffer, D_801D0C04, entryp->stats.intelligence);
    x78 = panel_x + 0x78;
    UI_TextDrawGlyphString(x78, y10, 0, g_UITextFormatBuffer);
    UI_TextDraw(x53, y15, 0, TEXT_LENGTH_MAX, g_MenuLabelAgility);
    TEXT_Format(g_UITextFormatBuffer, D_801D0C04, entryp->stats.agility);
    UI_TextDrawGlyphString(x78, y17, 0, g_UITextFormatBuffer);
    if (entryp->master_id != GAME_NONE) {
        x30 = entryp->master_id + 0x111;
        UI_MessageSetVariable(0, 8, UI_MessageGetText(x30));
        WinDrawCueText(xb, panel_y + 34, 0x34);
    }
    UI_SpriteDrawRun(panel_x, panel_y, D_801D3FE8, 0);
    for (i = 0; i < 16; i++) {
        UI_SpriteDrawRun(panel_x + (i * 8), panel_y, D_801D4014, 0);
    }

    UI_SpriteDrawRun(panel_x, panel_y, D_801D4020, 0);
}
