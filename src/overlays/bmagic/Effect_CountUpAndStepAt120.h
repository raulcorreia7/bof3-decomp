/* Counts the timer up and advances the step at 120. Every change here must verify every member. */
/* func_801EF374 (magic120), func_801EF24C (magic122) */
MATCH void Effect_CountUpAndStepAt120(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 120) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
