#include "game_00.h"

MATCH void func_801C1DF0(s32 handler_index) {
    D_801CD4C0[g_SceneState.scenario_id][handler_index & 0xFF]();
}
