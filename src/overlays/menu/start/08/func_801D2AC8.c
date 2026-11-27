#include "start_08.h"

extern s8 D_80148656; /* local: s8 read; a sibling copy is u8 */

MATCH void func_801D2AC8(void) {
    u8  i;
    s8* panel;

    for (i = 0; i < (Party_CountOrder(PARTY_ORDER_FIELD)); i++) {
        if (i == D_80148656) {
            g_UIPanelTasks[i + 4].state                     = 5;
            g_UIPanelTasks[i + MENU_PANEL_CARD_FIRST].state = 3;
        } else {
            g_UIPanelTasks[i + 4].state                     = 7;
            g_UIPanelTasks[i + MENU_PANEL_CARD_FIRST].state = 5;
        }
    }
    panel                    = &D_8014854C;
    g_UIPanelTasks[15].panel = 6;
    g_UIPanelTasks[15].mode  = MENU_START_MODE_EQUIPMENT;
    g_UIPanelTasks[15].state = 2;
    *panel                   = 1;
    panel += 0x24;
    g_UIPanelTasks[15].pos.vx = BATTLE_PARTY_STRIDE;
    g_UIPanelTasks[15].pos.vy = 116;
    g_UIPanelTasks[16].mode   = 7;
    g_UIPanelTasks[16].panel  = 6;
    g_BattleChoicePhase       = 2;
    g_UIPanelTasks[15].unk_0A = D_80148656;
    *panel                    = 1;
    /* D_80148574 stays an address symbol: a g_UIPanelTasks[16] view changes the code. */
    D_80148574                = -100;
    g_UIPanelTasks[16].pos.vy = 120;
    g_UIPanelTasks[17].mode   = 8;
    g_UIPanelTasks[16].unk_0A = D_80148656;
    g_UIPanelTasks[17].panel  = 6;
    D_80148597                = 2;
    panel += 0x24;
    *panel                    = 1;
    D_80148598                = -100;
    g_UIPanelTasks[17].pos.vy = 168;
    g_UIPanelTasks[17].unk_0A = D_80148656;
}
