#include "boss055_16.h"

MATCH void func_800C227C(void) {
    if (g_BattleState & 4) {
        if (LOHU(g_BattleActionId) == 0x81) {
            ((PartyBattler*)g_SpadWork)->word_08.byte.unk_0B = 1;
            D_801463BE                                       = 8;
            ((PartyBattler*)g_SpadWork)->unk_02              = 3;
            return;
        }
        func_801E567C();
    }
}
