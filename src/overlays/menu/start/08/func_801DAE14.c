/* best score 90.14 */
#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DAE14(u16 buttons) {
    s32 count;
    /* FAKE: pin keeps the row offset in the retail a3 home. */
    FAKE_REG(s32, offset, "a3");
    s32          i;
    s32          index;
    s32          j;
    volatile u8* flags;
    volatile u8* total;

    count  = Party_CountOrder(PARTY_ORDER_FIELD);
    flags  = &D_801484EA;
    *flags = 0;
    offset = 0;
    for (i = 0; i < CHARACTER_COUNT; i++) {
        if (((u8*)&g_Characters[0].unk_07)[offset] & 1) {
            for (index = 0; index < (count & BYTE_MASK); index++) {
                if (g_Characters[i].character_id == g_PartyFieldOrder[index]) {
                    break;
                }
            }
            if (index == (count & BYTE_MASK)) {
                D_801ED690[(*flags)++] = g_Characters[i].character_id;
            }
        }
        offset += 0xA4;
    }

    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].active  = 1;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].handler = 6;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].mode    = 0x13;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].state   = 2;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].pos.x   = BATTLE_PARTY_STRIDE;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].pos.y   = 0x3B;
    D_80148500                                          = D_801ED690;

    for (i = 0; i < (count & BYTE_MASK); i++) {
        D_801ED694[i][0] = 1;
    }
    for (; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        D_801ED694[i][0] = 0;
    }

    total = &D_801484EA;
    for (i = 0; i < *total; i++) {
        D_801ED695[i][0] = 1;
    }
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
INCLUDE_ASM(func_801DAE14);
#endif
