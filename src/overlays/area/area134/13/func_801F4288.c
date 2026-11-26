#include "area134_13.h"

MATCH void func_801F4288(void) {
    u8 timer;

    if (!(SELF(Actor)->timer & 0x3)) {
        func_801F48B0();
    }
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if (!(timer & BYTE_MASK)) {
        SELF(Actor)->header.mode += 1;
    }
    func_801F49A0();
}
