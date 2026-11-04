/* Counts the effect timer (work byte 0x09) up by two; at 0x10 it advances the
 * effect step (work byte 0x02). One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* func_801EF750 (magic021), func_801EF4D4 (magic041), func_801EF8C4 (magic111), func_801F01A8 (magic131), func_801F061C (magic222) */
MATCH void Effect_CountUpByTwoAndStep(void) {
    u8 timer;

    timer                           = g_SpadWork->word_08.byte.unk_09 + 2;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 16) {
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}
