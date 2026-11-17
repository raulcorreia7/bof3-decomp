#include "boss004_13.h"

MATCH void Boss_ChooseBattleEnding3(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        g_Game.battle_order = 7;
        g_Battle.outcome.options |= 0x80;
        Battle_EndToArea();
        g_ScenarioState.step_05 = 0x32;
    } else {
        u8* step;

        step = &g_ScenarioState.step_05;
        (*step)++;
        Battle_EndToArea();
    }
}
