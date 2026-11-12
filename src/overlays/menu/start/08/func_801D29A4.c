#include "start_08.h"

MATCH void func_801D29A4(void) {
    s32            i;
    u32            j;
    u8             count;
    u32            index;
    MenuPanelTask* panel;
    u16*           entry;

    i = 0;
    for (;;) {
        count = Party_CountOrder(PARTY_ORDER_FIELD);
        index = i & BYTE_MASK;
        if (index >= count) {
            break;
        }
        panel          = &g_MenuPanelTasks[12 + index];
        panel->handler = 6;
        panel->mode    = MENU_START_MODE_STATS;
        panel->state   = 2;
        panel->active  = 1;
        panel->pos.x   = 320;
        j              = index + 4;
        entry          = (u16*)((u8*)&D_80148336 + j * 0x24);
        panel->pos.y   = *entry;
        panel->unk_0A  = i;
        i += 1;
    }
    panel                                                   = &g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION];
    panel->handler                                          = 6;
    panel->mode                                             = MENU_START_MODE_MESSAGE;
    panel->state                                            = 2;
    panel->active                                           = 1;
    panel->pos.x                                            = 20;
    D_801484C2                                              = -0x14;
    panel->u.addr.unk_10                                    = 0;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].handler = 6;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].mode    = MENU_START_MODE_CURSOR_FRAME;
    panel += 8;
    panel->active = 0;
    panel->unk_0A = 0;
    panel->unk_0B = 1;
}
