#include "start_08.h"

/* func_801D9748 */
#ifdef NON_MATCHING
NON_MATCHING void Menu_OpenPartyScreen(void) {
    MenuPanelTask* record;
    MenuPanelTask* panels;
    u8             i;

    record               = &g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION];
    panels               = &g_UiPanelTasks[19];
    record->panel        = 6;
    record->mode         = MENU_START_MODE_MESSAGE;
    record->state        = 2;
    record->active       = 1;
    record->pos.vx       = 0x14;
    record->pos.vy       = -0x14;
    record->u.message.id = 0;
    for (i = 0; i < 2; i++) {
        panels[i].panel  = 6;
        panels[i].mode   = MENU_START_MODE_CURSOR_FRAME;
        panels[i].active = 0;
        panels[i].unk_0A = 0;
    }
    g_UiPanelTasks[18].panel                       = 6;
    g_UiPanelTasks[18].mode                        = MENU_START_MODE_COMMANDS;
    g_BattlePanelMode                              = 2;
    D_801485B8                                     = 1;
    g_BattleEquipSlot                              = 7;
    g_UiPanelTasks[18].unk_0B                      = 0xFF;
    g_UiPanelTasks[18].pos.vx                      = 0x70;
    g_UiPanelTasks[18].pos.vy                      = -0x14;
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
