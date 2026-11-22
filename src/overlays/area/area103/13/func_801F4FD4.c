#include "area103_13.h"

MATCH void func_801F4FD4(void) {
    u8 value;

    func_801F5174(7, 0x80);
    value = TASK(Actor)->timer;
    if (value < 0x10U) {
        func_801F53F0(value);
    }
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 32U) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
}
