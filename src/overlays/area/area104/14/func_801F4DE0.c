#include "area104_14.h"

MATCH void func_801F4DE0(void) {
    u8* work;
    u8  count;

    g_Game.current->u.field.mode_12B.u8_value = 1;
    work                                      = (u8*)g_Task;
    count                                     = work[9];
    if (count == 0) {
        func_801F4E3C();
    } else {
        work[9] = count - 1;
        func_801B0DFC();
    }
}
