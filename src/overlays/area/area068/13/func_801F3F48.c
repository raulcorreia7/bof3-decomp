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
    record1->unk_01 = request;
    record2         = g_ScriptWorkRecord;
    record2->unk_77 = 5;
    record          = g_ScriptWorkRecord;
    base            = (s32)g_Actors;
    /* FAKE: use keeps the g_Actors row materialized; retail fills the
     * third reload's delay slot with it here. */
    MATCH_FAKE_USE(base);
    do {
        record->unk_7E = 0;
        record         = (Actor*)((s32)record - base);
        step           = ((s32)(-(((s32)record) * 0xD79435E5))) >> 3;
        D_80146867     = (s8)step;
        /* FAKE: barrier keeps the D_801448EB/D_801448ED stores in statement
         * order after the row store. */
        MATCH_FAKE_BARRIER();
    } while (0);
    step       = 3;
    D_801448EB = request;
    /* FAKE: barrier keeps the D_801448ED store after the D_801448EB store. */
    MATCH_FAKE_BARRIER();
    D_801448ED = step;
    return 0;
}
#else
/* Same request-handler family as emi/world01/area059/13 func_801F2F34
 * (unk_77 = 5, D_801448ED = 3 differ) and shares its 38/39 draft shape;
 * the first shift-add multiply temp colors v0 instead of a0. This image
 * also wants the g_Actors address in the third reload's delay slot
 * (0x801F3F80); every tried form (barrier before/after the reload,
 * base assignment after it) schedules it one instruction earlier at
 * 0x801F3F78, ahead of the third reload. First differing instruction
 * 0x801F3F78. */
INCLUDE_ASM(func_801F3F48);
#endif
