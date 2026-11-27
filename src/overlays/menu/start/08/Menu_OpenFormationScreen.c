#include "start_08.h"

/* func_801DAA68 */
MATCH void Menu_OpenFormationScreen(void) {
    u8*            record;
    MenuPanelTask* panels;
    MenuPanelTask* panel;
    u8             i;

    record = &g_UIPanelTasks[11].active;
    panels = (MenuPanelTask*)(record + 0x120);
    i      = 0;
    record++;
    record--;
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].panel        = 6;
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].mode         = MENU_START_MODE_MESSAGE;
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].state        = 2;
    record[0]                                                 = 1;
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.vx       = 20;
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.vy       = 16;
    g_UIPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0;
    while (i < 2) {
        /* FAKE: retail adds the panel offset and `panels` in this operand order; plain forms swap it. */
        panel = (MenuPanelTask*)(i * sizeof(MenuPanelTask) + (u32)panels);
        i++;
        panel->panel  = 6;
        panel->mode   = MENU_START_MODE_CURSOR_FRAME;
        panel->active = 0;
        panel->unk_0A = 0;
    }

    i = 0;
    while (i < (u8)Party_CountOrder(PARTY_ORDER_FIELD)) {
        panel         = &g_UIPanelTasks[i + 4];
        panel->unk_0A = i;
        panel->panel  = 6;
        panel->mode   = 0;
        panel->state  = 0;
        panel->active = 1;
        panel->pos.vx = 17;
        panel->pos.vy = i * 54 + 62;
        panel->unk_0B = 1;
        panel->unk_0C = 0;
        i++;
    }

    Menu_DrawClutStrip(g_WindowClut);
    Menu_OpenFormation();
    g_MenuStep.sub_step = 2;
    g_MenuStep.state    = 0;
    D_80148654          = 5;
}
