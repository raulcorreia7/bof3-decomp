#include "area037_13.h"

MATCH void func_801F3854(void) {
    s8 choice = g_UIMessageChoice;

    if (choice == 0) {
        Game_SetScriptActive();
        g_SceneEventState.mode = AREA_ORIGIN_OFFSET;
        MESSAGE_REQUEST_CLEAR();
    } else if (choice == 1) {
        MESSAGE_REQUEST_CLEAR();
        g_ScriptVars[3] = 0x64;
    } else if (choice == 2) {
        MESSAGE_REQUEST_CLEAR();
        g_ScriptVars[3] = 0x5F;
    }
}
