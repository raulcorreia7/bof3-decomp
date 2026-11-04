/* Advances the step byte (work byte 0x01) while the effect ticker (work byte
 * 0x0B) is under 2. One definition shared by the bmagic effect modules; every
 * change here must verify every member. */
/* func_801EF070 (magic088), func_801EF048 (magic167) */
MATCH void Effect_NextStepWhileTickUnderTwo(void) {
    PartyBattler* work;

    work = g_SpadWork;
    if (work->word_08.byte.unk_0B < 2) {
        work->step_01++;
    }
}
