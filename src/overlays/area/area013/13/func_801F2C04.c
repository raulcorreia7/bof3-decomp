#include "area013_13.h"

MATCH s32 func_801F2C04(void) {
    s8 state;

    state            = g_MessageChoice;
    g_MessageRequest = ((u16*)(D_801F2E3C + 0x1508u))[state];
    switch (state) {
        case 0:
            g_ScriptVars[0] = 0x0A;
            break;
        case 1:
            g_ScriptVars[0] = 0x14;
            break;
        default:
            return;
    }
}
