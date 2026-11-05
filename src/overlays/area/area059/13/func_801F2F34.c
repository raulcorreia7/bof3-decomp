#include "area059_13.h"

#ifdef NON_MATCHING
NON_MATCHING s32 func_801F2F34(void) {
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
    base            = (s32)g_Actors;
    record2->unk_77 = 0;
    /* FAKE: use keeps the g_Actors row materialized before the unk_77
     * store. */
    MATCH_FAKE_USE(base);
    record = g_ScriptWorkRecord;
    do {
        record->unk_7E = 0;
        record         = (Actor*)((s32)record - base);
        step           = ((s32)(-(((s32)record) * 0xD79435E5))) >> 3;
        D_80146867     = (s8)step;
        /* FAKE: barrier keeps the D_801448EB/D_801448ED stores in statement
         * order after the row store. */
        MATCH_FAKE_BARRIER();
    } while (0);
    step       = 5;
    D_801448EB = request;
    /* FAKE: barrier keeps the D_801448ED store after the D_801448EB store. */
    MATCH_FAKE_BARRIER();
    D_801448ED = step;
    return 0;
}
#else
/* Area request handler: Game_SetScriptActive, Actor unk_01/unk_77/unk_7E,
 * the g_Actors row index into D_80146867, then D_801448EB/D_801448ED.
 * Draft is 38/39: the first shift-add multiply temp colors v0 instead of
 * a0 (0x801F2F7C retail `sll a0,a1,3`) and the chain colors follow. Best
 * score 55 (work/permute/nonmatchings/func_801F2F34-3). GCC 2.7.2
 * local-alloc.c closes every other color: the last-use tie gives
 * subu a1,a1,v1, the copy-propagated product copy leaves a fresh temp,
 * and const4 scans to a2 last. The tied {record,row} qty and the first
 * temp must both skip free v0/v1 in the regno scan though no hard reg
 * holds v0 across the chain - that model does not close. Next lever: a
 * shape whose first chain temp takes a0 with v0 free. Then
 * func_801F3F48 (unk_77 = 5, D_801448ED = 3). */
INCLUDE_ASM(func_801F2F34);
#endif
