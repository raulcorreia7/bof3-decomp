#include "start_08.h"

/* func_801DAE14 */
#ifdef NON_MATCHING
NON_MATCHING void Menu_OpenPartyChange(u16 buttons) {
    s32 count;
    u8  n;
    s32 offset;
    s32 i;
    s32 j;
    u8* total; /* D_801484EA: the reserve list length */
    u8* next;  /* the same byte, the index the scan advances */

    count  = Party_CountOrder(PARTY_ORDER_FIELD);
    n      = count;
    total  = &D_801484EA;
    *total = 0;
    next   = &D_801484EA;
    offset = 0;
    for (i = 0; i < CHAR_INDEX_COUNT; i++) {
        if (((u8*)&g_Characters[0].party_flags)[offset] & PARTY_FLAG_JOINED) {
            for (j = 0; j < n; j++) {
                if (g_Characters[i].character_id == g_PartyFieldOrder[j]) {
                    break;
                }
            }
            if (j == n) {
                D_801ED690[(*next)++] = g_Characters[i].character_id;
            }
        }
        offset += PARTY_RECORD_STRIDE;
    }

    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].active = 1;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].panel  = 6;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].mode   = 0x13;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].state  = 2;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].pos.x  = BATTLE_PARTY_STRIDE;
    g_UiPanelTasks[MENU_START_PANEL_COMMANDS].pos.y  = 0x3B;
    D_80148500                                       = D_801ED690;

    for (i = 0; i < n; i++) {
        D_801ED694[i][0] = 1;
    }
    for (; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        D_801ED694[i][0] = 0;
    }

    total = &D_801484EA;
    for (i = 0; i < *total; i++) {
        D_801ED695[i][0] = 1;
    }
    total = &D_801484EA;
    /* Retail re-tests the same count, which the loop above has already reached. */
    for (; i < *total; i++) {
        D_801ED695[i][0] = 0;
    }

    D_8014865A    = 0x7F;
    D_8014865D    = 0x7F;
    D_80148658[0] = 0;
    D_80148659    = 0;
    D_801ED69C    = 0xFF;
}
#else
INCLUDE_ASM(Menu_OpenPartyChange);
#endif
