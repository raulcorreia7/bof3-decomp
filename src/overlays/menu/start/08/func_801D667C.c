#include "start_08.h"

MATCH void func_801D667C(void) {
    MenuPanelTask* panel;

    panel         = &g_MenuPanelTasks[11];
    D_801484BD    = 6;
    D_801484BE    = 9;
    D_801484BF    = 2;
    panel->active = 1;
    panel++;
    D_801484C0    = 0x14;
    D_801484C2    = -0x14;
    D_801484CC    = 0;
    D_801484E1    = 6;
    D_801484E2    = 0xD;
    D_801484E3    = 2;
    panel->active = 1;
    panel++;
    D_801484E6    = -0x14;
    D_801484E4    = 0x40;
    D_801484EA    = 1;
    D_801484EB    = 0xFF;
    D_80148505    = 6;
    D_80148506    = 0x10;
    D_80148507    = 2;
    panel->active = 1;
    panel += 6;
    D_80148504.x            = 320;
    D_80148504.y            = 62;
    D_80148524              = &D_801ED63C;
    D_801485DE              = 0xA;
    D_80148504.group_cursor = 0;
    D_80148504.group        = 0xFF;
    D_80148504.group_first  = 0xFF;
    D_80148504.drawn_cursor = 1;
    D_801485DD              = 6;
    panel->active           = 0;
    D_801485E6              = 1;
    D_801485E7              = 1;
    D_80148625              = 6;
    D_80148626              = 0xE;
    D_80148627              = 0;
    panel += 2;
    panel->active = 0;
}
