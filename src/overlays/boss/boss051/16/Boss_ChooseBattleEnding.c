#include "boss051_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_SceneState.step_05 = 15;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
