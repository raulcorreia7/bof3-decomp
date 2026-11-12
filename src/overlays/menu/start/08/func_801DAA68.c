#include "start_08.h"

void func_801DAC1C(void);

MATCH void func_801DAA68(void) {
    u8*            record;
    MenuPanelTask* rows;
    MenuPanelTask* panel;
    u8             i;

    record = &D_801484BC;
    rows   = (MenuPanelTask*)(record + 0x120);
    i      = 0;
    record++;
    record--;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].handler      = 6;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].mode         = MENU_START_MODE_MESSAGE;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].state        = 2;
    record[0]                                                   = 1;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x        = 20;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y        = 16;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0;
    while (i < 2) {
        /* FAKE: retail adds the row offset and `rows` in this operand order; plain forms swap it. */
        panel = (MenuPanelTask*)(i * sizeof(MenuPanelTask) + (u32)rows);
        i++;
        panel->handler = 6;
        panel->mode    = MENU_START_MODE_CURSOR_FRAME;
        panel->active  = 0;
        panel->unk_0A  = 0;
    }

    i = 0;
    while (i < (u8)Party_CountOrder(PARTY_ORDER_FIELD)) {
        panel          = &g_MenuPanelTasks[i + 4];
        panel->unk_0A  = i;
        panel->handler = 6;
        panel->mode    = 0;
        panel->state   = 0;
        panel->active  = 1;
        panel->pos.x   = 17;
        panel->pos.y   = i * 54 + 62;
        panel->unk_0B  = 1;
        panel->unk_0C  = 0;
        i++;
    }

    Menu_DrawClutStrip(D_80144953);
    func_801DAC1C();
    g_MenuStep.sub_step = 2;
    g_MenuStep.state    = 0;
    D_80148654          = 5;
}
