#include "area047_13.h"

MATCH void func_801F2C6C(void) {
    s32 remaining;

    remaining       = SELF(Actor)->vx - 1;
    SELF(Actor)->vx = remaining;
    if (remaining == 0) {
        SELF(Actor)->vx = 560;
        func_801F3298();
        SELF(Actor)->header.mode += 1;
    }
}
