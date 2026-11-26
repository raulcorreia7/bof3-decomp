#include "area172_13.h"

MATCH void func_801F4B3C(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        if (SYS_TestFlag(&g_SceneFlagWords[14 * 8], 18)) {
            g_SceneEventState.mode = 0x23;
            g_SceneEventState.step = 5;
        } else {
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step     = 0;
        }
    }
}
