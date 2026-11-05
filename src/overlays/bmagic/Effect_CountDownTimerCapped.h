/* Raises the effect timer (work byte 0x09) by one up to 0x2E, counts the effect
 * counter (0x0A) down, and finishes the effect at zero like Effect_CountDownTimer.
 * One definition shared by the bmagic effect modules; every change here must
 * verify every member. */
/* Effect_CountDownTimerCapped (magic056, magic103) */
MATCH void Effect_CountDownTimerCapped(void) {
    PartyBattler* first;
    PartyBattler* work;
    PartyBattler* active;
    u8            timer;
    u8            count;

    first = g_Task;
    timer = first->unk_09;
    if (timer != 0x2E) {
        first->unk_09 = timer + 1;
    }
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->unk_0B--;
        func_801E5988();
    }
}
