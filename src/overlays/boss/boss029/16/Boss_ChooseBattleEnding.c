#include "boss029_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_SceneState.step_05 = 0x1C;
        func_801DDED8();
        g_SndBgmId = 0x62;
    } else {
        func_801DDF00();
    }
}
