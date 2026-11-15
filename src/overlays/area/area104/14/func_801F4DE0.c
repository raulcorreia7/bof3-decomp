#include "area104_14.h"

MATCH void func_801F4DE0(void) {
    u8 count;

    g_Game.current->u.field.mode_12B.u8_value = 1;
    count                                     = g_Task->timer;
    if (count == 0) {
        func_801F4E3C();
    } else {
        g_Task->timer = count - 1;
        Actor_UpdateMovement();
    }
}
