#include "start_08.h"

/* func_801D9748 */
#ifdef NON_MATCHING
NON_MATCHING void Menu_OpenPartyScreen(void) {
    u8*            record;
    MenuPanelTask* panels;
    MenuPanelTask* panel;
    u8             i;

    record                                                    = &D_801484BC;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].panel        = 6;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].mode         = MENU_START_MODE_MESSAGE;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].state        = 2;
    record[0]                                                 = 1;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x        = 0x14;
    LOH(g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y)   = -0x14;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0;
    panels                                                    = (MenuPanelTask*)(record + 0x120);
    i                                                         = 0;
    while (i < 2) {
        panel = (MenuPanelTask*)(i * sizeof(MenuPanelTask) + (u32)panels);
        i++;
        panel->panel  = 6;
        panel->mode   = MENU_START_MODE_CURSOR_FRAME;
        panel->active = 0;
        panel->unk_0A = 0;
    }

    g_UiPanelTasks[18].mode                        = MENU_START_MODE_COMMANDS;
    g_BattlePanelMode                              = 2;
    g_UiPanelTasks[18].active                      = 1;
    g_BattleItemRow                                = 7;
    g_UiPanelTasks[18].unk_0B                      = 0xFF;
    g_UiPanelTasks[18].pos.x                       = 0x70;
    LOH(g_UiPanelTasks[18].pos.y)                  = -0x14;
    g_UiPanelTasks[18].panel                       = 6;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].panel  = 6;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].mode   = MENU_START_MODE_CURSOR;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active = 0;
    Menu_DrawClutStrip(g_WindowClut);
    g_MenuPartyCommand = 0;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
    D_80148654       = 5;
    g_MenuStep.state = 0;
    g_MenuStep.sub_step += 1;
}
#else
INCLUDE_ASM(Menu_OpenPartyScreen);
#endif
