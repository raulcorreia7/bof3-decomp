#include "boss050_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScenarioState.step = 0x10;
        Battle_EndVictory();
        g_SndBGMId = 0x8C;
    } else {
        Battle_EndDefeat();
    }
}
