#include "area192_13.h"

MATCH void func_801F2DBC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_UiMessageChoice == 1) {
        Scene_StartEvent(0x36, 0x1E);
    } else if (g_UiMessageChoice == 2) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 1;
        g_ScenarioState.step_05  = 0x14;
    }
}
