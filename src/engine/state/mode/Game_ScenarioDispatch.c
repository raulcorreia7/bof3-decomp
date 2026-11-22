#include "engine/game/00/game_00.h"

/* func_801C1E3C */
MATCH void Game_ScenarioDispatch(s32 handler_index) {
    D_801CD510[g_ScenarioState.scenario_id][handler_index & BYTE_MASK]();
}
