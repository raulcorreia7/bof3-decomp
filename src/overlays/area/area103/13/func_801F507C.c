#include "area103_13.h"

MATCH void func_801F507C(void) {
    s32 delta;
    s32 steps;

    delta = 31 - SELF(Actor)->timer;
    steps = delta;
    if (delta < 0) {
        steps = delta + 3;
    }
    func_801F5174(steps >> 2, delta * 4);
    SELF(Actor)->timer += 1;
    if (SELF(Actor)->timer >= 25U) {
        SELF(Actor)->timer = 0;
        SELF(Actor)->header.step += 1;
    }
}
