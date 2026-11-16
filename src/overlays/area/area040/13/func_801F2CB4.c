#include "area040_13.h"

MATCH void func_801F2CB4(void) {
    u8* flags;

    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_ARMED()) {
        g_SceneState.step_05 = 0x1E;
    } else {
        g_SceneState.step_05 = 0x1C;
    }
    SYS_SetFlag(g_SceneFlags, 5);
    flags = &g_SceneState.flags_01;
    g_GameFlags &= 0xFF77;
    *flags &= ~SCENE_STATE_SCRIPT_ACTIVE;
}
