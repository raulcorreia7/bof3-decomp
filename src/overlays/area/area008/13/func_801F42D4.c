#include "area008_13.h"

MATCH void func_801F42D4(void) {
    s8 state;

    state            = g_MessageChoice;
    g_MessageRequest = D_801F53F0[state];
    switch (state) {
        case 0:
            g_ScriptVars[0] = 1;
            break;
        case 1:
            g_ScriptVars[0] = 0;
            break;
        default:
            return;
    }
}
