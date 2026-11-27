#include "area167_13.h"

MATCH void func_801F3D54(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice != 2) {
        if (g_UIMessageChoice == 0) {
            g_ScriptVars[2] = 0;
        } else {
            g_ScriptVars[2] = 2;
        }
        Game_SetScriptActive();
        g_ScriptVars[3]        = 0x40;
        g_SceneEventState.mode = 0x20;
        g_SceneEventState.step = 0x14;
    }
}
