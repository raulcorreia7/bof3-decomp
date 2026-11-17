#include "boss049_16.h"

MATCH void Boss_ChooseBattleEnding2(void) {
    if BATTLE_IS_VICTORY () {
        g_ScenarioState.step_05 = 10;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
