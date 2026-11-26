#include "battle_03.h"

/* Draws one battle panel per party member: the frame, the member's name and
 * status glyph, the HP and AP values and the rails around the row. */
MATCH void Battle_DrawPartyPanel(s16 x, s16 y) {
    s16 column_x;
    s8  clut;
    u16 color;
    u8  i;
    u8  r;
    u8  g;
    u8  b;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    Battle_DrawPanelShape(x, y, ((g_Battle.party_count * 2) + 0xA) & 0xFE, 1);
    Battle_DrawPanelShape(x, (s16)(y + 0x18), ((g_Battle.party_count * 2) + 0xB) & BYTE_MASK, 1);
    Battle_DrawWindowTile(x, (s16)(y + 2), (g_Battle.party_count + 0xD) & BYTE_MASK, 1);
    color = *(u16*)(BATTLE_GLOBAL_BYTES_3A08 + (((*(s8*)&g_WindowStyle) << 6) | 0x20));
    r     = PSX_COLOR_R(color) << 3;
    g     = PSX_COLOR_G(color) << 3;
    b     = PSX_COLOR_B(color) << 3;
    for (i = 0; i < g_Battle.party_count; i++) {
        column_x = x + 0x14;
        func_801D9DBC(column_x, (s16)(y + 0xE), 9, 0, 0);
        func_801D9E9C(column_x, (s16)(y + 0xE), g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST].unk_0B, g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST].flags, 0);
        if (g_Game.members[i].chr.stats.max_ap != 0) {
            Battle_DrawPanelLine(column_x, (s16)(y + 0xE), (s16)(x + (g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST].unk_0C + 0x14)), (s16)(y + 0xE), 100, 0, 200);
            if (g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST].unk_0E != 0) {
                Battle_DrawPanelLine((s16)(x + (g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST].unk_0C + 0x14)), (s16)(y + 0xE),
                                     (s16)(g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST].unk_0E + (g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST].unk_0C + column_x)), (s16)(y + 0xE), 200, 0, 0);
            }
        }
        if (g_Game.members[i].chr.status & 0x4000) {
            clut = 2;
        } else {
            clut = (g_Game.members[i].chr.status & 0xBFC) != 0;
        }
        UI_TextDrawString((s16)(x + 6), (s16)(y + 5), clut, CHARACTER_NAME_LENGTH, g_Game.members[i].chr.name);
        func_801DA078((u16)(x + 0x3A), (u16)(y + 6), 1);
        func_801DA078((u16)(x + 4), (u16)(y + 0xE), 0);
        if (g_Game.members[i].chr.status & 0x4000) {
            clut = 2;
        } else {
            clut = (g_Game.members[i].chr.status >> 0xB) & 4;
        }
        func_801D94D4((s16)(x + 0x48), (s16)(y + 0xF), clut, g_Game.members[i].chr.hp);
        if (g_Game.members[i].chr.ap == 0 || (g_Game.members[i].chr.status & 0x4000)) {
            clut = 2;
        } else {
            clut = (g_Game.members[i].chr.ap < (g_Game.members[i].chr.stats.max_ap >> 2)) << 2;
        }
        func_801D94D4((s16)(x + 0x48), (s16)(y + 8), clut, g_Game.members[i].chr.ap);
        Battle_DrawPanelLine((s16)(x + 2), (s16)(y + 2), (s16)(x + 0x5D), (s16)(y + 2), r, g, b);
        Battle_DrawPanelLine((s16)(x + 2), (s16)(y + 3), (s16)(x + 2), (s16)(y + 0x17), r, g, b);
        func_801DA4B4((s16)(x + 0x5D), (s16)(y + 2), (s16)(x + 0x5D), (s16)(y + 0x17), r, g, b);
        func_801DA4B4((s16)(x + 2), (s16)(y + 0x17), (s16)(x + 0x5D), (s16)(y + 0x17), r, g, b);
        x += 0x5E;
    }
}
