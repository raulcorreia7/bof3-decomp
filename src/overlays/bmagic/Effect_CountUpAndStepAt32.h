/* Counts the effect timer (work byte 0x09) up; at 32 it advances the effect
 * step (work byte 0x02); Effect_CountUpAndStep stops at 16. One definition
 * shared by the bmagic effect modules; every change here must verify every
 * member. */
/* func_801EF180 (magic040), func_801EF9DC (magic088) */
MATCH void Effect_CountUpAndStepAt32(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 32) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
