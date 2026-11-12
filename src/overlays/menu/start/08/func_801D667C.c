#include "start_08.h"

MATCH void func_801D667C(void) {
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
    panel++;
    D_801484E6     = -0x14;
    D_801484E4     = 0x40;
    D_801484EA     = 1;
    D_801484EB     = 0xFF;
    panel->handler = 6;
    panel->mode    = MENU_START_MODE_EQUIP_COMPARE;
    panel->state   = 2;
    panel->active  = 1;
    panel += 6;
    D_80148504.pos.x        = 320;
    D_80148504.pos.y        = 62;
    D_80148524              = g_EquipPreview;
    panel->mode             = MENU_START_MODE_CURSOR_FRAME;
    D_80148504.group_cursor = 0;
    D_80148504.group        = 0xFF;
    D_80148504.group_first  = 0xFF;
    D_80148504.drawn_cursor = 1;
    panel->handler          = 6;
    panel->active           = 0;
    panel->unk_0A           = 1;
    panel->unk_0B           = 1;
    D_80148625              = 6;
    D_80148626              = 0xE;
    D_80148627              = 0;
    panel += 2;
    panel->active = 0;
}
