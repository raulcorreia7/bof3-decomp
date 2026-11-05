#include "area175_13.h"

MATCH void func_801F38E8(void) {
    if (D_801490C7 == 1) {
        g_MessageRequest                   = 0x5A;
        g_ScriptWorkRecord->callback_index = 0xFF;
    } else {
        MESSAGE_REQUEST_CLEAR();
    }
}
