/* Counts the timer at byte 0x0A up by two and steps the handler when it
 * reaches 16.
 */
/* func_801EF0E8, func_801EF38C */
MATCH void Effect_CountUpTimerByTwoAndStep(void) {
    g_SpadWork->word_08.byte.timer_0A += 2;
    if (g_SpadWork->word_08.byte.timer_0A == 0x10) {
        g_SpadWork->unk_02 += 1;
    }
}
