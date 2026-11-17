#include "boss002_16.h"

MATCH void Boss_ChooseBattleEnding3(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_VICTORY) {
        g_ScenarioState.step_05 = 5;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
