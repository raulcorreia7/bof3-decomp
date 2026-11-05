#include "area000_13.h"

MATCH void func_801F2C04(void) {
    s8  sel;
    s32 value;

    MESSAGE_REQUEST_CLEAR();
    sel = D_801490C7;
    switch (sel) {
        case 0:
            value = 0x14;
            break;
        case 1:
            value = 0x19;
            break;
        default:
            return;
    }
    g_ScriptVars[0] = value;
    g_ScriptVars[3] = value;
}
