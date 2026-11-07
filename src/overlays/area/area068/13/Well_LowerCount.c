#include "area068_13.h"

/* func_801F2F24 */
MATCH void Well_LowerCount(void) {
    Actor* work;
    u8     step;

    if (g_InputPressed == PADRup) {
        g_WellPressCount++;
    }
    g_WellIdleFrames++;
    if (g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        work = g_Task;
        step = WELL_MODE_FAIL;
    } else {
        work = g_Task;
        step = WELL_MODE_LOWER_REPEAT;
    }
    work->header.mode = step;
}
