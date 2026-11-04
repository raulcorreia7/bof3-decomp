/* Counts the effect timer (work byte 0x09) and the effect counter (0x0A) up by
 * one; at counter 16 it advances the effect step (work byte 0x02). One
 * definition shared by the bmagic effect modules; every change here must verify
 * every member. */
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
