#include "battle_15.h"

MATCH void func_800A5A18(void) {
    u8*          flag;
    /* The state byte is accessed through a volatile view: retail orders the
     * counter load before this RMW and this store before the counter store. */
    volatile u8* state;
    u8           count;

    flag = &g_UIPanelTasks[21].active;
    if ((*flag & 0x1) == 0) {
        *flag = 0;
        UI_PanelOpenTask(0x13, 5);
        D_801485DE = 3;
        D_801485E0 = 0x15B;
        D_801485DF = 0;
        D_801485E2 = 0x3F;
        /* FAKE: statement boundary keeps the retail register order and schedule. */
        do {
            D_801485EC = 0;
        } while (0);
        D_801485EE                                      = 0;
        g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText(0x63);
        count                                           = g_BattleUIState + 1;
        state                                           = &g_Battle.selection;
        *state |= 0x80;
        g_BattleUIState = count;
    }
}
