#include "area143_13.h"

MATCH void func_801F3988(void) {
    s32 message;

    if (g_MessageChoice != 0) {
        message = 0x54;
    } else if (D_80145548 != 0x3FFFF) {
        message = 0x53;
    } else {
        g_MessageRequest = MSG_AREA143_MASTER_TEACH_READY;
        return;
    }
    g_MessageRequest = message;
    g_MenuMasterStep = 6;
}
