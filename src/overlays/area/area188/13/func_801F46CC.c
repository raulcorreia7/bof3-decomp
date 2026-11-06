#include "area188_13.h"

MATCH void func_801F46CC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_SceneState.scenario_id >= 0xD) {
        if (g_MessageChoice == 0) {
            g_SceneEventMode      = 0xA;
            g_SceneEventStep      = 0;
            g_SceneEventSelection = 0xFF;
        }
    } else if (g_MessageChoice != 0) {
        if (g_MessageChoice == 1) {
            Game_SetScriptActive();
            *g_ScriptVars = 5;
        }
    } else {
        Game_SetScriptActive();
        *g_ScriptVars = 0xA;
    }
}
