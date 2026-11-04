#include "boss002_16.h"

MATCH void Boss_ChooseBattleEnding3(void) {
    if (g_BattleResult & BATTLE_RESULT_VICTORY) {
        g_SceneState.step_05 = 5;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
