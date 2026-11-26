#include "area068_13.h"

/* func_801F2F24 */
MATCH void Well_LowerCount(void) {
    Actor* work;
    u8     step;

    if (g_PadStates[0].pressed == PADRup) {
        g_WellPressCount++;
    }
    g_WellIdleFrames++;
    if (g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        work = SELF(Actor);
        step = WELL_MODE_FAIL;
    } else {
        work = SELF(Actor);
        step = WELL_MODE_LOWER_REPEAT;
    }
    work->header.mode = step;
}
