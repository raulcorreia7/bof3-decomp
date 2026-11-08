#include "boss032_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    u8* result;

    if (g_Battle.outcome.result & 2) {
        BOSS_SEND_PARTY_TO_ENDING_POSE(0)
        BOSS_SEND_PARTY_TO_ENDING_POSE(1)
        BOSS_SEND_PARTY_TO_ENDING_POSE(2)
        result     = &g_Battle.outcome.result;
        g_SndBGMId = 0x6B;
        D_80146875 = 0xE;
        *result |= 8;
        func_801DDED8();
        return;
    }
    func_801DDF00();
}
