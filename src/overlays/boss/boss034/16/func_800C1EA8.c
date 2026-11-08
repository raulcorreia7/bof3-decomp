#include "boss034_16.h"

MATCH void func_800C1EA8(void) {
    u8 i;

    for (i = 0; i < 3; i++) {
        if (g_Game.members[i].unk_13A[2] == D_80181B14) {
            D_800C2778 = i;
        }
    }
    g_Battle.choose_ending_hook = func_800C20A8;
    g_Battle.end_hook           = func_800C22D0;
    g_Battle.boss_event_hook    = func_800C1F30;
}
