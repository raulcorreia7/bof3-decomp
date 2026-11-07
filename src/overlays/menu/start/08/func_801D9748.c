#include "start_08.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 92.47%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D9748(void) {
    volatile u8*   record;
    MenuPanelTask* rows;
    u8             i;

    record                                                 = &D_801484BC;
    i                                                      = 0;
    rows                                                   = (MenuPanelTask*)(record + 0x120);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].handler = 6;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].mode    = MENU_START_MODE_MESSAGE;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].state   = 2;
    record[0]                                              = 1;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x   = 0x14;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y   = -0x14;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].unk_10  = 0;
    while (i < 2) {
        rows[i].handler = 6;
        rows[i].mode    = MENU_START_MODE_CURSOR_FRAME;
        rows[i].active  = 0;
        rows[i].unk_0A  = 0;
        i++;
    }
    g_MenuPanelTasks[18].mode                         = MENU_START_MODE_COMMANDS;
    g_BattlePanelMode                                 = 2;
    D_801485B8                                        = 1;
    g_BattleItemRow                                   = 7;
    g_MenuPanelTasks[18].unk_0B                       = 0xFF;
    g_MenuPanelTasks[18].pos.x                        = 0x70;
    g_MenuPanelTasks[18].pos.y                        = -0x14;
    g_MenuPanelTasks[18].handler                      = 6;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].handler = 6;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].mode    = MENU_START_MODE_CURSOR;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active  = 0;
    Menu_DrawClutStrip(D_80144953);
    D_801ED68C = 0;
    SND_PlayCue(EMI_CUE_ID(1, 2));
    D_80148654 = 5;
    D_80148652 = 0;
    D_80148651 += 1;
}
#else
INCLUDE_ASM(func_801D9748);
#endif
