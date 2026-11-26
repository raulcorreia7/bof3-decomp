#include "start_08.h"

/* func_801DAE14: lists the joined characters outside the field party and opens the party change panel */
MATCH void Menu_OpenPartyChange(u16 buttons) {
    s32 count;
    u8  n;
    s32 i;
    s32 j;

    count                                            = Party_CountOrder(PARTY_ORDER_FIELD);
    n                                                = count;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A = 0;
    for (i = 0; i < CHAR_INDEX_COUNT; i++) {
        if (g_Characters[i].party_flags & PARTY_FLAG_JOINED) {
            for (j = 0; j < n; j++) {
                if (g_Characters[i].character_id == g_PartyFieldOrder[j]) {
                    break;
                }
            }
            if (j == n) {
                D_801ED690[g_UiPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A++] = g_Characters[i].character_id;
            }
        }
    }

    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].active = 1;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].panel  = 6;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].mode   = 0x13;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].state  = 2;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].pos.vx = SCREEN_WIDTH;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].pos.vy = 0x3B;
    D_80148500                                       = D_801ED690;

    for (i = 0; i < n; i++) {
        D_801ED694[i][0] = 1;
    }
    for (; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        D_801ED694[i][0] = 0;
    }

    for (i = 0; i < g_UiPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A; i++) {
        D_801ED695[i][0] = 1;
    }
    /* Retail tests the same count again, which the loop above has already reached. */
    for (; i < g_UiPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A; i++) {
        D_801ED695[i][0] = 0;
    }

    D_8014865A    = 0x7F;
    D_8014865D    = 0x7F;
    D_80148658[0] = 0;
    D_80148659    = 0;
    D_801ED69C    = 0xFF;
}
