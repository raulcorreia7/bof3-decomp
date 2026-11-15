#include "game_00.h"

/* func_801C1E3C */
MATCH void Game_DispatchScenario(s32 handler_index) {
    D_801CD510[g_SceneState.scenario_id][handler_index & BYTE_MASK]();
}
