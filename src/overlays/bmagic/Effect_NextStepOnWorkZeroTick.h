/* Advances the step byte (work byte 0x01) when the effect ticker (work byte
 * 0x0B) of the work-area record the scratchpad points to (offset 0x44) is
 * zero. One definition shared by the bmagic effect modules; every change here
 * must verify every member. */
/* func_801EF068 (magic009), func_801EEEA8 (magic039) */
MATCH void Effect_NextStepOnWorkZeroTick(void) {
    PartyBattler* work;

    work = SP_REF(PartyBattler*, 0x44u);
    if (work->word_08.byte.unk_0B == 0) {
        work->step_01 = work->step_01 + 1;
    }
}
