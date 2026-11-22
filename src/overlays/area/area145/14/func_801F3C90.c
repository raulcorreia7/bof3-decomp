#include "area145_14.h"

MATCH void func_801F3C90(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        g_ScriptVars[0] = 8;
    } else {
        g_ScriptVars[0]          = 0xA;
        g_ScenarioState.state_04 = 3;
        g_ScenarioState.step     = 0xA;
    }
}
