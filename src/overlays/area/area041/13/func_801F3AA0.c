#include "area041_13.h"

MATCH void func_801F3AA0(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice == 0) {
        Scene_SetupParty(3U);
        g_ScriptVars[1] = 0x1E;
    } else {
        Scene_SetupParty(4U);
        g_ScriptWorkRecord->header.flags = 0;
        g_ScriptVars[1]                  = 0x28;
    }
}
