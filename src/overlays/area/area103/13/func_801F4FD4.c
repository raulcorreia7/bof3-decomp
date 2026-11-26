#include "area103_13.h"

MATCH void func_801F4FD4(void) {
    u8 value;

    func_801F5174(7, 0x80);
    value = SELF(Actor)->timer;
    if (value < 0x10U) {
        func_801F53F0(value);
    }
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 32U) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step += 1;
    }
}
