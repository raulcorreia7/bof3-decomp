/* Counts the timer and the wait up; advances the step when the wait reaches 16. Every change here must verify every
   member. */
/* func_801EF114 (magic040), func_801EFC28 (magic126) */
MATCH void Effect_CountUpTimersAndStep(void) {
    PartyMember* work;

    work = g_Task;
    work->unk_09++;
    work = g_Task;
    work->timer++;
    if (work->timer == 16) {
        work = g_Task;
        work->header.step++;
    }
}
