#include "area078_13.h"

MATCH void func_801F2D78(void) {
    s8 choice;

    choice             = g_UIMessageChoice;
    g_UIMessageRequest = D_801F4184[choice];
    switch (choice) {
        case 0:
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.timer_06 = 0;
            g_ScenarioState.state_04 = 14;
            break;
        case 1:
            g_ScriptVars[0] = 0;
            break;
    }
}
