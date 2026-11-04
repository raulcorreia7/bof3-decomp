/* Counts the timer and the wait up by two; advances the step at timer 0x10. Every change here must verify every member. */
/* func_801EF2D4 (magic009), func_801EF034 (magic145), func_801EF520 (magic146) */
MATCH void Effect_CountUpTimersByTwoNextStep(void) {
    g_SpadWork->word_08.byte.unk_09 += 2;
    g_SpadWork->word_08.byte.timer_0A += 2;
    if (g_SpadWork->word_08.byte.unk_09 == 0x10) {
        Bmagic_NextStep();
    }
}
