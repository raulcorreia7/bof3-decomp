#include "area068_13.h"

/* func_801F3074 */
MATCH void Well_EndLowering(void) {
    if (g_WellLowerCount == 0) {
        SELF(Actor)->header.mode = WELL_MODE_FAIL;
    } else {
        g_WellIdleFrames         = 0;
        SELF(Actor)->header.mode = WELL_MODE_SWISH_INPUT;
    }
}
