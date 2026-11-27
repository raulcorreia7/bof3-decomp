#include "batl_end_00.h"

MATCH void func_801EEE4C(void) {
    UI_PanelOpenTask(1, 4);

    g_UIPanelTasks[1].mode   = 4;
    g_UIPanelTasks[1].state  = 0;
    g_UIPanelTasks[1].unk_09 = g_Battle.party_count * 16 + 4;
    if (g_Battle.outcome.reward_exp < 30) {
        D_801463B0 = 1;
    } else {
        D_801463B0 = g_Battle.outcome.reward_exp / 30;
    }
    {
        /* Base held once for the read-modify-write, as in retail. */
        u8* counter = (u8*)&g_Battle.ui_mode;

        *counter += 1;
    }
}
