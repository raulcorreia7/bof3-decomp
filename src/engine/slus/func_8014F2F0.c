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
    u16  offset_z;

    result                   = 0;
    iteration                = 0;
    level                    = 0x7FFF;
    g_AreaCameraAngle.vx     = -341;
    g_AreaCameraAngle.vz     = 853;
    g_AreaCameraRefreshCount = 2;

    do {
        GFX_UpdateScreenFade(&level, -0x400, 1, 0U, 2U);
        SYS_ThreadWait(1U);
        iteration++;
    } while (iteration < 5);

    active_result = result & BYTE_MASK;
    position      = (u16*)&g_AreaCameraAngle.vx;
    next_position = position + 2;
    for (;;) {
        if (active_result == 0) {
            result = GFX_UpdateScreenFade(&level, -0x400, 1, 0U, 2U);
        }

        first_coordinate         = *position;
        second_coordinate        = position[2];
        g_AreaCameraRefreshCount = 2;
        first_coordinate -= 0xB;
        *position = first_coordinate;
        /* FAKE: keep offset_z load ordered. */
        FAKE_BARRIER();
        offset_z = g_AreaCameraOffsetZ;
        second_coordinate -= 0xB;
        position[2] = second_coordinate;
        offset_z += 0x32;
        g_AreaCameraOffsetZ = offset_z;
        if ((s16)offset_z == 1500) {
            break;
        }
        SYS_ThreadWait(1U);
        active_result = result & BYTE_MASK;
    }

    *(s16*)position          = -0x2AA;
    *next_position           = 0x200;
    g_AreaCameraRefreshCount = 2;
    SYS_ThreadExit();
}
