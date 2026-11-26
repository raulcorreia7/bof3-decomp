#include "area068_13.h"

/* func_801F3764 */
MATCH void Well_TestRaiseCount(void) {
    u16 lower;
    u16 raise;

    lower = g_WellLowerCount;
    raise = g_WellPressCount;
    if (raise >= lower - 1 && raise <= lower + 1) {
        g_WellIdleFrames         = 0;
        SELF(Actor)->header.mode = WELL_MODE_SUCCESS;
    } else {
        SELF(Actor)->header.mode = WELL_MODE_FAIL;
    }
}
