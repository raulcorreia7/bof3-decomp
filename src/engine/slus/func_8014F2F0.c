#include "engine/slus/slus.h"

/* moves two shared coordinates toward a limit while waiting for the scheduler.
 */
MATCH void func_8014F2F0(void) {
    u16  level;
    s32  iteration;
    s32  result;
    s32  active_result;
    u16* position;
    u16* next_position;
    u16  first_coordinate;
    u16  second_coordinate;
    u16  timer;

    result                   = 0;
    iteration                = 0;
    level                    = 0x7FFF;
    g_AreaCameraAngle.vx     = -341;
    g_AreaCameraAngle.vz     = 853;
    g_AreaCameraRefreshCount = 2;

    do {
        GFX_StepScreenFade(&level, -0x400, 1, 0U, 2U);
        CallbackWait(1U);
        iteration++;
    } while (iteration < 5);

    active_result = result & BYTE_MASK;
    position      = (u16*)&g_AreaCameraAngle.vx;
    next_position = position + 2;
    for (;;) {
        if (active_result == 0) {
            result = GFX_StepScreenFade(&level, -0x400, 1, 0U, 2U);
        }

        first_coordinate         = *position;
        second_coordinate        = position[2];
        g_AreaCameraRefreshCount = 2;
        first_coordinate -= 0xB;
        *position = first_coordinate;
        /* FAKE: keep timer load ordered. */
        MATCH_FAKE_BARRIER();
        timer = g_AreaCameraOffsetZ;
        second_coordinate -= 0xB;
        position[2] = second_coordinate;
        timer += 0x32;
        g_AreaCameraOffsetZ = timer;
        if ((s16)timer == 1500) {
            break;
        }
        CallbackWait(1U);
        active_result = result & BYTE_MASK;
    }

    *(s16*)position          = -0x2AA;
    *next_position           = 0x200;
    g_AreaCameraRefreshCount = 2;
    CallbackExit();
}
