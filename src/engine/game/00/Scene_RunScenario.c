#include "game_00.h"

/* func_801C1DF0 */
MATCH void Scene_RunScenario(s32 step_index) {
    D_801CD4C0[g_SceneState.scenario_id][step_index & BYTE_MASK]();
}
