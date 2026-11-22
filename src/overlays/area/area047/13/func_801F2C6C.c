#include "area047_13.h"

MATCH void func_801F2C6C(void) {
    s32 remaining;

    remaining       = TASK(Actor)->vx - 1;
    TASK(Actor)->vx = remaining;
    if (remaining == 0) {
        TASK(Actor)->vx = 560;
        func_801F3298();
        TASK(Actor)->header.mode += 1;
    }
}
