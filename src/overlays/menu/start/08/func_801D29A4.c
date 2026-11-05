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
        panel            = &g_MenuPanelTasks[12 + idx];
        panel->unk_00[1] = 6;
        panel->unk_00[2] = 5;
        panel->state     = 2;
        panel->unk_00[0] = 1;
        panel->x         = 320;
        j                = idx + 4;
        entry            = (u16*)((u8*)&D_80148336 + j * 0x24);
        panel->y         = *entry;
        panel->unk_0A    = i;
        i += 1;
    }
    panel            = &g_MenuPanelTasks[11];
    D_801484BD       = 6;
    D_801484BE       = 9;
    D_801484BF       = 2;
    panel->unk_00[0] = 1;
    D_801484C0       = 0x14;
    D_801484C2       = -0x14;
    D_801484CC       = 0;
    D_801485DD       = 6;
    D_801485DE       = 0xA;
    panel += 8;
    panel->unk_00[0] = 0;
    D_801485E6       = 0;
    D_801485E7       = 1;
}
