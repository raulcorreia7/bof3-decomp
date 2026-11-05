#include "area078_13.h"

MATCH void func_801F2C04(void) {
    s32 bit;

    MESSAGE_REQUEST_CLEAR();
    switch (D_801490C7) {
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
