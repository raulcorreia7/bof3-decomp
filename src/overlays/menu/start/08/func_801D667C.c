#include "start_08.h"

MATCH void func_801D667C(void) {
    MenuPanelTask* panel;

    panel         = &g_MenuPanelTasks[11];
    panel->unk_01 = 6;
    panel->unk_02 = 9;
    panel->state  = 2;
    panel->active = 1;
    panel++;
    g_MenuPanelTasks[11].x      = 0x14;
    D_801484C2                  = -0x14;
    g_MenuPanelTasks[11].unk_10 = 0;
    panel->unk_01               = 6;
    panel->unk_02               = 0xD;
    panel->state                = 2;
    panel->active               = 1;
    panel++;
    D_801484E6    = -0x14;
    D_801484E4    = 0x40;
    D_801484EA    = 1;
    D_801484EB    = 0xFF;
    panel->unk_01 = 6;
    panel->unk_02 = 0x10;
    panel->state  = 2;
    panel->active = 1;
    panel += 6;
    D_80148504.x            = 320;
    D_80148504.y            = 62;
    D_80148524              = &D_801ED63C;
    panel->unk_02           = 0xA;
    D_80148504.group_cursor = 0;
    D_80148504.group        = 0xFF;
    D_80148504.group_first  = 0xFF;
    D_80148504.drawn_cursor = 1;
    panel->unk_01           = 6;
    panel->active           = 0;
    panel->unk_0A           = 1;
    panel->unk_0B           = 1;
    D_80148625              = 6;
    D_80148626              = 0xE;
    D_80148627              = 0;
    panel += 2;
    panel->active = 0;
}
