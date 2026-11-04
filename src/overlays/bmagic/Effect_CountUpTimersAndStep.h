/* Counts the timer and the wait up; advances the step when the wait reaches 16. Every change here must verify every member. */
/* func_801EF114 (magic040), func_801EFC28 (magic126) */
MATCH void Effect_CountUpTimersAndStep(void) {
    PartyBattler* work;

    work = g_SpadWork;
    work->word_08.byte.unk_09++;
    work = g_SpadWork;
    work->word_08.byte.timer_0A++;
    if (work->word_08.byte.timer_0A == 16) {
        work = g_SpadWork;
        work->unk_02++;
    }
}
