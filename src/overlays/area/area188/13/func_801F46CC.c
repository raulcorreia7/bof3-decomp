#include "area188_13.h"

MATCH void func_801F46CC(void) {
    g_MessageRequest = 0xFFFF;
    if (g_SceneState.scenario_id >= 0xD) {
        if (D_801490C7 == 0) {
            D_801448EB = 0xA;
            D_801448EC = 0;
            D_801448ED = 0xFF;
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
