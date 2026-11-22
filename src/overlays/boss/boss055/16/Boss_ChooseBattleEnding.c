#include "boss055_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_VICTORY) {
        BOSS_SEND_PARTY_TO_ENDING_POSE(0)
        BOSS_SEND_PARTY_TO_ENDING_POSE(1)
        BOSS_SEND_PARTY_TO_ENDING_POSE(2)
        g_ScenarioState.step = 15;
        Battle_EndToArea();
        g_SndBGMId = 0xFF;
        return;
    }
    Battle_EndDefeat();
}
