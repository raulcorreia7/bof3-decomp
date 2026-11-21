#include "area193_13.h"

MATCH s32 func_801F2C9C(void) {
    g_UiMessageRequest = D_801F3A08[g_UiMessageChoice];
    if (g_UiMessageChoice == 1) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 1;
        g_ScenarioState.step_05  = 0;
    }
}
