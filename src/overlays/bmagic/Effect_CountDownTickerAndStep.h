/* Counts the ticker down and advances the step at zero. Every change here must verify every member. */
/* func_801EF8A0 (magic086), func_801EF348 (magic096) */
MATCH void Effect_CountDownTickerAndStep(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_0B - 1;
    g_SpadWork->word_08.byte.unk_0B = timer;
    if (timer == 0) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
