#include "area094_13.h"

MATCH void func_801F2DC4(void) {
    u8 state;

    g_MessageRequest = D_801F535C[g_MessageChoice];
    switch (g_MessageChoice) {
        case 0:
        default:
            return;

        case 1:
            Game_SetScriptActive();
            g_SceneState.step_05 = 0x32;
            state                = 7;
            break;

        case 2:
            if (SYS_TestFlag(g_SceneFlags, 32)) {
                Game_SetScriptActive();
                g_SceneState.step_05 = 2;
                state                = 9;
                break;
            }
            Game_SetScriptActive();
            g_ScriptVars[0]      = 0;
            g_ScriptVars[1]      = 0;
            g_ScriptVars[2]      = 0;
            g_ScriptVars[3]      = 0;
            g_SceneState.step_05 = 0;
            state                = 9;
            goto state_store;
    }
    g_ScriptVars[0] = 0;
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
state_store:
    g_SceneState.state_04 = state;
}
