#include "battle_15.h"

MATCH void func_800A5DE0(void) {
    u8* counter;
    u8  count;

    UI_PanelOpenTask(0x15, 5);
    D_80148628              = -190;
    D_8014862A              = 0x3F;
    g_UiPanelTasks[21].mode = 0;
    D_80148627              = 0;
    D_8014862E              = 1;
    counter                 = (u8*)&g_Battle.ui_mode;
    count                   = *counter;
    g_UiPanelTasks[19].state              = 2;
    *counter                = (count + 1);
}
