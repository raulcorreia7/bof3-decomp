#include "engine/slus/slus.h"

/* initializes two coordinates and fades them toward an endpoint
 * while waiting for the scheduler.
 */
MATCH void func_8014F024(void) {
    u16  level;
    s32  iterations;
    s32  status;
    s32  masked_status;
    u16* coordinates;
    u16* second_coordinate;
    u16  first_value;
    u16  second_value;
    u16  countdown;

    status                   = 0;
    iterations               = 0;
    level                    = 0x7FFF;
    g_AreaCameraAngle.vx     = -341;
    g_AreaCameraAngle.vz     = 853;
    g_AreaCameraRefreshCount = 2;

    do {
        GFX_StepScreenFade(&level, -0x400, 1, 0U, 2U);
        CallbackWait(1U);
        iterations++;
    } while (iterations < 5);

    masked_status     = status & BYTE_MASK;
    coordinates       = (u16*)&g_AreaCameraAngle.vx;
    second_coordinate = coordinates + 2;
    do {
        if (masked_status == 0) {
            status = GFX_StepScreenFade(&level, -0x400, 1, 0U, 2U);
        }
        first_value              = *coordinates;
        second_value             = coordinates[2];
        g_AreaCameraRefreshCount = 2;
        first_value -= 0xB;
        *coordinates = first_value;
        /* FAKE: keep counter load ordered. */
        MATCH_FAKE_BARRIER();
        countdown = g_AreaCameraOffsetZ;
        second_value -= 0xB;
        coordinates[2] = second_value;
        countdown += 0x32;
        g_AreaCameraOffsetZ = countdown;
        if ((s16)countdown == 0x5DC) {
            break;
        }
        CallbackWait(1U);
        masked_status = status & BYTE_MASK;
    } while (1);

    *(s16*)coordinates       = -0x2AA;
    *second_coordinate       = 0x200;
    g_AreaCameraRefreshCount = 2;
    CallbackExit();
}
