/* Counts the effect timer (work byte 0x09) down; at zero it advances the effect
 * step (work byte 0x02). One definition shared by the bmagic effect modules;
 * every change here must verify every member. */
/* Effect_CountDownTimerStep (magic088, magic096, magic110, magic113, magic130), Effect_CountDownTimerStep_801EF42C (magic130) */
/* The statements of Effect_CountDownTimerStep; each member declares timer. */
#define BMAGIC_COUNT_DOWN_TIMER_STEP()                             \
    timer                       = g_Task->word_08.byte.unk_09 - 1; \
    g_Task->word_08.byte.unk_09 = timer;                           \
    if (timer == 0) {                                              \
        g_Task->step = g_Task->step + 1;                           \
    }

MATCH void Effect_CountDownTimerStep(void) {
    u8 timer;

    BMAGIC_COUNT_DOWN_TIMER_STEP();
}
