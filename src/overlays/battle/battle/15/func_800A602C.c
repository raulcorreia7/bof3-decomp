#include "battle_15.h"

MATCH void func_800A602C(void) {
    u8* counter;
    u8  count;

    g_BattlePanelMode = 3;
    Menu_ArmPanelTask(0x13, 5);
    D_801485DE = 4;
    D_801485DF = 0;
    D_801485E0 = 0x15B;
    counter    = (u8*)&g_Battle.ui_state;
    count      = *counter;
    D_801485E2 = 0x3F;
    D_801485EC = 0;
    D_801485EE = 0;
    *counter   = (count + 1);
}
