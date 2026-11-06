#include "area128_13.h"

MATCH void func_801F2FD8(void) {
    if (g_MessageChoice == 0) {
        Game_SetScriptActive();
        D_801448EB       = 0x38;
        D_801448EC       = 0xA;
        g_MessageRequest = 0x49;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
