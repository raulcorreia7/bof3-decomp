#include "battle_03.h"

MATCH void func_801E679C(void) {
    PartyMember* work;
    u8*          table;

    g_Task->unk_29    = 0;
    g_Task->unk_25    = 0x1D;
    g_Task->unk_26    = 0;
    g_Task->unk_24    = 0x84;
    g_Task->unk_27    = D_801EB4A4[g_Task->unk_07] + 0xB0;
    g_Task->unk_28    = 0;
    work              = g_Task;
    work->unk_2B      = 0;
    work->unk_2C.half = 0;
    if (g_Task->unk_07 != 6) {
        if ((u32)(g_Task->facing - 1) < 2) {
            g_Task->unk_2A = 1;
        } else {
            g_Task->unk_2A = 0;
        }
    } else if (g_Task->facing & 0x1) {
        g_Task->unk_2A = 1;
    } else {
        g_Task->unk_2A = 0;
    }
    g_Task->header.mode = g_Task->header.mode + 1;
    table               = D_801EB4B0 + (g_Task->unk_07 << 1);
    Actor_SelectScript(table[g_Task->facing >> 1]);
    Area_AddActor();
}
