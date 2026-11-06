#include "area068_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F3F48(void) {
    s32 step;
    /* FAKE: pin carries the request code in a2 from the first store to the
     * D_801448EB store. */
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
    record1         = g_ScriptWorkRecord;
    request         = 4;
    record1->mode   = request;
    record2         = g_ScriptWorkRecord;
    record2->unk_77 = 5;
    record          = g_ScriptWorkRecord;
    base            = (s32)g_Actors;
    /* FAKE: use keeps the g_Actors row materialized; retail fills the
     * third reload's delay slot with it here. */
    MATCH_FAKE_USE(base);
    ORDER_LOCK_BEGIN
        record->unk_7E = 0;
        record         = (Actor*)((s32)record - base);
        step           = ((s32)(-(((s32)record) * 0xD79435E5))) >> 3;
        D_80146867     = (s8)step;
        /* FAKE: barrier keeps the D_801448EB/D_801448ED stores in statement
         * order after the row store. */
        MATCH_FAKE_BARRIER();
    ORDER_LOCK_END;
    step       = 3;
    D_801448EB = request;
    /* FAKE: barrier keeps the D_801448ED store after the D_801448EB store. */
    MATCH_FAKE_BARRIER();
    D_801448ED = step;
    return 0;
}
#else
/* blocker: g_Actors address load scheduled early; first diff: 0x801F3F78. */
INCLUDE_ASM(func_801F3F48);
#endif
