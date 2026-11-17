#include "area144_13.h"

MATCH void func_801F3D14(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        g_ScriptVars[0] = 5;
        Scene_SetupParty(6);
        g_ScenarioState.state_04 = 7;
        g_ScenarioState.step_05  = 0x14;
    } else {
        Scene_SetupParty(5);
    }
}
