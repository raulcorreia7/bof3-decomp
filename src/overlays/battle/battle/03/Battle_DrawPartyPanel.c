#include "battle_03.h"

#ifdef NON_MATCHING
/* Draws one battle panel per party member: the frame, the member's name and
 * status glyph, the HP and AP values and the rails around the row. */
NON_MATCHING void Battle_DrawPartyPanel(s32 x, s32 y) {
    MenuPanelTask* task;
    s32            column_x;
    s32            clut;
    s16            panel_x;
    u16            color;
    u8             i;
    u8             r;
    u8             g;
    u8             b;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    Battle_DrawPanelShape((s16)x, (s16)y, ((g_Battle.party_count * 2) + 0xA) & 0xFE, 1);
    Battle_DrawPanelShape((s16)x, (s16)(y + 0x18), ((g_Battle.party_count * 2) + 0xB) & BYTE_MASK, 1);
    Battle_DrawWindowTile((s16)x, (s16)(y + 2), (g_Battle.party_count + 0xD) & BYTE_MASK, 1);
    /* Retail reads the style byte signed. */
    color = *(u16*)((u8*)D_80033A08 + (((*(s8*)&g_WindowStyle) << 6) | 0x20));
    r     = PSX_COLOR_R(color) << 3;
    g     = PSX_COLOR_G(color) << 3;
    b     = PSX_COLOR_B(color) << 3;

    column_x = x;
    for (i = 0; i < g_Battle.party_count; i++) {
        task    = &g_UiPanelTasks[i + MENU_PANEL_BATTLER_FIRST];
        panel_x = (s16)(column_x + 0x14);
        func_801D9DBC(panel_x, (s16)(y + 0xE), 9, 0, 0);
        func_801D9E9C(panel_x, (s16)(y + 0xE), task->unk_0B, task->flags, 0);
        if (g_Game.members[i].chr.stats.max_ap != 0) {
            Battle_DrawPanelLine(panel_x, (s16)(y + 0xE), (s16)(column_x + task->unk_0C + 0x14), (s16)(y + 0xE), 100, 0, 200);
            if (task->unk_0E != 0) {
                Battle_DrawPanelLine((s16)(column_x + task->unk_0C + 0x14), (s16)(y + 0xE), (s16)(column_x + task->unk_0C + task->unk_0E + 0x14), (s16)(y + 0xE), 200, 0, 0);
            }
        }
        if (g_Game.members[i].chr.status & 0x4000) {
            clut = 2;
        } else {
            clut = (g_Game.members[i].chr.status & 0xBFC) != 0;
        }
        UI_TextDrawString((s16)(column_x + 6), (s16)(y + 5), clut, CHARACTER_NAME_LENGTH, g_Game.members[i].chr.name);
        func_801DA078((u16)(column_x + 0x3A), (u16)(y + 6), 1);
        func_801DA078((u16)(column_x + 4), (u16)(y + 0xE), 0);
        if (g_Game.members[i].chr.status & 0x4000) {
            clut = 2;
        } else {
            clut = (g_Game.members[i].chr.status >> 0xB) & 4;
        }
        func_801D94D4((s16)(column_x + 0x48), (s16)(y + 0xF), clut, g_Game.members[i].chr.hp);
        clut = 2;
        if (g_Game.members[i].chr.ap != 0 && !(g_Game.members[i].chr.status & 0x4000)) {
            clut = (g_Game.members[i].chr.ap < (g_Game.members[i].chr.stats.max_ap >> 2)) << 2;
        }
        func_801D94D4((s16)(column_x + 0x48), (s16)(y + 8), clut, g_Game.members[i].chr.ap);
        Battle_DrawPanelLine((s16)(column_x + 2), (s16)(y + 2), (s16)(column_x + 0x5D), (s16)(y + 2), r, g, b);
        Battle_DrawPanelLine((s16)(column_x + 2), (s16)(y + 3), (s16)(column_x + 2), (s16)(y + 0x17), r, g, b);
        func_801DA4B4((s16)(column_x + 0x5D), (s16)(y + 2), (s16)(column_x + 0x5D), (s16)(y + 0x17), r, g, b);
        func_801DA4B4((s16)(column_x + 2), (s16)(y + 0x17), (s16)(column_x + 0x5D), (s16)(y + 0x17), r, g, b);
        column_x += 0x5E;
    }
}
#else
INCLUDE_ASM(Battle_DrawPartyPanel);
#endif
