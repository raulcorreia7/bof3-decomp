#include "boss029_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScenarioState.step_05 = 0x1C;
        Battle_EndVictory();
        g_SndBGMId = 0x62;
    } else {
        Battle_EndDefeat();
    }
}
