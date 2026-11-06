#include "area075_13.h"

MATCH void func_801F3740(void) {
    s8 sel;

    sel = D_801490C7;
    if (sel == 0) {
        g_MessageRequest = 0x19;
        g_SceneEventStep = 0x14;
        g_ScriptVars[0]  = 0x15;
    } else {
        g_MessageRequest = 0x1A;
    }
}
