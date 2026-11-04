#include "battle_03.h"

MATCH void func_801E679C(void) {
    PartyBattler* work;
    u8*           table;

    g_SpadWork->unk_29 = 0;
    g_SpadWork->unk_25 = 0x1D;
    g_SpadWork->unk_26 = 0;
    g_SpadWork->unk_24 = 0x84;
    g_SpadWork->unk_27 = D_801EB4A4[g_SpadWork->unk_07] + 0xB0;
    g_SpadWork->unk_28 = 0;
    work               = g_SpadWork;
    work->unk_2B       = 0;
    work->unk_2C.half  = 0;
    if (g_SpadWork->unk_07 != 6) {
        if ((u32)(g_SpadWork->word_08.byte.unk_08 - 1) < 2) {
            g_SpadWork->unk_2A = 1;
        } else {
            g_SpadWork->unk_2A = 0;
        }
    } else if (g_SpadWork->word_08.byte.unk_08 & 1) {
        g_SpadWork->unk_2A = 1;
    } else {
        g_SpadWork->unk_2A = 0;
    }
    g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    table               = D_801EB4B0 + (g_SpadWork->unk_07 << 1);
    Actor_SelectScript(table[g_SpadWork->word_08.byte.unk_08 >> 1]);
    Area_AddActor();
}
