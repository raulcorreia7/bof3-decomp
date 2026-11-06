/* Counts the effect timer (work byte 0x09) down; at zero it advances the effect
 * step (work byte 0x02). One definition shared by the bmagic effect modules;
 * every change here must verify every member. */
/* Effect_CountDownTimerStep (magic088, magic096, magic110, magic113, magic130), Effect_CountDownTimerStep_801EF42C (magic130) */
/* The statements of Effect_CountDownTimerStep. */
#define BMAGIC_COUNT_DOWN_TIMER_STEP()                     \
    do {                                                   \
        u8 timer;                                          \
                                                           \
        timer          = g_Task->unk_09 - 1;               \
        g_Task->unk_09 = timer;                            \
        if (timer == 0) {                                  \
            g_Task->header.step = g_Task->header.step + 1; \
        }                                                  \
    } while (0)

MATCH void Effect_CountDownTimerStep(void) {
    BMAGIC_COUNT_DOWN_TIMER_STEP();
}
