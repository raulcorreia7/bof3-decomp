#include "area192_13.h"

MATCH void func_801F2DBC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 1) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x36;
        g_SceneEventStep = 0x1E;
    } else if (g_MessageChoice == 2) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 1;
        g_SceneState.step_05  = 0x14;
    }
}
