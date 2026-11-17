#include "boss007_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    u8* result;

    result = &g_BattleResult;
    if (*result & BATTLE_RESULT_DEFEAT) {
        g_Game.battle_order      = 6;
        g_ScenarioState.state_04 = 6;
        g_ScenarioState.step_05  = 50;
    } else {
        g_Game.battle_order = 2;
        g_AreaDrawFlags     = 0;
        *result |= BATTLE_RESULT_NO_BGM;
        g_SndBGMId = 4;
        g_ScenarioState.step_05++;
    }
    Battle_EndToArea();
}
