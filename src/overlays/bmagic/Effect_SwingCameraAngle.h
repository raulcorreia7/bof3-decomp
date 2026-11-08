/* Swings the area camera's pitch by 20 each tick, up on odd timer values and down on even ones. When the timer
 * reaches zero the pitch returns to its rest angle of -60 degrees, the timer reloads with `settle_ticks` and the
 * effect advances a step. Shared by the bmagic effect modules, each passing its own tick count.
 * A statement macro, not a static inline: GCC 2.95 inlines the helper after it has lost the shared
 * g_AreaCameraAngle address of the two branches, which makes the function two instructions longer. */
#define BMAGIC_SWING_CAMERA(settle_ticks)          \
    do {                                           \
        if ((g_Task->unk_09 & 1) != 0) {           \
            g_AreaCameraAngle.vx += 20;            \
        } else {                                   \
            g_AreaCameraAngle.vx -= 20;            \
        }                                          \
        if (--g_Task->unk_09 == 0) {               \
            g_AreaCameraAngle.vx = -DEG(60);       \
            g_Task->unk_09       = (settle_ticks); \
            g_Task->header.step++;                 \
        }                                          \
    } while (0)
