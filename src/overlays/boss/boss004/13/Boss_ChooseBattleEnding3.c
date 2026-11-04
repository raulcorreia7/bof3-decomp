#include "boss004_13.h"

MATCH void Boss_ChooseBattleEnding3(void) {
    if (g_BattleResult & BATTLE_RESULT_DEFEAT) {
        g_BattlePartyOrder = 7;
        g_BattleOptions |= 0x80;
        func_801DDF28();
        g_SceneState.step_05 = 0x32;
    } else {
        u8* step;

        step = &g_SceneState.step_05;
        (*step)++;
        func_801DDF28();
    }
}
