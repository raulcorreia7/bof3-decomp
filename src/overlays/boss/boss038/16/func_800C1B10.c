#include "boss038_16.h"
#include "scenario/state.h"

MATCH void func_800C1B10(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_VICTORY) {
        g_ScriptVars[0]         = 5;
        g_ScenarioState.step_05 = 0x20;
        g_SndBGMId              = 0x77;
        Battle_EndVictory();
        return;
    }
    Battle_EndDefeat();
}
