/* Advances the step byte (work byte 0x01) when the effect ticker (work byte
 * 0x0B) is zero. One definition shared by the bmagic effect modules; every
 * change here must verify every member. */
/* func_801EEDB0 (magic145), func_801EEFD0 (magic146) */
MATCH void Effect_NextStepOnZeroTick(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B == 0) {
        work->step_01++;
    }
}
