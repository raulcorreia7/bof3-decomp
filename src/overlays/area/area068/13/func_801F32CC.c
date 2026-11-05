#include "area068_13.h"

MATCH void func_801F32CC(void) {
    u8* work;
    u8  value;

    work    = (u8*)g_Task;
    value   = work[9];
    work[9] = value + 0xFF;
    if (value == 0) {
        g_Task->mode = 0xD;
    }
}
