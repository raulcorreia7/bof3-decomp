#include "battle_15.h"

MATCH void func_800A4C70(void) {
    u8*          flag;
    /* The state byte is accessed through a volatile view: retail orders the
     * counter load before this RMW and this store before the counter store. */
    volatile u8* state;
    u8           count;

    flag = &g_UiPanelTasks[21].active;
    if ((*flag & 0x1) == 0) {
        *flag = 0;
        UI_PanelOpenTask(0x12, 5);
        g_UiPanelTasks[18].mode                         = 2;
        g_UiPanelTasks[18].pos.vx                       = -0xA5;
        g_BattlePanelMode                               = 0;
        g_UiPanelTasks[18].pos.vy                       = 0x3F;
        g_BattleTargetCursorCol                         = 0;
        D_801485CA                                      = 0;
        g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText(0x59);
        count                                           = g_BattleUIState + 1;
        state                                           = &g_Battle.selection;
        *state |= 0x80;
        g_BattleUIState = count;
    }
}
