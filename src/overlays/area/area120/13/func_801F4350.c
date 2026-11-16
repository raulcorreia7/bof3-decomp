#include "area120_13.h"

MATCH void func_801F4350(void) {
    u16* count;

    if (g_MessageChoice == 0) {
        count = &g_ScriptWorkRecord->unk_7E;
        MESSAGE_REQUEST_CLEAR();
        *count += 1;
        g_SceneState.state_04 = 0xD;
        g_SceneState.step_05  = 8;
    } else {
        g_MessageRequest = AREA120_MSG_VISITOR_REFUSED;
    }
}
