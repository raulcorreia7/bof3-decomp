#include "shop_00.h"

MATCH void func_801D334C(void) {
    u8* p;
    u8* counter;

    p                         = (u8*)g_MenuPanelTasks;
    D_80148331                = 7;
    D_80148332                = 0;
    g_MenuPanelTasks[0].state = 2;
    *p                        = 1;
    p += 0x24;
    D_80148334           = 0x14;
    /* FAKE: retail reads D_80148336 as s16. */
    (*(s16*)&D_80148336) = -0x14;
    D_80148340           = 0;
    D_80148355           = 7;
    D_80148356           = 1;
    D_80148357           = 2;
    *p                   = 1;
    p += 0x2D0;
    D_80148358 = 0x68;
    D_8014835A = -0x14;
    D_80148625 = 7;
    D_80148626 = 3;
    *p         = 0;
    D_80148430 = BATTLE_PARTY_STRIDE;
    D_80148432 = 0x3E;
    p -= 0x1F8;
    *p         = 1;
    D_8014842D = 7;
    D_8014842E = 9;
    D_8014842F = 2;
    D_80148436 = 0;
    D_80148437 = 0;
    D_80148438 = 0;
    D_80148439 = 0xFF;
    D_80148434 = 3;
    D_80148435 = 0;
    D_8014843C = 0;
    D_8014843E = 0;
    D_801E6058 = 0;
    D_801E606C = 1;
    counter    = &g_MenuStep.sub_step;
    *counter += 2;
    g_MenuStep.state = 0;
}
