#include "area068_13.h"

/* func_801F3658 */
MATCH s32 Well_RaiseCount(void) {
    Actor* work;
    u8     step;

    if (g_InputPressed == PADRdown) {
        g_WellPressCount++;
    }
    g_WellIdleFrames++;
    if (g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        work = g_Task;
        step = WELL_MODE_FAIL;
    } else {
        work = g_Task;
        step = WELL_MODE_RAISE_REPEAT;
    }
    work->header.mode = step;
}
