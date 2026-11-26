#include "area172_13.h"

MATCH void func_801F4AAC(void) {
    Actor* work;
    SELF(Actor)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(Actor)->tint.bytes.flags = 1;
    work                          = SELF(Actor);
    work->tint.steps.delta.b      = -0x40;
    work->tint.steps.delta.g      = -0x40;
    work->tint.steps.delta.r      = -0x40;
}
