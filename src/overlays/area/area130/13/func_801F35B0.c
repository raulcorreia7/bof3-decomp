#include "area130_13.h"

MATCH void func_801F35B0(void) {
    g_UIMessageRequest = D_801F5058[g_UIMessageChoice];
    switch (g_UIMessageChoice) {
        case 0:
            g_ScenarioState.step = 0xA;
            *g_ScriptVars        = 0;
            SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
            g_ScenarioState.state_04 = 6;
            break;
        case 1:
            *g_ScriptVars = 0;
            break;
    }
}
