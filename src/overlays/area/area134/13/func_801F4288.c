#include "area134_13.h"

MATCH void func_801F4288(void) {
    u8 temp_v0;

    if (!(g_Task->timer & 3)) {
        func_801F48B0();
    }
    temp_v0       = g_Task->timer - 1;
    g_Task->timer = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->header.mode += 1;
    }
    func_801F49A0();
}
