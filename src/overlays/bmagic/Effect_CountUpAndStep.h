/* Counts the effect timer (work byte 0x09) up; at 0x10 it advances the effect
 * step (work byte 0x02). One definition shared by the bmagic effect modules;
 * every change here must verify every member. */
/* Effect_CountUpAndStep (magic062, magic067, magic079, magic082, magic086, magic088, magic111, magic137, magic167, magic223, magic225), Effect_CountUpAndStep_801EFF08 (magic079) */
/* The statements of Effect_CountUpAndStep; each member declares timer. */
#define BMAGIC_COUNT_UP_AND_STEP()                                         \
    timer                           = g_SpadWork->word_08.byte.unk_09 + 1; \
    g_SpadWork->word_08.byte.unk_09 = timer;                               \
    if (timer == 16) {                                                     \
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;                       \
    }

MATCH void Effect_CountUpAndStep(void) {
    u8 timer;

    BMAGIC_COUNT_UP_AND_STEP();
}
