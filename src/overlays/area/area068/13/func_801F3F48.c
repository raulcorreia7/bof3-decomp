#include "area068_13.h"

MATCH s32 func_801F3F48(void) {
    /* CLEANUP: replace the expanded product with (-(s32)record * 0xD79435E5) >> 3. */
    /* FAKE: the product needs the retail temporary registers. */
    MATCH_FAKE_PIN(s32, step, "v1");
    MATCH_FAKE_PIN(s32, part, "a0");
    /* FAKE: pin carries the request code in a2 from the first store to the
     * g_SceneEventMode store. */
    MATCH_FAKE_PIN(s32, request, "a2");
    Actor* record1;
    Actor* record2;
    /* FAKE: pin carries the record row in a1 so the difference recycles
     * into it (subu a1,a1,v1). */
    MATCH_FAKE_PIN(Actor*, record, "a1");
    /* FAKE: pin carries the g_Actors row in v1; unpinned the address
     * materialization sinks and the schedule breaks. */
    MATCH_FAKE_PIN(s32, base, "v1");

    Game_SetScriptActive();
    record1              = g_ScriptWorkRecord;
    request              = 4;
    record1->header.mode = request;
    record2              = g_ScriptWorkRecord;
    record2->unk_77      = 5;
    record               = g_ScriptWorkRecord;
    base                 = (s32)g_Actors;
    ORDER_LOCK_BEGIN
        record->unk_7E = 0;
        record         = (Actor*)((s32)record - base);
        part           = ((s32)record << 3) - (s32)record;
        part           = (part << 2) - (s32)record;
        step           = (part << 9) - part;
        part           = step << 18;
        step           = -(step + part);
        step >>= 3;
        D_80146867 = (s8)step;
        /* FAKE: barrier keeps the g_SceneEventMode/g_SceneEventSelection stores in statement
         * order after the row store. */
        MATCH_FAKE_BARRIER();
    ORDER_LOCK_END;
    step             = 3;
    g_SceneEventMode = request;
    /* FAKE: barrier keeps the g_SceneEventSelection store after the g_SceneEventMode store. */
    MATCH_FAKE_BARRIER();
    g_SceneEventSelection = step;
    return 0;
}
