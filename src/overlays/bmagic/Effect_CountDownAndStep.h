/* Counts the effect counter (work byte 0x0A) down; at zero it advances the
 * effect step (work byte 0x02). One definition shared by the bmagic effect
 * modules; every change here must verify every member. */
/* Effect_CountDownAndStep (magic062, magic067, magic076, magic078, magic082, magic111, magic131, magic137, magic222), Effect_CountDownAndStep_801F0C98 (magic131) */
/* The statements of Effect_CountDownAndStep. */
#define BMAGIC_COUNT_DOWN_AND_STEP()         \
    do {                                     \
        u8 count;                            \
                                             \
        count         = g_Task->timer - 1;   \
        g_Task->timer = count;               \
        if (count == 0) {                    \
            g_Task->step = g_Task->step + 1; \
        }                                    \
    } while (0)

MATCH void Effect_CountDownAndStep(void) {
    BMAGIC_COUNT_DOWN_AND_STEP();
}
