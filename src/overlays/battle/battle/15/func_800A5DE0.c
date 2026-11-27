#include "battle_15.h"

MATCH void func_800A5DE0(void) {
    u8* counter;
    u8  count;

    UI_PanelOpenTask(0x15, 5);
    g_UIPanelTasks[21].pos.vx = -190;
    g_UIPanelTasks[21].pos.vy = 0x3F;
    g_UIPanelTasks[21].mode   = 0;
    g_UIPanelTasks[21].state  = 0;
    g_UIPanelTasks[21].unk_0A = 1;
    counter                   = (u8*)&g_Battle.ui_mode;
    count                     = *counter;
    g_UIPanelTasks[19].state  = 2;
    *counter                  = (count + 1);
}
