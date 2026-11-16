#include "area134_13.h"

MATCH void func_801F4288(void) {
    u8 timer;

    if (!(g_Task->timer & 0x3)) {
        func_801F48B0();
    }
    ACTOR_COUNT_DOWN(timer, timer);
    if (!(timer & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
    func_801F49A0();
}
