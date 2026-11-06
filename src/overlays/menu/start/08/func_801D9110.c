#include "start_08.h"

MATCH void func_801D9110(void) {
    MenuPanelTask* panel;

    panel          = &g_MenuPanelTasks[11];
    panel->handler = 6;
    panel->mode    = 9;
    panel->state   = 2;
    panel->active  = 1;
    panel++;
    g_MenuPanelTasks[11].pos.x  = 0x14;
    D_801484C2                  = -0x14;
    g_MenuPanelTasks[11].unk_10 = 0;
    panel->handler              = 6;
    panel->mode                 = 0xD;
    panel->state                = 2;
    panel->active               = 1;
    panel += 4;
    D_801484E6          = -0x14;
    D_801484E4          = 0x40;
    D_801484EA          = 2;
    D_801484EB          = 0xFF;
    panel->handler      = 6;
    panel->mode         = 0x11;
    g_BattleChoicePhase = 2;
    panel->active       = 1;
    panel += 3;
    D_80148574     = 0x140;
    D_80148576     = 0x3E;
    panel->mode    = 0xA;
    D_8014857B     = 0;
    D_8014857A     = 0;
    D_8014857C     = 0xFF;
    D_8014857D     = 0xFF;
    D_80148578     = 0;
    D_80148579     = 0;
    D_80148580     = 0;
    panel->handler = 6;
    panel->active  = 0;
    panel->unk_0A  = 1;
    panel->unk_0B  = 1;
    D_80148625     = 6;
    D_80148626     = 0xE;
    D_80148627     = 0;
    panel += 2;
    panel->active = 0;
}
