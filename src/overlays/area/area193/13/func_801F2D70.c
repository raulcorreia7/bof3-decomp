#include "area193_13.h"

MATCH void func_801F2D70(void) {
    Actor* record;

    record = g_ScriptWorkRecord;
    MESSAGE_REQUEST_CLEAR();
    record->unk_18 = D_801F3A18[g_UIMessageChoice * 2];
    /* FAKE: retail reloads the selection byte after the 0x18 store; the
     * compiler keeps the first load without a barrier (pure-C best 0x48/0x58). */
    FAKE_BARRIER();
    record->unk_1C = D_801F3A19[g_UIMessageChoice * 2];
}
