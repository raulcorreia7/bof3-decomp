#include "area068_13.h"

MATCH void func_801F386C(void) {
    s32 sel;
    u8  value;

    sel              = g_MessageChoice;
    g_MessageRequest = D_801F4D68[sel];
    switch (sel) {
        case 0:
            g_ScriptVars[0] = 0;
            break;
        case 1:
            value           = 0xFF;
            g_ScriptVars[0] = value;
            break;
        default:
            break;
    }
}
