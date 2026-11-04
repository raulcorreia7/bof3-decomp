/* Swings the area camera's pitch by 20 each tick, up on odd timer values and
 * down on even ones; when the timer reaches zero it resets the pitch to -0x2AA,
 * reloads the timer with BMAGIC_CAMERA_SWING_TICKS and advances the effect step.
 * One definition shared by the bmagic effect modules; each image header names
 * the tick count BMAGIC_CAMERA_SWING_TICKS. Every change here must verify every
 * member. */
/* func_801EF274 (magic222), func_801EF540 (magic226) */
MATCH void Effect_SwingCameraAngle(void) {
    if ((g_SpadWork->unk_09 & 1) != 0) {
        g_AreaCameraAngle.vx += 20;
    } else {
        g_AreaCameraAngle.vx -= 20;
    }
    if (--g_SpadWork->unk_09 == 0) {
        g_AreaCameraAngle.vx = -0x2AA;
        g_SpadWork->unk_09   = BMAGIC_CAMERA_SWING_TICKS;
        g_SpadWork->unk_02++;
    }
}
