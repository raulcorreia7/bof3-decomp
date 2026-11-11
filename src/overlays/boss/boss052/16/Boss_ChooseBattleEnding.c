#include "boss052_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_VICTORY) {
        BOSS_SEND_PARTY_TO_ENDING_POSE(0)
        BOSS_SEND_PARTY_TO_ENDING_POSE(1)
        BOSS_SEND_PARTY_TO_ENDING_POSE(2)
        D_80146875 = 0x1A;
        func_801DDED8();
        return;
    }
    func_801DDF00();
}
