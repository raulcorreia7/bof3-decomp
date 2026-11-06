#include "area068_13.h"

MATCH void func_801F381C(void) {
    s8 state;

    state            = g_MessageChoice;
    g_MessageRequest = D_801F4D64[state];
    switch (state) {
        case 0:
            g_ScriptVars[0] = 0x14;
            break;
        case 1:
            g_ScriptVars[0] = 3;
            break;
        default:
            return;
    }
}
