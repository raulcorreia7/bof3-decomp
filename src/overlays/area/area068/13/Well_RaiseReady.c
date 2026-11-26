#include "area068_13.h"

/* func_801F3578 */
MATCH void Well_RaiseReady(void) {
    u8* counter;

    if (--g_WellRaiseTimer == 0) {
        SELF(Actor)->header.mode = WELL_MODE_RAISE_CHECK;
    } else if (g_PadStates[0].pressed == PADRdown) {
        g_WellIdleFrames = 0;
        g_WellPressCount += 1;
        SELF(Actor)->header.mode = WELL_MODE_RAISE_COUNT;
        counter                  = &g_ScriptVars[1];
        *counter += 1;
    } else if (++g_WellIdleFrames >= WELL_IDLE_FRAMES_MAX) {
        SELF(Actor)->header.mode = WELL_MODE_FAIL;
    } else {
        SELF(Actor)->header.mode = WELL_MODE_RAISE_READY;
    }
}
