#include "area143_13.h"

MATCH void func_801F3AF4(void) {
    Actor* work;

    if (g_MessageChoice == 0) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 8;
        if (g_MessageRequest == 0x44) {
            work                 = g_ScriptWorkRecord;
            g_SceneState.step_05 = 8;
            g_MessageRequest     = MSG_075;
            /* FAKE: retail keeps the count load after the request store. */
            FAKE_BARRIER();
            work->unk_7E++;
        } else {
            g_SceneState.step_05 = 0xA;
            g_MessageRequest     = MESSAGE_NONE;
        }
    } else {
        g_MessageRequest = MSG_076;
    }
}
