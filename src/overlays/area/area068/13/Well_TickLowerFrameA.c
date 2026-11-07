#include "area068_13.h"

/* func_801F2F98 */
MATCH void Well_TickLowerFrameA(void) {
    if (--g_WellLowerTimer == 0) {
        SND_PlayCue(0x201);
        g_WellLowerTimer    = 0;
        g_WellLowerCount    = g_WellPressCount;
        g_Task->header.mode = 0xA;
    } else if (g_InputPressed == PADRup) {
        g_WellIdleFrames = 0;
        g_WellPressCount += 1;
        g_Task->header.mode = 1;
    } else {
        g_Task->header.mode = 3;
    }
}
