#include "area128_13.h"
#include "scenario/state.h"

MATCH void func_801F2F84(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 0) {
        g_ScriptWorkRecord->unk_7E = 11;
        g_ScriptVars[0]            = 15;
        /* FAKE: keep the shared step store after the script update. */
        FAKE_BARRIER();
        g_SceneState.step_05 = 3;
    } else {
        g_SceneState.step_05 = 8;
    }
}
