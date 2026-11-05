/* Advances the step when the work record's ticker is one. Every change here must verify every member. */
/* func_801EEFC4 (magic041), func_801EEE8C (magic118) */
MATCH void Effect_NextStepOnWorkLastTick(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->unk_0B == 1) {
        work->mode = work->mode + 1;
    }
}
