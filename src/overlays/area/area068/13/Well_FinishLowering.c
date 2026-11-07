#include "area068_13.h"

/* func_801F3074 */
MATCH void Well_FinishLowering(void) {
    if (g_WellLowerCount == 0) {
        g_Task->header.mode = 0x16;
    } else {
        g_WellIdleFrames    = 0;
        g_Task->header.mode = 0xB;
    }
}
