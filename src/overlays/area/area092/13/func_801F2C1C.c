#include "area092_13.h"

MATCH void func_801F2C1C(void) {
    s8 choice = g_MessageChoice;

    g_MessageRequest = D_801F41B0[choice];
    switch (choice) {
        case 2:
            Game_SetScriptActive();
            g_SceneState.step_05 = 10;
            break;
        case 3:
            Game_SetScriptActive();
            g_SceneState.step_05 = 30;
            break;
        case 4:
            Game_SetScriptActive();
            g_SceneState.step_05 = 20;
            break;
        case 0:
        case 1:
        case 5:
        default:
            return;
    }
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 8;
}
