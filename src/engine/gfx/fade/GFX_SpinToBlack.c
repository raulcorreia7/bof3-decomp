#include "engine/slus/slus.h"

/* spins the shared tint step on the g_AreaCameraAngle.vz rotation cell until
 * the step reports completion, then clears the six tint bytes and releases the
 * thread.
 */
/* func_8014F460 */
MATCH void GFX_SpinToBlack(void) {
    s32  flag;
    u16* level;
    u16  value;

    flag  = 2;
    level = (u16*)&g_AreaCameraAngle.vz;
    value = 0;

loop:
    if ((GFX_FadeUpdateScreen(&value, 0x800, 1, GFX_LAYER_TOP, flag) & BYTE_MASK) == 0) {
        *level = (*level + 0x20) & ANGLE_MASK;
        SYS_ThreadWait(1);
        /* Retail keeps this spin as a goto loop (as in GFX_FadeRunWhite). */
        goto loop;
    }

    g_GfxBuffers[1].draw.b0 = 0;
    g_GfxBuffers[1].draw.g0 = 0;
    g_GfxBuffers[1].draw.r0 = 0;
    g_GfxBuffers[0].draw.b0 = 0;
    g_GfxBuffers[0].draw.g0 = 0;
    g_GfxBuffers[0].draw.r0 = 0;
    SYS_ThreadExit();
}
