#include "area193_13.h"

MATCH s32 func_801F2C9C(void) {
    g_UIMessageRequest = D_801F3A08[g_UIMessageChoice];
    if (g_UIMessageChoice == 1) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 1;
        g_ScenarioState.step     = 0;
    }
}
