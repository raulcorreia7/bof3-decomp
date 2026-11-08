#include "boss004_13.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        g_Game.battle_order = 7;
        g_Battle.outcome.options |= 0x80;
        func_801DDF28();
        g_SceneState.step_05 = 0x32;
    } else {
        u8* step;

        step = &g_SceneState.step_05;
        (*step)++;
        func_801DDF28();
    }
}
