#include "area059_13.h"

MATCH s32 func_801F2F34(void) {
    /* CLEANUP: the shift-and-subtract run is GCC's exact division of the pointer difference, so
     * the readable form is D_80146867 = g_ScriptWorkRecord - g_Actors. That form compiles the
     * same multiply, but its stores and registers still differ (tried plain, a shared mode local
     * and barriers). */
    /* FAKE: the product needs the retail temporary registers. */
    FAKE_REG(s32, step, "v1");
    FAKE_REG(s32, part, "a0");
    /* FAKE: pin carries the request code in a2 from the first store to the
     * g_SceneEventMode store. */
    FAKE_REG(s32, request, "a2");
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
    FAKE_ORDER_LOCK_BEGIN
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
        FAKE_BARRIER();
    FAKE_ORDER_LOCK_END;
    step             = 5;
    g_SceneEventMode = request;
    /* FAKE: barrier keeps the g_SceneEventSelection store after the g_SceneEventMode store. */
    FAKE_BARRIER();
    g_SceneEventSelection = step;
    return 0;
}
