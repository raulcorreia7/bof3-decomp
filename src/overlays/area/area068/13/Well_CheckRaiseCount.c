#include "area068_13.h"

/* func_801F3764 */
MATCH void Well_CheckRaiseCount(void) {
    u8* p;
    s32 value;
    u16 a;
    u16 b;

    a = g_WellLowerCount;
    b = g_WellPressCount;
    if (b >= a - 1 && b <= a + 1) {
        p                = TASK_BYTES;
        g_WellIdleFrames = 0;
        value            = 0x15;
    } else {
        p     = TASK_BYTES;
        value = 0x16;
    }
    p[0x1] = value;
}
