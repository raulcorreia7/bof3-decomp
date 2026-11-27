#include "area094_13.h"

MATCH void func_801F2DC4(void) {
    u8 state;

    g_UIMessageRequest = D_801F535C[g_UIMessageChoice];
    switch (g_UIMessageChoice) {
        case 0:
        default:
            return;

        case 1:
            Game_SetScriptActive();
            g_ScenarioState.step = 0x32;
            state                = 7;
            break;

        case 2:
            if (SYS_TestFlag(g_SceneFlags, 32)) {
                Game_SetScriptActive();
                g_ScenarioState.step = 2;
                state                = 9;
                break;
            }
            Game_SetScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step = 0;
            state                = 9;
            goto state_store;
    }
    SCRIPT_VARS_CLEAR_ALL();
state_store:
    g_ScenarioState.state_04 = state;
}
