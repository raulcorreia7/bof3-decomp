#include "boss055_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if (g_BattleOutcome.result & 2) {
        BOSS_SEND_PARTY_TO_ENDING_POSE(0)
        BOSS_SEND_PARTY_TO_ENDING_POSE(1)
        BOSS_SEND_PARTY_TO_ENDING_POSE(2)
        D_80146875 = 0xF;
        func_801DDF28();
        g_SndBGMId = 0xFF;
        return;
    }
    func_801DDF00();
}
