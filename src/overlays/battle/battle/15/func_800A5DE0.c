#include "battle_15.h"

MATCH void func_800A5DE0(void) {
    u8* counter;
    u8  count;

    Menu_OpenPanelTask(0x15, 5);
    D_80148628 = -190;
    D_8014862A = 0x3F;
    D_80148626 = 0;
    D_80148627 = 0;
    D_8014862E = 1;
    counter    = (u8*)&g_Battle.ui_state;
    count      = *counter;
    D_801485DF = 2;
    *counter   = (count + 1);
}
