#include "area128_13.h"

MATCH void func_801F2FD8(void) {
    if (g_MessageChoice == 0) {
        Scene_StartEvent(0x38, 0xA);
        g_MessageRequest = AREA128_MSG_START;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
