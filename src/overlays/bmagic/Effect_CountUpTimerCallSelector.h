/* Lowers the ticker and counts the timer up; at 24 selects the target (0x10) and advances the step. Every change here must verify every member. */
/* func_801EF2EC (magic120), func_801EF1C4 (magic122) */
MATCH void Effect_CountUpTimerCallSelector(void) {
    PartyBattler* work;
    u8            timer;

    work                      = g_SpadWork;
    work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;
    work                      = g_SpadWork;
    timer                     = work->word_08.byte.unk_09 + 1;
    work->word_08.byte.unk_09 = timer;
    if (timer == 24) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        work         = g_SpadWork;
        work->unk_02 = work->unk_02 + 1;
    }
}
