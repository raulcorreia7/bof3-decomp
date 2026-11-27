#include "area128_13.h"

MATCH void func_801F2F84(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice == 0) {
        g_ScriptWorkRecord->unk_7E = 11;
        g_ScriptVars[0]            = 15;
        g_ScenarioState.step       = 3;
    } else {
        g_ScenarioState.step = 8;
    }
}
