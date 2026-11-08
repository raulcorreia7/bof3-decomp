#include "area068_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3F48(void) {
    s32 step;
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
    record2->unk_77      = 5;
    record               = g_ScriptWorkRecord;
    base                 = (s32)g_Actors;
    FAKE_ORDER_LOCK_BEGIN
        record->unk_7E = 0;
        record         = (Actor*)((s32)record - base);
        step           = ((s32)(-(((s32)record) * 0xD79435E5))) >> 3;
        D_80146867     = (s8)step;
        /* FAKE: barrier keeps the g_SceneEventMode/g_SceneEventSelection stores in statement
         * order after the row store. */
        FAKE_BARRIER();
    FAKE_ORDER_LOCK_END;
    step             = 3;
    g_SceneEventMode = request;
    /* FAKE: barrier keeps the g_SceneEventSelection store after the g_SceneEventMode store. */
    FAKE_BARRIER();
    g_SceneEventSelection = step;
    return 0;
}
#else
/* nonmatching: 8 rows, one register choice. The exact record-index division (x * 0xD79435E5, then >> 3) builds its
 * temporaries in a0/v1 in retail and v0/v1 here (first row 0x801F3F90). FAKE_USE(base) before the third reload
 * was dropped: it cost 4 bytes and moved the first row to 0x801F3F78. */
INCLUDE_ASM(func_801F3F48);
#endif
