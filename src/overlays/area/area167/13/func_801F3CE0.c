#include "area167_13.h"

MATCH void func_801F3CE0(void) {
    s8 variant;

    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice != 2) {
        variant = 2;
        if (g_UIMessageChoice == 0) {
            variant = 1;
        }
        g_ScriptVars[2] = variant;
        Game_SetScriptActive();
        g_ScriptVars[3]        = 0x40;
        g_SceneEventState.mode = 0x20;
        g_SceneEventState.step = 0x15;
    }
}
