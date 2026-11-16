#include "boss040_16.h"

MATCH void Boss_ChooseBattleEnding2(void) {
    if BATTLE_IS_VICTORY () {
        g_SceneState.step_05 = 38;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
