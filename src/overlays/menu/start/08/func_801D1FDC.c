#include "start_08.h"

MATCH void func_801D1FDC(void) {
    s32            i;
    u8             count;
    u32            index;
    MenuPanelTask* panel;

    Menu_ResetPanelTasks();
    i = 0;
    for (;;) {
        count = Party_CountOrder(0);
        index = i & BYTE_MASK;
        if (index >= count) {
            break;
        }
        panel = &g_MenuPanelTasks[4 + index];

        panel->unk_0A = i;
        i += 1;
        panel->unk_01 = 6;
        panel->active = 1;
        panel->unk_02 = 0;
        panel->state  = 0;
        panel->x      = 0x62;
        panel->y      = index * 0x36 + 0x3E;
        panel->unk_0B = 0;
        panel->unk_0C = 0;
    }
    panel         = &g_MenuPanelTasks[7];
    panel->unk_01 = 6;
    panel->unk_02 = 1;
    panel->state  = 0;
    panel->active = 1;
    panel++;
    g_MenuPanelTasks[7].x = 0xC8;
    g_MenuPanelTasks[7].y = 0x10;
    panel->unk_01         = 6;
    panel->unk_02         = 2;
    panel->state          = 0;
    panel->active         = 1;
    panel++;
    panel->unk_02 = 3;
    D_80148454    = 0x10;
    D_80148456    = 0x10;
    panel->unk_01 = 6;
    panel->state  = 0;
    panel->active = 1;
    panel->x      = 0x68;
    panel->y      = 0x2A;
    D_8014849A    = 4;
    panel->unk_0A = 0;
    panel->unk_0B = 0;
    panel->unk_0C = 0;
    panel->unk_10 = 0;
    D_80148499    = 6;
    D_8014849B    = 0;
    panel++;
    panel->active = 1;
    panel->x      = 0x73;
    panel->y      = 0x10;
    panel->unk_10 = 0;
}
