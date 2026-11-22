#include "boss036_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScenarioState.step = 8;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
