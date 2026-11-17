#include "boss037_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScenarioState.step_05 = 28;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
