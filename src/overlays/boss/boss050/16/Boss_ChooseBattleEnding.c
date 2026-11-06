#include "boss050_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_SceneState.step_05 = 0x10;
        func_801DDED8();
        g_SaveData.snd_bgm_id = 0x8C;
    } else {
        func_801DDF00();
    }
}
