/* Counts the timer up and advances the step at 30. Every change here must verify every member. */
/* func_801EFBA4 (magic056), func_801F0410 (magic103) */
MATCH void Effect_CountUpAndStepAt30(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 30) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}
