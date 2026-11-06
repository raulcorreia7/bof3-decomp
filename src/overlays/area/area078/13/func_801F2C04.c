#include "area078_13.h"

MATCH s32 func_801F2C04(void) {
    s32 bit;

    MESSAGE_REQUEST_CLEAR();
    switch (g_MessageChoice) {
        case 0:
            bit = 0x16;
            break;
        case 1:
            bit = 0x17;
            break;
        default:
            return;
    }
    g_ScriptVars[0] = 0x1E;
    SYS_SetFlag(g_SceneFlags, bit);
}
