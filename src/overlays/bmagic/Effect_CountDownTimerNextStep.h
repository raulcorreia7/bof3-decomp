/* Counts the effect timer (work byte 0x09) down; at zero it advances the step
 * byte (work byte 0x01) the bmagic dispatcher indexes. One definition shared by
 * the bmagic effect modules; every change here must verify every member. */
/* func_801EF01C (magic009), func_801EEED4 (magic101), func_801EEEC0 (magic118) */
MATCH void Effect_CountDownTimerNextStep(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}
