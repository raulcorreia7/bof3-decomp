/* Advances the step when the work record's ticker is one. Every change here must verify every member. */
/* func_801EEFC4 (magic041), func_801EEE8C (magic118) */
MATCH void Effect_NextStepOnWorkLastTick(void) {
    PartyBattler* work;

    work = SP_REF(PartyBattler*, 0x44u);
    if (work->word_08.byte.unk_0B == 1) {
        work->step_01 = work->step_01 + 1;
    }
}
