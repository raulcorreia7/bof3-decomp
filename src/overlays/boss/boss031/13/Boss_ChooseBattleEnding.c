#include "boss031_13.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScenarioState.step = 0x14;
        Battle_EndVictory();
    } else {
        g_Battle.outcome.options &= 0xBF;
        Battle_EndDefeat();
    }
}
