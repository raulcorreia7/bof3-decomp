#include "game_00.h"

/* func_801C1DF0 */
MATCH void Scene_RunScenario(s32 handler_index) {
    D_801CD4C0[g_SceneState.scenario_id][handler_index & BYTE_MASK]();
}
