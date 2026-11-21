#include "area143_13.h"

MATCH void func_801F3AF4(void) {
    Actor* work;

    if (g_UiMessageChoice == 0) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 8;
        if (g_UiMessageRequest == 0x44) {
            work                    = g_ScriptWorkRecord;
            g_ScenarioState.step_05 = 8;
            g_UiMessageRequest      = MSG_AREA143_075;
            /* FAKE: retail keeps the count load after the request store. */
            FAKE_BARRIER();
            work->unk_7E++;
        } else {
            g_ScenarioState.step_05 = 0xA;
            g_UiMessageRequest      = MESSAGE_NONE;
        }
    } else {
        g_UiMessageRequest = MSG_AREA143_076;
    }
}
