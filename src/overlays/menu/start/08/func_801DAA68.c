#include "start_08.h"

void func_801DAC1C(void);

/* nonmatching: 10 rows. Both loops schedule `i++` (addiu s0,s0,1) before the row address; retail forms the address first
 * (first row 0x801DAAE0, again at 0x801DAB34 where the panel base and offset take v0/v1 the other way round). Tried:
 * for, while and do-while forms, a typed panel pointer against an indexed byte pointer, 7 min permuter. */
#ifdef NON_MATCHING
NON_MATCHING void func_801DAA68(void) {
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
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.x        = 0x14;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].pos.y        = 0x10;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = 0;
    while (i < 2) {
        rows[i].handler = 6;
        rows[i].mode    = MENU_START_MODE_CURSOR_FRAME;
        rows[i].active  = 0;
        rows[i].unk_0A  = 0;
        i++;
    }

    i = 0;
    while (i < (u8)Party_CountOrder(PARTY_ORDER_FIELD)) {
        panel          = &g_MenuPanelTasks[i + 4];
        panel->unk_0A  = i;
        panel->handler = 6;
        panel->mode    = 0;
        panel->state   = 0;
        panel->active  = 1;
        panel->pos.x   = 0x11;
        panel->pos.y   = i * 54 + 62;
        panel->unk_0B  = 1;
        panel->unk_0C  = 0;
        i++;
    }

    Menu_DrawClutStrip(D_80144953);
    func_801DAC1C();
    D_80148651 = 2;
    D_80148652 = 0;
    D_80148654 = 5;
}
#else
INCLUDE_ASM(func_801DAA68);
#endif
