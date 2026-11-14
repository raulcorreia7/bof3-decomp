#include "area121_14.h"

MATCH void func_801F5324(void) {
    u8  count;
    u8* work;

    g_Game.current->u.field.mode_12B.u8_value = 1;
    work                                      = (u8*)g_Task;
    count                                     = work[0x09];
    if (count == 0) {
        func_801F5380();
    } else {
        work[0x09] = count - 1;
        Actor_UpdateMovement();
    }
}
