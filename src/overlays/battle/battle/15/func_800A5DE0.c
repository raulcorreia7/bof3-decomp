#include "battle_15.h"

MATCH void func_800A5DE0(void) {
    u8* counter;
    u8  count;

    UI_PanelOpenTask(0x15, 5);
<<<<<<< HEAD
    D_80148628              = -190;
    D_8014862A              = 0x3F;
    g_UIPanelTasks[21].mode = 0;
    D_80148627              = 0;
    D_8014862E              = 1;
    counter                 = (u8*)&g_Battle.ui_mode;
    count                   = *counter;
    D_801485DF              = 2;
    *counter                = (count + 1);
||||||| 072714357
    D_80148628              = -190;
    D_8014862A              = 0x3F;
    g_UIPanelTasks[21].mode = 0;
    D_80148627              = 0;
    D_8014862E              = 1;
    counter                 = (u8*)&g_Battle.ui_mode;
    count                   = *counter;
    D_801485DF              = 2;
    *counter                = (count + 1);
=======
    D_80148628               = -190;
    D_8014862A               = 0x3F;
    g_UIPanelTasks[21].mode  = 0;
    D_80148627               = 0;
    D_8014862E               = 1;
    counter                  = (u8*)&g_Battle.ui_mode;
    count                    = *counter;
    g_UIPanelTasks[19].state = 2;
    *counter                 = (count + 1);
>>>>>>> public/main
}
