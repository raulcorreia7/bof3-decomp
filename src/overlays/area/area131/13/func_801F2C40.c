#include "area131_13.h"

MATCH void func_801F2C40(void) {
    if (g_UIMessageChoice == 0) {
        Game_SetScriptActive();
        g_ScenarioState.state_04                = 7;
        g_ScenarioState.step                    = 10;
        g_ScriptVars[0]                         = 0;
        ((u8*)g_ScriptWorkRecord)[1]            = 4;
        ((u8*)g_ScriptWorkRecord)[0x78]         = 2;
        ((u8*)g_ScriptWorkRecord)[0x77]         = 4;
        *(u16*)((u8*)g_ScriptWorkRecord + 0x7E) = 0;
        g_UIMessageRequest                      = MSG_AREA131_ASK_DESTINATION;
    } else {
        g_UIMessageRequest = MESSAGE_NONE;
    }
}
