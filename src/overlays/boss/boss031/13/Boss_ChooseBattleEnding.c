#include "boss031_13.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_SceneState.step_05 = 0x14;
        func_801DDED8();
    } else {
        g_BattleOptions &= 0xBF;
        func_801DDF00();
    }
}
