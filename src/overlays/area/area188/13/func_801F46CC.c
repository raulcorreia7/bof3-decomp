#include "area188_13.h"

MATCH void func_801F46CC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_SceneState.scenario_id >= 0xD) {
        if (D_801490C7 == 0) {
            g_SceneEventMode      = SCENE_EVENT_SHOP_SAVE;
            g_SceneEventStep      = 0;
            g_SceneEventSelection = 0xFF;
        }
    } else if (D_801490C7 != 0) {
        if (D_801490C7 == 1) {
            Game_SetScriptActive();
            *g_ScriptVars = 5;
        }
    } else {
        Game_SetScriptActive();
        *g_ScriptVars = 0xA;
    }
}
