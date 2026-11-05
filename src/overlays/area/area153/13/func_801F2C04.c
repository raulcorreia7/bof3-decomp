#include "area153_13.h"

MATCH void func_801F2C04(void) {
    u8* record;

    record                    = (u8*)g_ScriptWorkRecord;
    g_MessageRequest          = 0xFFFF;
    FIELD(s32, record, 0x18U) = D_801F3BF8[D_801490C7 * 2];
    /* FAKE: retail reloads the selection after the 0x18 store. */
    MATCH_FAKE_BARRIER();
    FIELD(s32, record, 0x1CU) = D_801F3BF9[D_801490C7 * 2];
}
