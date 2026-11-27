#include "area188_13.h"

MATCH void func_801F46CC(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_ScenarioState.scenario_id >= 0xD) {
        if (g_UIMessageChoice == 0) {
            g_SceneEventState.mode      = SCENE_EVENT_INN;
            g_SceneEventState.step      = 0;
            g_SceneEventState.selection = 0xFF;
        }
    } else if (g_UIMessageChoice != 0) {
        if (g_UIMessageChoice == 1) {
            Game_SetScriptActive();
            *g_ScriptVars = 5;
        }
    } else {
        Game_SetScriptActive();
        *g_ScriptVars = 0xA;
    }
}
