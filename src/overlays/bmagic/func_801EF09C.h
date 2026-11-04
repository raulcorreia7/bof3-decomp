/* Raises the ticker and timer, lowers the counter by two and advances the step when it reaches 0x10.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EF09C (magic055), func_801EF09C (magic091) */
MATCH void func_801EF09C(void) {
    u8 counter;

    g_SpadWork->word_08.byte.unk_0B += 1;
    g_SpadWork->word_08.byte.timer_0A += 2;
    counter                         = g_SpadWork->word_08.byte.unk_09 - 2;
    g_SpadWork->word_08.byte.unk_09 = counter;
    if ((counter & 0xFF) == 0x10) {
        g_SpadWork->step_01 += 1;
    }
}
