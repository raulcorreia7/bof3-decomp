#include "area037_13.h"

MATCH void func_801F37F4(void) {
    s8 sel;

    sel = g_UIMessageChoice;
    if (sel == 0) {
        MESSAGE_REQUEST_CLEAR();
        g_ScriptVars[3] = 0x64;
        Scene_SetupParty(3);
    } else {
        g_UIMessageRequest = MSG_AREA037_GAME_DECLINED_COME_BACK;
        g_ScriptVars[3]    = 0;
    }
}
