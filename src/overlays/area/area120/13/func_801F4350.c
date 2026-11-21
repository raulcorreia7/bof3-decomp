#include "area120_13.h"

MATCH void func_801F4350(void) {
    u16* count;

    if (g_UiMessageChoice == 0) {
        count = &g_ScriptWorkRecord->unk_7E;
        MESSAGE_REQUEST_CLEAR();
        *count += 1;
        g_ScenarioState.state_04 = 0xD;
        g_ScenarioState.step_05  = 8;
    } else {
        g_UiMessageRequest = MSG_AREA120_DECLINE_TAKE_TIME;
    }
}
