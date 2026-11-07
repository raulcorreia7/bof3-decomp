#include "area068_13.h"

/* func_801F2DE8 */
MATCH void Well_Begin(void) {
    u8 pick;

    pick                = rand() & 0xF;
    g_WellLowerTimer    = D_801F3FE4[pick];
    g_WellRaiseTimer    = D_801F3FE4[pick];
    g_WellIdleFrames    = 0;
    g_WellSwishStep     = 0;
    g_WellSwishButtons  = 0;
    g_WellPressCount    = 0;
    g_WellLowerCount    = 0;
    g_Task->header.mode = 1;
}
