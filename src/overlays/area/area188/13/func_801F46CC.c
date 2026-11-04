#include "area188_13.h"

MATCH void func_801F46CC(void) {
    u8 var_v0;

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
            var_v0 = 5;
            goto block_7;
        }
    } else {
        Game_SetScriptActive();
        var_v0 = 0xA;
    block_7:
        *g_ScriptVars = var_v0;
    }
}
