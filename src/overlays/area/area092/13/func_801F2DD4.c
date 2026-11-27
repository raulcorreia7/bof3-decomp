#include "area092_13.h"

MATCH void func_801F2DD4(void) {
    s8 choice;
    u8 event;

    choice             = g_UIMessageChoice;
    g_UIMessageRequest = D_801F41C4[choice];
    switch (choice) {
        case 0:
            Game_SetScriptActive();
            event = 60;
            break;
        case 1:
            if (SYS_TestFlag(g_SceneFlags, 27) == 0) {
                Game_SetScriptActive();
                event = 18;
            } else {
                Game_SetScriptActive();
                event = 35;
            }
            break;
        default:
            return;
    }
    g_ScenarioState.step     = event;
    g_ScriptVars[0]          = 0;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 7;
}
