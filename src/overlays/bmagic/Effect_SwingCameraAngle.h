/* Swings the area camera's pitch by 20 each tick, up on odd timer values and
 * down on even ones; when the timer reaches zero it resets the pitch to -0x2AA,
 * reloads the timer with `ticks` and advances the effect step.
 * One definition shared by the bmagic effect modules; each member passes its
 * function name and tick count. Every change here must verify every member. */
#define BMAGIC_SWING_CAMERA_ANGLE(name, ticks) \
    MATCH void name(void) {                    \
        if ((g_Task->unk_09 & 1) != 0) {       \
            g_AreaCameraAngle.vx += 20;        \
        } else {                               \
            g_AreaCameraAngle.vx -= 20;        \
        }                                      \
        if (--g_Task->unk_09 == 0) {           \
            g_AreaCameraAngle.vx = -0x2AA;     \
            g_Task->unk_09       = (ticks);    \
            g_Task->header.step++;             \
        }                                      \
    }
