/* Reloads the effect timer and advances the effect step while the effect ticker
 * is under 5. One definition shared by the two bmagic effect modules; every
 * change here must verify every member. */
/* func_801EF4D0 (magic074), func_801EF4E4 (magic073), func_801EF640 (magic169) */
MATCH void Effect_NextStepUnderTickLimit(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B < 5) {
        work->word_08.byte.unk_09 = 8;
        work                      = g_SpadWork;
        work->unk_02              = work->unk_02 + 1;
    }
}
