/* Counts the wait down and finishes the effect at zero. Every change here must verify every member. */
/* func_801EF3E0 (magic096), func_801EF478 (magic130) */
MATCH void Effect_CountDownAndFinish(void) {
    PartyBattler* work;

    work                        = g_SpadWork;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A - 1;
    if (work->word_08.byte.timer_0A == 0) {
        work                      = BATTLE_ACTIVE_WORK;
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
        func_801E5988();
    }
}
