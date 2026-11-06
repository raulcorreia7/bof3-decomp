#include "area191_13.h"

MATCH void func_801F2DBC(void) {
    u8* state;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        state               = &g_SceneState.step_05;
        *state              = *state + 1;
        g_Task->header.mode = 3;
    }
    func_801F2E34();
}
