/* Counts the timer and the wait up by two; advances the step at timer 0x10. Every change here must verify every member.
*/
/* func_801EF2D4 (magic009), func_801EF034 (magic145), func_801EF520 (magic146) */
MATCH void Effect_CountUpTimersByTwoNextStep(void) {
    g_Task->unk_09 += 2;
    g_Task->timer += 2;
    if (g_Task->unk_09 == 0x10) {
        Bmagic_NextStep();
    }
}
