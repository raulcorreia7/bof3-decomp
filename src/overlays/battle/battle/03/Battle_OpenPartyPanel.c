#include "battle_03.h"

/* func_801D9304 */
MATCH void Battle_OpenPartyPanel(u8 index) {
    u8 count;

    UI_PanelOpenTask(1, 3);
    count                    = g_Battle.party_count;
    g_UIPanelTasks[1].mode   = 0;
    g_UIPanelTasks[1].state  = index;
    g_UIPanelTasks[1].unk_0A = count;
    D_80148358               = D_801EAF27[count & BYTE_MASK];
    D_8014835A               = 0xF0;
    g_UIPanelTasks[1].unk_08 = 0;
    g_UIPanelTasks[1].unk_09 = 0;
}
