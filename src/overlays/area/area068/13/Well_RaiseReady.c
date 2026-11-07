#include "area068_13.h"

/* func_801F3578 */
MATCH void Well_RaiseReady(void) {
    u8* counter;

    if (--g_WellRaiseTimer == 0) {
        g_Task->header.mode = WELL_MODE_RAISE_CHECK;
    } else if (g_InputPressed == PADRdown) {
        g_WellIdleFrames = 0;
        g_WellPressCount += 1;
        g_Task->header.mode = WELL_MODE_RAISE_COUNT;
        counter             = &D_80146865;
        *counter += 1;
    } else if (++g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        g_Task->header.mode = WELL_MODE_FAIL;
    } else {
        g_Task->header.mode = WELL_MODE_RAISE_READY;
    }
}
