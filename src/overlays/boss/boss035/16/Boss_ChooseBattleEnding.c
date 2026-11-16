#include "boss035_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_SceneState.step_05 = 21;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
