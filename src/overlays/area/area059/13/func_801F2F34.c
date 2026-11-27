#include "area059_13.h"

MATCH s32 func_801F2F34(void) {
    /* FAKE: the product needs the retail temporary registers. */
    FAKE_REG(s32, step, "v1");
    FAKE_REG(s32, part, "a0");
    s32    request;
    Actor* record1;
    Actor* record2;
    /* FAKE: pin carries the record row in a1 so the difference recycles
     * into it (subu a1,a1,v1). */
    FAKE_REG(Actor*, record, "a1");
    /* FAKE: pin carries the g_Actors row in v1; unpinned the address
     * materialization sinks and the schedule breaks. */
    FAKE_REG(s32, base, "v1");

    Game_SetScriptActive();
    record1              = g_ScriptWorkRecord;
    request              = 4;
    record1->header.mode = request;
    record2              = g_ScriptWorkRecord;
    base                 = (s32)g_Actors;
    record2->unk_77      = 0;
    /* FAKE: use keeps the g_Actors row materialized before the unk_77
     * store. */
    FAKE_USE(base);
    record = g_ScriptWorkRecord;
    record->unk_7E = 0;
    AREA_STORE_SCRIPT_RECORD_INDEX(record, base, part, step);
    step                        = 5;
    g_SceneEventState.mode      = request;
    g_SceneEventState.selection = step;
    return 0;
}
