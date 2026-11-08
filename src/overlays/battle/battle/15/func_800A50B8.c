#include "battle_15.h"

MATCH void func_800A50B8(void) {
    u8* counter;
    u8  count;

    Menu_OpenPanelTask(0x15, 5);
    D_80148628        = 0x142;
    D_80148626        = 0;
    D_80148627        = 0;
    D_8014862A        = 0x3F;
    counter           = (u8*)&g_Battle.ui_state;
    count             = *counter;
    g_BattlePanelMode = 2;
    *counter          = (count + 1);
}
