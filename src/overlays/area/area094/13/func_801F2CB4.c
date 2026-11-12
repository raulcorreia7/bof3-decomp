#include "area094_13.h"

MATCH void func_801F2CB4(void) {
    u8 value;

    g_MessageRequest = D_801F5358[g_MessageChoice];
    switch (g_MessageChoice) {
        case 0:
            break;

        case 1:
            if (!SYS_TestFlag(g_SceneFlags, 22)) {
                SYS_SetFlag(g_SceneFlags, 22);
                Game_SetScriptActive();
                g_ScriptVars[0]      = 0;
                g_ScriptVars[1]      = 0;
                g_ScriptVars[2]      = 0;
                g_ScriptVars[3]      = 0;
                g_SceneState.step_05 = 0;
                value                = 7;
                goto value_store;
            }
            if (!SYS_TestFlag(g_SceneFlags, 26)) {
                Game_SetScriptActive();
                value = 0x19;
            } else {
                Game_SetScriptActive();
                value = 0x32;
            }
            g_SceneState.step_05 = value;
            value                = 7;
            g_ScriptVars[0]      = 0;
            g_ScriptVars[1]      = 0;
            g_ScriptVars[2]      = 0;
            g_ScriptVars[3]      = 0;
        value_store:
            g_SceneState.state_04 = value;
            break;
    }
}
