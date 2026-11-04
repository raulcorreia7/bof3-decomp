#include "area143_13.h"

MATCH void func_801F3988(void) {
    s32 message;

    if (D_801490C7 != 0) {
        message = 0x54;
    } else if (D_80145548 != 0x3FFFF) {
        message = 0x53;
    } else {
        g_MessageRequest = 0x52;
        return;
    }
    g_MessageRequest = message;
    g_MasterStep     = 6;
}
