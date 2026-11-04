/* Lowers the effect ticker (work byte 0x0B) and counts the effect timer (work
 * byte 0x09) up; at 24 it calls func_800A9610 with the target selector and
 * 0x10 and advances the effect step (work byte 0x02). One definition shared by
 * the bmagic effect modules; every change here must verify every member. */
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
