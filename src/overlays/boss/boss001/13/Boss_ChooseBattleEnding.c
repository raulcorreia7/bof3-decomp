#include "boss001_13.h"
#include "scenario/state.h"

/* func_800C1FF8 */
MATCH void Boss_ChooseBattleEnding(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        g_ScenarioState.state_04 = 6;
        g_ScenarioState.step_05  = 0x32;
    } else {
        g_ScenarioState.step_05++;
    }
    Battle_EndToArea();
}
