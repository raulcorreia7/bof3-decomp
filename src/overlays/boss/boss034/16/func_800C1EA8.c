#include "boss034_16.h"

MATCH void func_800C1EA8(void) {
    u8 i;

    for (i = 0; i < 3; i++) {
        if (g_BattlePartyBattlers[i].unk_13A[2] == D_80181B14) {
            D_800C2778 = i;
        }
    }
    g_BattleChooseEndingHook = func_800C20A8;
    g_BattleEndHook          = func_800C22D0;
    g_BossBattleEventHook    = func_800C1F30;
}
