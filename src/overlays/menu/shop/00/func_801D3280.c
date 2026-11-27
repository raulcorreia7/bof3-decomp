#include "shop_00.h"

MATCH void func_801D3280(void) {
    u8* counter_ptr;
    u8  counter;

    counter_ptr               = &D_80148654;
    g_UIPanelTasks[21].active = 0;
    counter                   = *counter_ptr - 1;
    *counter_ptr              = counter;
    if (counter == 0) {
        g_MenuStep.sub_step = 1;
        g_MenuStep.state    = 0;
    }
}
