#include "start_08.h"

void func_801DAC1C(void);

/* nonmatching: one row differs. The cursor-frame loop adds the row offset and `rows` as `addu v1,v1,a2` in retail and
 * `addu v1,a2,v1` here (0x801DAAEC). `panel = &rows[i]; i++;` before the stores fixed the other nine rows. Tried:
 * i + rows, rows + i, &i[rows], &rows[i++], an index copy local (s32 and u8), i & 0xFF, (s32)i, the 0x120 base inline
 * in the loop (loses the shared base register), rows as &g_MenuPanelTasks[n]. Only
 * `(MenuPanelTask*)(i * sizeof(MenuPanelTask) + (u32)rows)` matches, and it adds two casts. */
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
        panel = &rows[i];
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
