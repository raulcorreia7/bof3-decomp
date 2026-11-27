#include "battle_15.h"

MATCH void func_800A50B8(void) {
    u8* counter;
    u8  count;

    UI_PanelOpenTask(0x15, 5);
    D_80148628              = 0x142;
    g_UIPanelTasks[21].mode = 0;
    D_80148627              = 0;
    D_8014862A              = 0x3F;
    counter                 = (u8*)&g_Battle.ui_mode;
    count                   = *counter;
    g_BattlePanelMode       = 2;
    *counter                = (count + 1);
}
