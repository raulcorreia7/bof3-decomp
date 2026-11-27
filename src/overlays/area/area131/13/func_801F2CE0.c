#include "area131_13.h"

MATCH void func_801F2CE0(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice == 0) {
        Game_SetScriptActive();
        g_ScenarioState.state_04        = 7;
        g_ScriptVars[0]                 = 0;
        g_ScenarioState.step            = 0;
        g_ScriptWorkRecord->header.mode = 4;
        g_ScriptWorkRecord->unk_78      = 2;
        g_ScriptWorkRecord->unk_77      = 2;
        g_ScriptWorkRecord->unk_7E      = 0;
    }
}
