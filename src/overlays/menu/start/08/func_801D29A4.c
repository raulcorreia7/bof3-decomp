#include "start_08.h"

MATCH void func_801D29A4(void) {
    s32            i;
    u8             count;
    u32            index;
    MenuPanelTask* panel;

    i = 0;
    for (;;) {
        count = Party_CountOrder(PARTY_ORDER_FIELD);
        index = i & BYTE_MASK;
        if (index >= count) {
            break;
        }
        panel         = &g_UiPanelTasks[12 + index];
        panel->panel  = 6;
        panel->mode   = MENU_START_MODE_STATS;
        panel->state  = 2;
        panel->active = 1;
        panel->pos.vx = 320;
        panel->pos.vy = g_UiPanelTasks[index + 4].pos.vy;
        panel->unk_0A = i;
        i += 1;
    }
    panel                                               = &g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION];
    panel->panel                                        = 6;
    panel->mode                                         = MENU_START_MODE_MESSAGE;
    panel->state                                        = 2;
    panel->active                                       = 1;
    panel->pos.vx                                       = 20;
    g_UiPanelTasks[11].pos.vy                           = -0x14;
    panel->u.addr.unk_10                                = 0;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].panel = 6;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME].mode  = MENU_START_MODE_CURSOR_FRAME;
    panel += 8;
    panel->active = 0;
    panel->unk_0A = 0;
    panel->unk_0B = 1;
}
