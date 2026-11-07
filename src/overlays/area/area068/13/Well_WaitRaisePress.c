#include "area068_13.h"

/* func_801F3658 */
MATCH s32 Well_WaitRaisePress(void) {
    Actor* work;
    u8     step;

    if (g_InputPressed == PADRdown) {
        g_WellPressCount++;
    }
    g_WellIdleFrames++;
    if (g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        work = g_Task;
        step = 0x16;
    } else {
        work = g_Task;
        step = 0x12;
    }
    work->header.mode = step;
}
