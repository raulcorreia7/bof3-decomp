#include "boss030_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    u8* visit_count;

    if BATTLE_IS_VICTORY () {
        visit_count = &g_ScriptVars[0];
        (*visit_count)++;
        g_SceneState.step_05 = 0xC;
        func_801DDED8();
        g_SndBgmId = 0x5A;
    } else {
        func_801DDF00();
    }
}
