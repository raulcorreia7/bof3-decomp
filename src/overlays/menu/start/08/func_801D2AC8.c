#include "start_08.h"

extern s8 D_80148656; /* local: s8 read; a sibling copy is u8 */

MATCH void func_801D2AC8(void) {
    u8  i;
    s8* panel;

    for (i = 0; i < (Party_CountOrder(PARTY_ORDER_FIELD)); i++) {
        if (i == D_80148656) {
            g_MenuPanelTasks[i + 4].state   = 5;
            g_MenuPanelTasks[i + 0xC].state = 3;
        } else {
            g_MenuPanelTasks[i + 4].state   = 7;
            g_MenuPanelTasks[i + 0xC].state = 5;
        }
    }
    panel                        = &D_8014854C;
    g_MenuPanelTasks[15].handler = 6;
    g_MenuPanelTasks[15].mode    = MENU_START_MODE_EQUIPMENT;
    g_MenuPanelTasks[15].state   = 2;
    *panel                       = 1;
    panel += 0x24;
    g_MenuPanelTasks[15].pos.x   = BATTLE_PARTY_STRIDE;
    g_MenuPanelTasks[15].pos.y   = 116;
    g_MenuPanelTasks[16].mode    = 7;
    g_MenuPanelTasks[16].handler = 6;
    g_BattleChoicePhase          = 2;
    g_MenuPanelTasks[15].unk_0A  = D_80148656;
    *panel                       = 1;
    /* D_80148574 stays an address symbol: a g_MenuPanelTasks[16] view changes the code. */
    D_80148574                   = -100;
    g_MenuPanelTasks[16].pos.y   = 120;
    g_MenuPanelTasks[17].mode    = 8;
    g_MenuPanelTasks[16].unk_0A  = D_80148656;
    g_MenuPanelTasks[17].handler = 6;
    D_80148597                   = 2;
    panel += 0x24;
    *panel                      = 1;
    D_80148598                  = -100;
    g_MenuPanelTasks[17].pos.y  = 168;
    g_MenuPanelTasks[17].unk_0A = D_80148656;
}
