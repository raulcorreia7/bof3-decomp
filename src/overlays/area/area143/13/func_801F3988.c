#include "area143_13.h"

MATCH void func_801F3988(void) {
    s32 message;

    if (g_MessageChoice != 0) {
        message = 0x54;
    } else if (D_80145548 != 0x3FFFF) {
        message = 0x53;
    } else {
        g_MessageRequest = AREA143_MSG_POWER_AWAKENED;
        return;
    }
    g_MessageRequest = message;
    g_MenuMasterStep = 6;
}
