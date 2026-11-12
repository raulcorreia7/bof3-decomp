#include "start_08.h"

MATCH void func_801D9110(void) {
    MenuPanelTask* panel;

    panel          = &g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION];
    panel->handler = 6;
    panel->mode    = MENU_START_MODE_MESSAGE;
    panel->state   = 2;
    panel->active  = 1;
    panel++;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x        = 20;
    D_801484C2                                                  = -0x14;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0;
    panel->handler                                              = 6;
    panel->mode                                                 = MENU_START_MODE_COMMANDS;
    panel->state                                                = 2;
    panel->active                                               = 1;
    panel += 4;
    D_801484E6          = -0x14;
    D_801484E4          = 0x40;
    D_801484EA          = 2;
    D_801484EB          = 0xFF;
    panel->handler      = 6;
    panel->mode         = MENU_START_MODE_ABILITIES;
    g_BattleChoicePhase = 2;
    panel->active       = 1;
    panel += 3;
    /* the slide x and the skill-order cells keep their own symbols: retail schedules each store separately */
    D_80148574     = 0x140;
    D_80148576     = 0x3E;
    panel->mode    = MENU_START_MODE_CURSOR_FRAME;
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
