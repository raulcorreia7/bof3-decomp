#include "area037_13.h"

MATCH void func_801F37F4(void) {
    s8 sel;

    sel = g_MessageChoice;
    if (sel == 0) {
        MESSAGE_REQUEST_CLEAR();
        g_ScriptVars[3] = 0x64;
        Scene_SetupParty(3);
    } else {
        g_MessageRequest = 0xBD;
        g_ScriptVars[3]  = 0;
    }
}
