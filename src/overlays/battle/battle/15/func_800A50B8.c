#include "battle_15.h"

MATCH void func_800A50B8(void) {
    u8* counter;
    u8  count;

    UI_PanelOpenTask(0x15, 5);
    g_UiPanelTasks[21].pos.vx = 0x142;
    g_UiPanelTasks[21].mode   = 0;
    g_UiPanelTasks[21].state  = 0;
    g_UiPanelTasks[21].pos.vy = 0x3F;
    counter                   = (u8*)&g_Battle.ui_mode;
    count                     = *counter;
    g_BattlePanelMode         = 2;
    *counter                  = (count + 1);
}
