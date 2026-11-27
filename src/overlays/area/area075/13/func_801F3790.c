#include "area075_13.h"

MATCH void func_801F3790(void) {
    s8 sel;

    sel = g_UIMessageChoice;
    if (sel == 0) {
        MESSAGE_REQUEST_CLEAR();
        g_SceneEventState.step = 0xF;
        D_801448EE             = 0x1E;
        g_ScriptVars[0]        = 0x14;
    } else {
        g_UIMessageRequest = MSG_AREA075_FOREMAN_ASK_READY;
    }
}
