#include "area068_13.h"

MATCH s32 func_801F3F48(void) {
    /* CLEANUP: the shift-and-subtract run is GCC's exact division of the pointer difference, so
     * the readable form is the actor index g_ScriptWorkRecord - g_Actors (the same as in
     * area059 func_801F2F34). */
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
    record2->unk_77      = 5;
    record               = g_ScriptWorkRecord;
    base                 = (s32)g_Actors;
    record->unk_7E = 0;
    AREA_STORE_SCRIPT_RECORD_INDEX(record, base, part, step);
    step                        = 3;
    g_SceneEventState.mode      = request;
    g_SceneEventState.selection = step;
    return 0;
}
