#include "area068_13.h"

/* func_801F2DE8 */
MATCH void Well_Begin(void) {
    u8 pick;

    pick                = RANDOM_MASK(WELL_TIME_LIMIT_MASK);
    g_WellLowerTimer    = g_WellTimeLimits[pick];
    g_WellRaiseTimer    = g_WellTimeLimits[pick];
    g_WellIdleFrames    = 0;
    g_WellSwishStep     = 0;
    g_WellSwishButtons  = 0;
    g_WellPressCount    = 0;
    g_WellLowerCount    = 0;
    g_Task->header.mode = WELL_MODE_LOWER_READY;
}
