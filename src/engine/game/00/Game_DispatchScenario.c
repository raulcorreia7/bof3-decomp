#include "game_00.h"

/* func_801C1E3C */
MATCH void Game_DispatchScenario(s32 step_index) {
    D_801CD510[g_ScenarioState.scenario_id][step_index & BYTE_MASK]();
}
