#include "shop_00.h"

MATCH void func_801E2650(void) {
    u8* panel;
    s32 offset;

    panel                     = (u8*)g_MenuPanelTasks;
    D_80148331                = 7;
    D_80148332                = 0;
    g_MenuPanelTasks[0].state = 2;
    panel[0]                  = 1;
    D_80148334                = 0x14;
    /* FAKE: retail reads D_80148336 as s16. */
    (*(s16*)&D_80148336)      = -0x14;
    D_80148626                = 3;
    D_80148340                = 0;
    D_80148625                = 7;
    offset                    = 0x2D0;
    panel                     = panel + 0x2F4;
    panel[0]                  = 0;
    D_80148356                = 0xF;
    D_80148360                = 0x7F;
    D_80148358                = -0x64;
    D_80148355                = 7;
    D_80148357                = 2;
    D_8014835F                = 0;
    D_8014835E                = 0;
    D_80148361                = 0;
    D_8014835C                = 0;
    D_8014835A                = 0x3E;
    panel[-offset]            = 1;
}
