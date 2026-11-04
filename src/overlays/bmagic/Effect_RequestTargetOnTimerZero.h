/* Counts the effect timer (work byte 0x09) down; at zero it requests the target
 * selector for the effect with func_800A9610 and advances the step (work byte
 * 0x01). One definition shared by the bmagic effect modules; every change here
 * must verify every member. */
/* func_801EEF9C (magic053), func_801EEF88 (magic124), func_801EEEB8 (magic129), func_801EEE0C (magic130), func_801EF03C (magic132), func_801EEEB0 (magic220), func_801EEF4C (magic223), func_801EEF3C (magic226) */
MATCH void Effect_RequestTargetOnTimerZero(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_800A9610(g_BattleTargetSelector, 0x10);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}
