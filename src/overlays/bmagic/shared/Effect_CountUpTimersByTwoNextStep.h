/* Counts the timer and the wait up by two; advances the step at timer 0x10. */
/* func_801EF2D4 (magic009), func_801EF034 (magic145), func_801EF520 (magic146) */
MATCH void Effect_CountUpTimersByTwoNextStep(void) {
    BMAGIC_WORK->unk_09 += 2;
    BMAGIC_WORK->timer += 2;
    if (BMAGIC_WORK->unk_09 == 0x10) {
        BMagic_NextStep();
    }
}
