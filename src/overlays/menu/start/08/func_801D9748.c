#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D9748(void) {
    volatile u8*   record;
    MenuPanelTask* rows;
    u8             i;

    record                                                      = &D_801484BC;
    rows                                                        = (MenuPanelTask*)(record + 0x120);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].panel        = 6;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].mode         = MENU_START_MODE_MESSAGE;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].state        = 2;
    record[0]                                                   = 1;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x        = 0x14;
    LOH(g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y)   = -0x14;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0;
    for (i = 0; i < 2; i++) {
        rows[i].panel  = 6;
        rows[i].mode   = MENU_START_MODE_CURSOR_FRAME;
        rows[i].active = 0;
        rows[i].unk_0A = 0;
    }
    g_MenuPanelTasks[18].mode                        = MENU_START_MODE_COMMANDS;
    g_BattlePanelMode                                = 2;
    D_801485B8                                       = 1;
    g_BattleItemRow                                  = 7;
    g_MenuPanelTasks[18].unk_0B                      = 0xFF;
    g_MenuPanelTasks[18].pos.x                       = 0x70;
    LOH(g_MenuPanelTasks[18].pos.y)                  = -0x14;
    g_MenuPanelTasks[18].panel                       = 6;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].panel  = 6;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].mode   = MENU_START_MODE_CURSOR;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
    Menu_DrawClutStrip(D_80144953);
    D_801ED68C = 0;
    SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 2));
    D_80148654       = 5;
    g_MenuStep.state = 0;
    g_MenuStep.sub_step += 1;
}
#else
INCLUDE_ASM(func_801D9748);
#endif
