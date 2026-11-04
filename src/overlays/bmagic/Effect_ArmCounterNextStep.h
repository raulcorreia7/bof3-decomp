/* Starts a 0x88-frame wait and advances the step. Every change here must verify every member. */
/* func_801EFF8C (magic067), func_801EFCC0 (magic137), func_801EF0B8 (magic223) */
MATCH void Effect_ArmCounterNextStep(void) {
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0x88;
    Bmagic_NextStep();
}
