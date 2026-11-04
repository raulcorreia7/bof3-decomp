/* Counts the effect counter (work byte 0x0A) down; at zero it advances the
 * effect step (work byte 0x02). One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* Effect_CountDownAndStep (magic062, magic067, magic076, magic078, magic082, magic111, magic131, magic137, magic222), Effect_CountDownAndStep_801F0C98 (magic131) */
/* The statements of Effect_CountDownAndStep; each member declares count. */
#define BMAGIC_COUNT_DOWN_AND_STEP()                                           \
    count                             = g_SpadWork->word_08.byte.timer_0A - 1; \
    g_SpadWork->word_08.byte.timer_0A = count;                                 \
    if (count == 0) {                                                          \
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;                           \
    }

MATCH void Effect_CountDownAndStep(void) {
    u8 count;

    BMAGIC_COUNT_DOWN_AND_STEP();
}
