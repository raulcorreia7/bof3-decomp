#include "game_00.h"

MATCH void func_801C1E3C(s32 handler_index) {
    D_801CD510[g_SceneState.scenario_id][handler_index & 0xFF]();
}
