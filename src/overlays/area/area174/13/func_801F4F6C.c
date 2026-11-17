#include "area174_13.h"

MATCH void func_801F4F6C(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        g_ScenarioState.step_05 = 0x1E;
    } else {
        g_ScenarioState.step_05 = 0xA;
    }
}
