#include "area068_13.h"

/* func_801F2F24 */
MATCH void Well_WaitLowerPress(void) {
    Actor* work;
    u8     step;

    if (g_InputPressed == PADRup) {
        g_WellPressCount++;
    }
    g_WellIdleFrames++;
    if (g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        work = g_Task;
        step = 0x16;
    } else {
        work = g_Task;
        step = 4;
    }
    work->header.mode = step;
}
