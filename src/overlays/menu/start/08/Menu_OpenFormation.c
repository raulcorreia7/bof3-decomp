#include "start_08.h"

/* func_801DAC1C */
/* Lays out the formation grid: a member cell per filled row and a card for each open formation slot. */
MATCH void Menu_OpenFormation(void) {
    u8*            table;
    MenuPanelTask* panel;
    u8             count;
    s32            has_member;
    u8             row;
    u8             col;
    u8             panel_index;
    u32            bit;
    u32            limit;
    u8             group_base;

    count = Party_CountOrder(PARTY_ORDER_FIELD);
    switch (count) {
        case 1:
            group_base = 0;
            limit      = 1;
            break;
        case 2:
            group_base = 1;
            limit      = 3;
            break;
        case 3: /* a full party takes the default layout */
        default:
            group_base = 4;
            limit      = 6;
            break;
    }
    bit         = 1;
    panel_index = 0;
    for (row = 0; row < 3; row++) {
        for (col = 0; col < 3; col++) {
            has_member = row < count;
            table      = g_FormationCells[row];
            if (col == 0 && has_member) {
                table[0] = 1;
            } else {
                table[col] = 0;
            }
            if (col != 0) {
                if ((bit & g_PartyMenuFlags) != 0 && panel_index < limit) {
                    table[col]           = 1;
                    panel                = &g_UiPanelTasks[MENU_PANEL_CARD_FIRST] + panel_index;
                    panel->panel         = 6;
                    panel->mode          = 0xB;
                    panel->state         = 2;
                    panel->pos.x         = (col - 1) * 0x4B + 0x140;
                    panel->unk_0A        = group_base + panel_index;
                    panel->active        = 1;
                    panel->pos.y         = row * 0x36 + 0x3E;
                    panel->unk_0B        = panel_index;
                    panel->unk_0C        = 0;
                    panel->u.addr.unk_10 = 0xE00;
                } else {
                    table[col] = 0;
                }
                panel_index++;
                bit *= 2;
            }
        }
    }
    g_FormationPickColumn   = 0x7F;
    g_FormationPickRow      = 0x7F;
    g_FormationCursorColumn = 0;
    g_FormationCursorRow    = 0;
    g_FormationColumn       = (g_PartyFormation & 1) + 1;
    g_FormationRow          = (u8)g_PartyFormation >> 1;
}
