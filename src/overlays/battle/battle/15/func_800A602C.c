#include "battle_15.h"

MATCH void func_800A602C(void) {
    u8* counter;
    u8  count;

    g_BattlePanelMode = 3;
    UI_PanelOpenTask(0x13, 5);
    g_UIPanelTasks[19].mode              = 4;
    g_UIPanelTasks[19].state             = 0;
    g_UIPanelTasks[19].pos.vx            = 0x15B;
    counter                              = (u8*)&g_Battle.ui_mode;
    count                                = *counter;
    g_UIPanelTasks[19].pos.vy            = 0x3F;
    g_UIPanelTasks[19].u.battle.cursor   = 0;
    g_UIPanelTasks[19].u.battle.row_base = 0;
    *counter                             = (count + 1);
}
