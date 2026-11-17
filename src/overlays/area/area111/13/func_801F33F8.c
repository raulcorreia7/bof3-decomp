#include "area111_13.h"

MATCH void func_801F33F8(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 5;
        g_ScenarioState.step_05  = 0;
    }
}
