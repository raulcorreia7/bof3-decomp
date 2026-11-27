#include "area068_13.h"

/* func_801F3538 */
MATCH void Well_BeginRaise(void) {
    if (g_PadStates[0].pressed == PADRdown) {
        g_WellPressCount += 1;
        SELF(Actor)->header.mode = WELL_MODE_RAISE_READY;
    }
}
