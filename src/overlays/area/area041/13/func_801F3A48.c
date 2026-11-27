#include "area041_13.h"

MATCH void func_801F3A48(void) {
    s32 sel;
    u8  value;

    sel = g_UIMessageChoice;
    MESSAGE_REQUEST_CLEAR();
    if (sel == 0) {
        Scene_SetupParty(1);
        value = 0xA;
    } else {
        Scene_SetupParty(2);
        value = 0x14;
    }
    g_ScriptVars[1] = value;
}
