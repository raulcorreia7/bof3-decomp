#include "area134_13.h"

MATCH void func_801F4288(void) {
    u8 timer;

    if (!(g_Task->timer & 0x3)) {
        func_801F48B0();
    }
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
    func_801F49A0();
}
