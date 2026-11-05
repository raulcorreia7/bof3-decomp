/* Counts the timer up and advances the step at 32. Every change here must verify every member. */
/* func_801EF180 (magic040), func_801EF9DC (magic088) */
MATCH void Effect_CountUpAndStepAt32(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 32) {
        g_Task->step = g_Task->step + 1;
    }
}
