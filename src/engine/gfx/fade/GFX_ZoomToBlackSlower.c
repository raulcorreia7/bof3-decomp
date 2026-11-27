#include "engine/slus/slus.h"

/* spins GFX_FadeUpdateScreen until it reports a nonzero masked status,
 * stepping the two g_AreaCameraAngle.vx coordinates up by 0xB and the g_AreaCameraOffsetZ count
 * down by 0x32 each pass and re-arming the callback count.
 */
/* func_8014F24C */
MATCH void GFX_ZoomToBlackSlower(void) {
    s32  flag;
    u16* level;
    u16  value;
    u16  first_coordinate;
    u16  second_coordinate;
    u16  countdown;

    flag  = 2;
    level = (u16*)&g_AreaCameraAngle.vx;
    value = 0;

loop:
    if ((GFX_FadeUpdateScreen(&value, 0x200, 1, GFX_LAYER_TOP, flag) & BYTE_MASK) == 0) {
        first_coordinate         = level[0];
        countdown                = g_AreaCameraOffsetZ;
        g_AreaCameraRefreshCount = flag;
        first_coordinate += 0xB;
        level[0] = first_coordinate;
        /* FAKE: hold the second coordinate load after the first store. */
        do {
            second_coordinate = level[2];
        } while (0);
        countdown -= 0x32;
        /* FAKE: hold the count store ahead of the coordinate add. */
        do {
            g_AreaCameraOffsetZ = countdown;
        } while (0);
        level[2] = second_coordinate + 0xB;
        SYS_ThreadWait(1);
        /* Retail keeps this spin as a goto loop (as in GFX_SpinToBlack). */
        goto loop;
    }
    SYS_ThreadExit();
}
