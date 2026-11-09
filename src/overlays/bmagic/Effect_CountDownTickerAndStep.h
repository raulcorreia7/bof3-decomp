/* Counts the ticker down and advances the step at zero. */
/* func_801EF8A0 (magic086), func_801EF348 (magic096) */
MATCH void Effect_CountDownTickerAndStep(void) {
    u8 timer;

    timer                = g_Task->param.unk_0B - 1;
    g_Task->param.unk_0B = timer;
    if (timer == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}
