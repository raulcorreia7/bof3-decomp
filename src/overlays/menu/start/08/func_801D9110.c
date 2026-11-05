#include "start_08.h"

MATCH void func_801D9110(void) {
    MenuPanelTask* panel;

    panel            = &g_MenuPanelTasks[11];
    D_801484BD       = 6;
    D_801484BE       = 9;
    D_801484BF       = 2;
    panel->unk_00[0] = 1;
    panel++;
    D_801484C0       = 0x14;
    D_801484C2       = -0x14;
    D_801484CC       = 0;
    D_801484E1       = 6;
    D_801484E2       = 0xD;
    D_801484E3       = 2;
    panel->unk_00[0] = 1;
    panel += 4;
    D_801484E6          = -0x14;
    D_801484E4          = 0x40;
    D_801484EA          = 2;
    D_801484EB          = 0xFF;
    D_80148571          = 6;
    D_80148572          = 0x11;
    g_BattleChoicePhase = 2;
    panel->unk_00[0]    = 1;
    panel += 3;
    D_80148574       = 0x140;
    D_80148576       = 0x3E;
    D_801485DE       = 0xA;
    D_8014857B       = 0;
    D_8014857A       = 0;
    D_8014857C       = 0xFF;
    D_8014857D       = 0xFF;
    D_80148578       = 0;
    D_80148579       = 0;
    D_80148580       = 0;
    D_801485DD       = 6;
    panel->unk_00[0] = 0;
    D_801485E6       = 1;
    D_801485E7       = 1;
    D_80148625       = 6;
    D_80148626       = 0xE;
    D_80148627       = 0;
    panel += 2;
    panel->unk_00[0] = 0;
}
