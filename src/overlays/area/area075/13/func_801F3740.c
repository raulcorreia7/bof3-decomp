#include "area075_13.h"

MATCH void func_801F3740(void) {
    s8 sel;

    sel = g_UIMessageChoice;
    if (sel == 0) {
        g_UIMessageRequest     = MSG_AREA075_FOREMAN_START_TEST;
        g_SceneEventState.step = 0x14;
        g_ScriptVars[0]        = 0x15;
    } else {
        g_UIMessageRequest = MSG_AREA075_FOREMAN_ASK_REPEAT;
    }
}
