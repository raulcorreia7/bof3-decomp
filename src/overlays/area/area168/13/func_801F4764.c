#include "area168_13.h"

MATCH void func_801F4764(void) {
    u8* record;

    MESSAGE_REQUEST_CLEAR();
    if (D_801490C7 == 3) {
        Game_SetScriptActive();
        D_801448EB = 0xA;
        D_801448EC = 0x5;
        D_801448ED = 0xFF;
    }
    record = (u8*)g_ScriptWorkRecord;
    FIELD(s32, record, 0x18U) = D_801F4F94[D_801490C7 * 2];
    /* FAKE: retail reloads the selection byte after the 0x18 store. */
    MATCH_FAKE_BARRIER();
    FIELD(s32, record, 0x1CU) = D_801F4F95[D_801490C7 * 2];
}
