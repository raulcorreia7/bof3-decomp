/* Counts the effect timer (work byte 0x09) down; at zero it copies the coordinates
 * and height span of the battler D_801EB4E0 into the effect work, reloads the
 * timer with 0x40, clears the effect counters (work bytes 0x0A, 0x0B) and advances
 * the effect step (work byte 0x01). One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EEFFC (magic055), func_801EEFFC (magic091) */
MATCH void Effect_CopyBattlerCoordsOnTimerZero(void) {
    u8            timer;
    PartyBattler* src;
    PartyBattler* work;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        src                               = BATTLE_ACTIVE_WORK;
        work                              = g_SpadWork;
        work->coord_x_34                  = src->coord_x_34;
        work->coord_y_38                  = src->coord_y_38;
        work->word_3C                     = src->word_3C;
        work->word_08.byte.unk_09         = 0x40;
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->word_08.byte.unk_0B   = 0;
        g_SpadWork->step_01               = g_SpadWork->step_01 + 1;
    }
}
