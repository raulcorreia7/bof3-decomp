#include "area120_13.h"

MATCH void func_801F4350(void) {
    u16* count;

    if (g_MessageChoice == 0) {
        count = &g_ScriptWorkRecord->unk_7E;
        MESSAGE_REQUEST_CLEAR();
        *count += 1;
        D_80146874 = 0xD;
        D_80146875 = 8;
    } else {
        g_MessageRequest = 0x35;
    }
}
