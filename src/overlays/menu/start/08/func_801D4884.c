#include "start_08.h"

MATCH void func_801D4884(void) {
    u8* ptr = &D_801484BC;
    u8  value;

    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].handler = 6;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].mode    = 9;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].state   = 2;
    *ptr                                                   = 1;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x   = 0x14;
    D_801484C2                                             = -0x14;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].unk_10  = 0;
    ptr += 0x24;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].handler = 6;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].mode    = 0xD;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].state   = 2;
    *ptr                                                = 1;
    D_801484E6                                          = -0x14;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].pos.x   = 0x40;
    g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A  = 0;
    {
        /* FAKE: keep the retail byte value in $a0 across both stores. */
        MATCH_REG(u8, byte, "a0");

        byte                                               = 0xFF;
        g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0B = byte;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].handler   = 6;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].mode      = 0xC;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].state     = 2;
        ptr += 0x24;
        *ptr = 1;
        ptr += 0xD8;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = byte;
        g_MenuPanelTasks[MENU_START_PANEL_ITEMS].flags  = byte;
    }
    value                                                   = *s_ChoiceMenuValues;
    D_80148508                                              = -0xC8;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.y          = 0x3E;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].mode    = 0xA;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A         = 0;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_08         = 0;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_09         = 0;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_10         = 0;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_12         = 0;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].handler = 6;
    g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B         = value;
    *ptr                                                    = 0;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0A  = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B  = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].handler       = 6;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].mode          = 0xE;
    D_80148627                                              = 0;
    /* FAKE: keep the updated record pointer for the final store. */
    MATCH_FAKE_OPAQUE(ptr);
    ptr[0x48] = 0;
}
