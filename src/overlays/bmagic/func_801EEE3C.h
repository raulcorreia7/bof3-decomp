/* Advances the effect counters and moves to the next step when the first reaches 0x10.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEE3C (magic055), func_801EEE3C (magic091) */
MATCH void func_801EEE3C(void) {
    g_Task->word_08.byte.unk_09 += 1;
    g_Task->word_08.byte.timer_0A += 1;
    if (g_Task->word_08.byte.unk_09 == 0x10) {
        g_Task->mode = g_Task->mode + 1;
    }
}
