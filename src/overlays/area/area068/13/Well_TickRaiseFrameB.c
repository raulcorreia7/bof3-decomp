#include "area068_13.h"

/* func_801F36CC */
MATCH void Well_TickRaiseFrameB(void) {
    u8 timer;

    timer            = g_WellRaiseTimer - 1;
    g_WellRaiseTimer = timer;
    if (timer == 0) {
        g_WellRaiseTimer    = 0;
        g_Task->header.mode = 0x14;
    } else if (g_InputPressed == PADRdown) {
        g_WellIdleFrames = 0;
        g_WellPressCount++;
        g_Task->header.mode = 0x10;
    } else {
        g_Task->header.mode = 0x11;
    }
}
