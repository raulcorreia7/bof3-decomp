/* Clears the effect timer (work byte 0x09), loads the effect counter (0x0A)
 * with 0x88 and advances the step byte through Bmagic_NextStep. One definition
 * shared by the bmagic effect modules; every change here must verify every
 * member. */
/* func_801EFF8C (magic067), func_801EFCC0 (magic137), func_801EF0B8 (magic223) */
MATCH void Effect_ArmCounterNextStep(void) {
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0x88;
    Bmagic_NextStep();
}
