#include "area172_13.h"

MATCH void func_801F4B3C(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        if (SYS_TestFlag(D_80144EF8, 18)) {
            g_SceneEventMode = 0x23;
            g_SceneEventStep = 5;
        } else {
            g_SceneState.state_04 = 6;
            g_SceneState.step_05  = 0;
        }
    }
}
