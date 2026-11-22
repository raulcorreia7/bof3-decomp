#include "area103_13.h"

MATCH void func_801F507C(void) {
    s32 delta;
    s32 steps;

    delta = 31 - TASK(Actor)->timer;
    steps = delta;
    if (delta < 0) {
        steps = delta + 3;
    }
    func_801F5174(steps >> 2, delta * 4);
    TASK(Actor)->timer += 1;
    if (TASK(Actor)->timer >= 25U) {
        TASK(Actor)->timer = 0;
        TASK(Actor)->header.step += 1;
    }
}
