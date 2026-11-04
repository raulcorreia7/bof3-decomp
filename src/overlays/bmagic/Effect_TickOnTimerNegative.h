/* Counts the effect timer (work byte 0x09) down by two; once the byte reads
 * negative as a signed value it ticks the effect ticker (work byte 0x0B) of the
 * battler D_801EB4E0 and runs the effect step. One definition shared by the
 * bmagic effect modules; every change here must verify every member. */
/* func_801F0650 (magic126), func_801EF770 (magic172) */
MATCH void Effect_TickOnTimerNegative(void) {
    PartyBattler* work;
    s8            timer;

    work         = g_SpadWork;
    timer        = work->unk_09 - 2;
    work->unk_09 = timer;
    if (timer < 0) {
        work         = D_801EB4E0;
        work->unk_0B = work->unk_0B - 1;
        func_801E5988();
    }
}
