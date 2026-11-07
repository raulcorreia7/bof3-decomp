#include "area068_13.h"

/* func_801F3538 */
MATCH void Well_BeginRaise(void) {
    if (g_InputPressed == PADRdown) {
        g_WellPressCount += 1;
        g_Task->header.mode = WELL_MODE_RAISE_READY;
    }
}
