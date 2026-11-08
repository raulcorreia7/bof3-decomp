#include "area193_13.h"

MATCH void func_801F2D70(void) {
    u8* record;

    record = (u8*)g_ScriptWorkRecord;
    MESSAGE_REQUEST_CLEAR();
    FIELD(s32, record, 0x18U) = D_801F3A18[g_MessageChoice * 2];
    /* FAKE: retail reloads the selection byte after the 0x18 store; the
     * compiler keeps the first load without a barrier (pure-C best 0x48/0x58). */
    FAKE_BARRIER();
    FIELD(s32, record, 0x1CU) = D_801F3A19[g_MessageChoice * 2];
}
