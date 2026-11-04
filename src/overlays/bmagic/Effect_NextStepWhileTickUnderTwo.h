/* Advances the step while the ticker is under 2. Every change here must verify every member. */
/* func_801EEE68 (magic013), func_801EF070 (magic088), func_801EF048 (magic167) */
MATCH void Effect_NextStepWhileTickUnderTwo(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B < 2) {
        work->step_01++;
    }
}
