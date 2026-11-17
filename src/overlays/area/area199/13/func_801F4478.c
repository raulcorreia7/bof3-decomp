#include "area199_13.h"

MATCH void func_801F4478(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        g_ScenarioState.step_05 = 0;
    } else {
        g_ScenarioState.step_05 = 1;
    }
}
