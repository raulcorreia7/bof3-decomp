/* Counts the timer and the wait up; advances the step when the wait reaches 16. */
/* func_801EF114 (magic040), func_801EFC28 (magic126) */
MATCH void Effect_CountUpTimersAndStep(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    work->unk_09++;
    work = TASK(PartyMember);
    work->timer++;
    if (work->timer == 16) {
        work = TASK(PartyMember);
        work->header.step++;
    }
}
