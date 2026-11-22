#include "area134_13.h"

MATCH void func_801F4288(void) {
    u8 timer;

    if (!(TASK(Actor)->timer & 0x3)) {
        func_801F48B0();
    }
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if (!(timer & BYTE_MASK)) {
        TASK(Actor)->header.mode += 1;
    }
    func_801F49A0();
}
