#include "start_08.h"

MATCH void func_801D1FDC(void) {
    s32            i;
    u8             count;
    u32            index;
    MenuPanelTask* panel;

    Menu_ResetPanelTasks();
    i = 0;
    for (;;) {
        count = Party_CountOrder(PARTY_ORDER_FIELD);
        index = i & BYTE_MASK;
        if (index >= count) {
            break;
        }
        panel = &g_MenuPanelTasks[4 + index];

        panel->unk_0A = i;
        i += 1;
        panel->handler = 6;
        panel->active  = 1;
        panel->mode    = MENU_START_MODE_CHARACTER;
        panel->state   = 0;
        panel->pos.x   = 98;
        panel->pos.y   = index * 0x36 + 0x3E;
        panel->unk_0B  = 0;
        panel->unk_0C  = 0;
    }
    panel          = &g_MenuPanelTasks[7];
    panel->handler = 6;
    panel->mode    = MENU_START_MODE_ZENNY;
    panel->state   = 0;
    panel->active  = 1;
    panel++;
    g_MenuPanelTasks[7].pos.x = 200;
    g_MenuPanelTasks[7].pos.y = 16;
    panel->handler            = 6;
    panel->mode               = MENU_START_MODE_PLAY_TIME;
    panel->state              = 0;
    panel->active             = 1;
    panel++;
    panel->mode          = MENU_START_MODE_CAMP_ICONS;
    D_80148454           = 0x10;
    D_80148456           = 0x10;
    panel->handler       = 6;
    panel->state         = 0;
    panel->active        = 1;
    panel->pos.x         = 104;
    panel->pos.y         = 42;
    D_8014849A           = 4;
    panel->unk_0A        = 0;
    panel->unk_0B        = 0;
    panel->unk_0C        = 0;
    panel->u.addr.unk_10 = 0;
    D_80148499           = 6;
    D_8014849B           = 0;
    panel++;
    panel->active        = 1;
    panel->pos.x         = 115;
    panel->pos.y         = 16;
    panel->u.addr.unk_10 = 0;
}
