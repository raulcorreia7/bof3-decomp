/* Counts the effect timer (work byte 0x09) down; at zero it calls
 * func_800A9610 with the target selector and 0x20 and advances the step byte
 * (work byte 0x01). One definition shared by the bmagic effect modules; every
 * change here must verify every member. */
/* func_801EEF3C (magic067), func_801EEEFC (magic137) */
MATCH void Effect_CountDownTimerCallSelector(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_800A9610(g_BattleTargetSelector, 0x20);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}
