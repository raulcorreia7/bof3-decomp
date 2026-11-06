#include "area191_13.h"

MATCH void func_801F3054(void) {
    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 == 1) {
        Game_SetScriptActive();
        g_SaveData.scene_event.mode = 0x35;
        g_SaveData.scene_event.step = 0x1E;
    } else if (D_801490C7 == 2) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 1;
        g_SceneState.step_05  = 0x14;
    }
}
