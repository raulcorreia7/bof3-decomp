#include "engine/slus/slus.h"

/* advances both coordinate words of the shared target and counts its
 * distance cell down while the step reports incomplete; then releases the
 * callback thread.
 */
MATCH void func_8014EF80(void) {
    s32  flag;
    u16* coordinates;
    u16  value;
    /* FAKE: allocator picks the countdown cell first; retail reuses v0 as the coordinate accumulator. */
    MATCH_FAKE_PIN(u16, coordinate, "v0");
    u16 countdown;

    flag        = 2;
    coordinates = (u16*)&g_AreaCameraAngle.vx;
    value       = 0;

loop:
    if ((GFX_StepScreenFade(&value, 0x400, 1, 0, flag) & BYTE_MASK) == 0) {
        coordinate               = coordinates[0];
        countdown                = g_AreaCameraOffsetZ;
        g_AreaCameraRefreshCount = flag;
        coordinate += 0xB;
        coordinates[0] = coordinate;
        coordinate     = coordinates[2];
        countdown -= 0x32;
        g_AreaCameraOffsetZ = countdown;
        coordinate += 0xB;
        coordinates[2] = coordinate;
        CallbackWait(1);
        /* Retail keeps this spin as a goto loop (as in func_8014F460). */
        goto loop;
    }

    CallbackExit();
}
