#include "area172_13.h"

MATCH void func_801F2D48(void) {
    Actor* work              = SELF(Actor);
    work->tint.steps.delta.b = -1;
    work->tint.steps.delta.g = -1;
    work->tint.steps.delta.r = -1;
    func_801F2DF4(1);
    SELF(Actor)->timer       = 4;
    SELF(Actor)->header.mode = 4;
}
