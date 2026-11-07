#include "area068_13.h"

/* func_801F3578 */
MATCH void Well_TickRaiseFrameA(void) {
    u8* counter;

    if (--g_WellRaiseTimer == 0) {
        g_Task->header.mode = 0x14;
    } else if (g_InputPressed == PADRdown) {
        g_WellIdleFrames = 0;
        g_WellPressCount += 1;
        g_Task->header.mode = 0x11;
        counter             = &D_80146865;
        *counter += 1;
    } else if (++g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        g_Task->header.mode = 0x16;
    } else {
        g_Task->header.mode = 0x10;
    }
}
