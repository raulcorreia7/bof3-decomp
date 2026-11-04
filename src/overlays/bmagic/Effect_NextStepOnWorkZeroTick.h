/* Advances the step when the work record's ticker is zero. Every change here must verify every member. */
/* func_801EF068 (magic009), func_801EEEA8 (magic039) */
MATCH void Effect_NextStepOnWorkZeroTick(void) {
    PartyBattler* work;

    work = SP_REF(PartyBattler*, 0x44u);
    if (work->word_08.byte.unk_0B == 0) {
        work->step_01 = work->step_01 + 1;
    }
}
