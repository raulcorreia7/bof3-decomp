#include "engine/slus/slus.h"

/* spins GFX_StepScreenFade until it reports a nonzero masked status,
 * stepping the two g_AreaCameraAngle.vx coordinates up by 0xB and the g_AreaCameraOffsetZ count
 * down by 0x32 each pass and re-arming the callback count.
 */
MATCH void func_8014F24C(void) {
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
    if ((GFX_StepScreenFade(&value, 0x200, 1, 0, flag) & BYTE_MASK) == 0) {
        first_coordinate         = level[0];
        countdown                = g_AreaCameraOffsetZ;
        g_AreaCameraRefreshCount = flag;
        first_coordinate += 0xB;
        level[0] = first_coordinate;
        /* FAKE: hold the second coordinate load after the first store. */
        ORDER_LOCK(second_coordinate = level[2]);
        countdown -= 0x32;
        /* FAKE: hold the count store ahead of the coordinate add. */
        ORDER_LOCK(g_AreaCameraOffsetZ = countdown);
        level[2] = second_coordinate + 0xB;
        CallbackWait(1);
        /* Retail keeps this spin as a goto loop (as in func_8014F460). */
        goto loop;
    }
    CallbackExit();
}
