#include "area041_13.h"

MATCH void func_801F3A48(void) {
    s32 sel;
    u8  value;

    sel = D_801490C7;
    MESSAGE_REQUEST_CLEAR();
    if (sel == 0) {
        func_801BE1B0(1);
        value = 0xA;
    } else {
        func_801BE1B0(2);
        value = 0x14;
    }
    g_ScriptVars[1] = value;
}
