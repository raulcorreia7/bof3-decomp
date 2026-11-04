/* Advances the step when the ticker is zero. Every change here must verify every member. */
/* func_801EF528 (magic083), func_801F00B4 (magic151) */
MATCH void Effect_StepOnZeroTick(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B == 0) {
        work->unk_02++;
    }
}
