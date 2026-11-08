/* Counts the effect timer down and finishes the effect at zero. One definition
 * shared by the bmagic effect modules; each member passes the
 * timer step.
 * Every change here must verify every member. */
static inline void BMagic_CountDownEffectTimer(u8 step) {
    PartyBattler* work;
    PartyBattler* active;
    u8            count;

    work = g_Task;
    work->unk_09 += step;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}
