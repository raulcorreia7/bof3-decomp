/* Counts the effect timer (work byte 0x09) up; at 30 it advances the effect
 * step (work byte 0x02); Effect_CountUpAndStep stops at 16. One definition
 * shared by the bmagic effect modules; every change here must verify every
 * member. */
/* func_801EFBA4 (magic056), func_801F0410 (magic103) */
MATCH void Effect_CountUpAndStepAt30(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 30) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
