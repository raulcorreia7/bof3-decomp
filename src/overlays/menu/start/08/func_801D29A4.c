#include "start_08.h"

MATCH void func_801D29A4(void) {
    s32            i;
    u32            j;
    u8             count;
    u32            idx;
    MenuPanelTask* panel;
    u16*           entry;

    i = 0;
    for (;;) {
        count = Party_CountOrder(0);
        idx   = i & BYTE_MASK;
        if (idx >= (u32)count) {
            break;
        }
        panel         = &g_MenuPanelTasks[12 + idx];
        panel->unk_01 = 6;
        panel->unk_02 = 5;
        panel->state  = 2;
        panel->active = 1;
        panel->x      = 320;
        j             = idx + 4;
        entry         = (u16*)((u8*)&D_80148336 + j * 0x24);
        panel->y      = *entry;
        panel->unk_0A = i;
        i += 1;
    }
    panel                       = &g_MenuPanelTasks[11];
    panel->unk_01               = 6;
    panel->unk_02               = 9;
    panel->state                = 2;
    panel->active               = 1;
    panel->x                    = 0x14;
    D_801484C2                  = -0x14;
    panel->unk_10               = 0;
    g_MenuPanelTasks[19].unk_01 = 6;
    g_MenuPanelTasks[19].unk_02 = 0xA;
    panel += 8;
    panel->active = 0;
    panel->unk_0A = 0;
    panel->unk_0B = 1;
}
