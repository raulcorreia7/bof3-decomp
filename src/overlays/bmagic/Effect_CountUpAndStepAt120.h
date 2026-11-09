/* Counts the timer up and advances the step at 120. */
/* func_801EF374 (magic120), func_801EF24C (magic122) */
MATCH void Effect_CountUpAndStepAt120(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 120) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}
